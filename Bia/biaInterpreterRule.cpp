#include "biaInterpreterRule.hpp"


namespace bia
{
namespace grammar
{

BiaInterpreterRule::BiaInterpreterRule()
{
	m_fFlags = F_NONE;
}

BiaInterpreterRule::BiaInterpreterRule(uint32_t p_fFlags, std::vector<bia_token_function> p_vTokens) : m_vTokens(std::move(p_vTokens))
{
	m_fFlags = p_fFlags;

	if (m_vTokens.size() > (1 << Report::TOKEN_BITS) - 1)
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid token size.");
}

size_t BiaInterpreterRule::RunRule(const char * p_pcBuffer, size_t p_iSize, TokenParams p_params)
{
	const auto iSizeToBegin = p_params.pBundle->Size();
	Report::token_id iCursor = 0;
	auto iRuleId = static_cast<Report::rule_id>(this - p_params.pRules);
	auto WrapUp = [&] {
		auto unTokenAdded = p_params.pBundle->Size() - iSizeToBegin;

		if (m_fFlags & F_WRAP_UP)
		{
			if (unTokenAdded > 1)
			{
				//Edit beginning token
				auto pBegin = p_params.pBundle->Begin() + iSizeToBegin;

				pBegin->content.children = { pBegin, p_params.pBundle->End() };

				//End
				auto end = *pBegin;

				end.type = Report::TYPE::END;

				p_params.pBundle->AddReport(std::move(end));
			}
			//Dont report empty child
			else if (m_fFlags & F_DONT_REPORT_EMPTY)
			{
				if (unTokenAdded)
					p_params.pBundle->Reset(iSizeToBegin);
			}
			//Empty child
			else if (unTokenAdded == 1)
			{
				//Edit beginning token
				auto pBegin = p_params.pBundle->Begin() + iSizeToBegin;

				pBegin->content.children = { pBegin, pBegin };
				pBegin->type = Report::TYPE::EMPTY_CHILD;
			}
		}
	};

	//Wrap up
	if (m_fFlags & F_WRAP_UP)
	{
		Report begin{};

		begin.type = Report::TYPE::BEGIN;
		begin.unRuleId = iRuleId;
		begin.unTokenId = p_params.iTokenId;

		p_params.pBundle->AddReport(std::move(begin));
	}

	//Or loop
	if (m_fFlags & F_OR)
	{
		size_t iAccount = 0;
		bool bLoop;

		while (iCursor < m_vTokens.size())
		{
			do
			{
				TokenOutput output{};

				p_params.iTokenId = iCursor + 1;
				
				switch (m_vTokens.begin()[iCursor++](p_pcBuffer, p_iSize, p_params, output))
				{
				case ACTION::REPORT:
				{
					Report token{};

					token.type = Report::TYPE::TOKEN;
					token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
					token.unRuleId = iRuleId;
					token.unTokenId = iCursor;
					token.unCustomParameter = output.iCustom;

					p_params.pBundle->AddReport(std::move(token));
				}
				case ACTION::DONT_REPORT:
					WrapUp();

					return output.iTokenSize + output.iBufferOffset + output.iBufferPadding + iAccount;
				case ACTION::REPORT_AND_LOOP:
				{
					Report token{};

					token.type = Report::TYPE::TOKEN;
					token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
					token.unRuleId = iRuleId;
					token.unTokenId = iCursor;
					token.unCustomParameter = output.iCustom;

					p_params.pBundle->AddReport(std::move(token));
				}
				case ACTION::DONT_REPORT_AND_LOOP:
				{
					auto iOffset = output.iTokenSize + output.iBufferOffset + output.iBufferPadding;

					iAccount += iOffset;
					p_pcBuffer += iOffset;
					p_iSize -= iOffset;

					bLoop = true;
					--iCursor;

					continue;
				}
				case ACTION::ERROR:
					break;
				}

				bLoop = false;
			} while (bLoop);
		}

		//Clear errors
		p_params.pBundle->Reset(iSizeToBegin);

		return 0;
	}
	//And loop
	else
	{
		const auto ciSize = p_iSize;
		bool bLoop;

		while (iCursor < m_vTokens.size())
		{
			do
			{
				TokenOutput output{};

				p_params.iTokenId = iCursor + 1;

				switch (m_vTokens.begin()[iCursor++](p_pcBuffer, p_iSize, p_params, output))
				{
				case ACTION::REPORT:
				{
					Report token{};

					token.type = Report::TYPE::TOKEN;
					token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
					token.unRuleId = iRuleId;
					token.unTokenId = iCursor;
					token.unCustomParameter = output.iCustom;

					p_params.pBundle->AddReport(std::move(token));
				}
				case ACTION::DONT_REPORT:
				{
					auto iOffset = output.iTokenSize + output.iBufferOffset + output.iBufferPadding;

					p_pcBuffer += iOffset;
					p_iSize -= iOffset;

					break;
				}
				case ACTION::REPORT_AND_LOOP:
				{
					Report token{};

					token.type = Report::TYPE::TOKEN;
					token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
					token.unRuleId = iRuleId;
					token.unTokenId = iCursor;
					token.unCustomParameter = output.iCustom;

					p_params.pBundle->AddReport(std::move(token));
				}
				case ACTION::DONT_REPORT_AND_LOOP:
				{
					auto iOffset = output.iTokenSize + output.iBufferOffset + output.iBufferPadding;

					p_pcBuffer += iOffset;
					p_iSize -= iOffset;

					bLoop = true;
					--iCursor;

					continue;
				}
				case ACTION::ERROR:
					//Clear errors
					p_params.pBundle->Reset(iSizeToBegin);

					return 0;
				}

				bLoop = false;
			} while (bLoop);
		}

		WrapUp();

		return ciSize - p_iSize;
	}
}

}
}