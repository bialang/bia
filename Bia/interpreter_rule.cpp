#include "interpreter_rule.hpp"


namespace bia
{
namespace grammar
{

interpreter_rule::interpreter_rule() noexcept
{
	_flags = F_NONE;
}

interpreter_rule::interpreter_rule(uint32_t _flags, std::vector<bia_token_function> && _tokens) noexcept : _tokens(std::move(_tokens))
{
	this->_flags = _flags;
}

size_t interpreter_rule::run_rule(const char * _buffer, size_t _size, token_param _params) const
{
	report::token_type _cursor = 0;
	const auto _size_to_begin = _params.bundle->size();
	auto _rule_id = static_cast<report::rule_type>(this - _params.rules);

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

	// Wrap up
	if (_flags & F_WRAP_UP)
	{
		report begin{};

		begin.type = report::TYPE::BEGIN;
		begin.rule_id = iRuleId;
		begin.token_id = _params.token_id;

		_params.bundle->add_report(std::move(begin));
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
				token_output output{};

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
				token_output output{};

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