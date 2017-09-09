#include "yinterpreter.h"
#include "yinterpreter_exception.h"


namespace yu
{
namespace interpret
{

struct SRule
{
	unsigned int uiRule;
	std::vector<std::shared_ptr<STerm>> vpTerms;
	bool bUnify;
};

struct STemporaryHandler
{
	STemporaryHandler() : problemCode((const char*)nullptr)
	{
		vReports.reserve(8);
	}

	virtual size_t StartSequence()
	{
		return vReports.size();
	}

	virtual void ClearSequence(const size_t & p_iSequence)
	{
		if (vReports.size() > p_iSequence)
			vReports.erase(vReports.begin() + p_iSequence, vReports.end());
	}

	virtual void AddReport(const SReport & p_report, const size_t & p_iSize)
	{
		//Filter reports that are unnecessary
		if (p_report.code.GetSize() || p_report.pvTokenUnion)
			vReports.push_back(p_report);

		if (problemCode.GetOffset() < p_report.code.GetOffset())
			problemCode.PointTo(p_report.code, p_iSize);
	}

	virtual void UniteSequence(const size_t & p_iSequence, SReport p_report, const size_t & p_iSize)
	{
		if (vReports.size() > p_iSequence)
		{
			p_report.pvTokenUnion = new std::vector<SReport>(vReports.begin() + p_iSequence, vReports.end());
			vReports.erase(vReports.begin() + p_iSequence, vReports.end());

			AddReport(p_report, p_iSize);
		}
	}

	static void Delete(SReport * p_pReport)
	{
		for (auto i = p_pReport->pvTokenUnion->begin()._Ptr, cond = p_pReport->pvTokenUnion->end()._Ptr; i < cond; ++i)
		{
			if (i->pvTokenUnion)
				Delete(i);

			delete i->pvTokenUnion;
			i->pvTokenUnion = nullptr;
		}
	}

	std::vector<SReport> vReports;
	ycode problemCode;
};

struct SEmptyHandler : STemporaryHandler
{
	virtual size_t StartSequence() override
	{
		return 0;
	}
	virtual void ClearSequence(const size_t&) override {}
	virtual void AddReport(const SReport&, const size_t&) override {}
	virtual void UniteSequence(const size_t&, SReport, const size_t&) override {}
};

struct CYinterpreter::Impl
{
	Impl()
	{
		bRulesModified = false;
	}

	bool bRulesModified;

	std::vector<SRule> vRules;

	static std::unique_ptr<STemporaryHandler> spEmptyHandler;

	///////////////////////////////////////////////////////////////////

	enum INTERPRET_RETURN
	{
		IR_SUCCESS,
		IR_FAIL,
		IR_IGNORE
	};

	//Interpreter helper functions
	INTERPRET_RETURN InterpreterHelper_OptionalCluster(STemporaryHandler * p_pHandler, const SRule * p_pRule, ycode & p_code, SOptional * p_pOptional, SOptionalCluster * p_pOptionalCluster, const unsigned int & p_uiTermId, const CYinterpreter * p_pTemporaryRules);
	INTERPRET_RETURN InterpreterHelper_CustomChecker(STemporaryHandler * p_pHandler, const SRule * p_pRule, ycode & p_code, SOptional * p_pOptional, SCustomChecker * p_pCustomChecker, const unsigned int & p_uiTermId);
	INTERPRET_RETURN InterpreterHelper_RulePointer(STemporaryHandler * p_pHandler, ycode & p_code, SOptional * p_pOptional, SRulePointer * p_pRulePointer, const CYinterpreter * p_pTemporaryRules);

	static bool CheckCharset(const SCharset * p_pCharset, const ycode & p_code, size_t & p_iOffset);
	bool CheckCharRanges(const SCharRanges * p_pCharRanges, const ycode & p_code, size_t & p_iOffset);
	bool InterpretRule(STemporaryHandler * p_pHandler, const SRule * p_pRule, const SRule * p_pTemporaryRule, ycode & p_code, const CYinterpreter * p_pTemporaryRules);
	INTERPRET_RETURN InterpretToken(STemporaryHandler * p_pHandler, const SRule * p_pRule, ycode & p_code, SToken * p_pToken, const unsigned int & p_uiTermId, const CYinterpreter * p_pTemporaryRules);
	bool FindRule(unsigned int p_uiRule, const CYinterpreter * p_pTemporaryRules, SRule *& p_pRule, SRule *& p_pTmpRule);
};

std::unique_ptr<STemporaryHandler> CYinterpreter::Impl::spEmptyHandler(new SEmptyHandler());

CYinterpreter::Impl::INTERPRET_RETURN CYinterpreter::Impl::InterpreterHelper_OptionalCluster(STemporaryHandler * p_pHandler, const SRule * p_pRule, ycode & p_code, SOptional * p_pOptional, SOptionalCluster * p_pOptionalCluster, const unsigned int & p_uiTermId, const CYinterpreter * p_pTemporaryRules)
{
	auto iSequence = p_pHandler->StartSequence();
	auto bSuccessfulCluster = p_pOptionalCluster->unMin == 0;
	const auto cbUpperLimit = p_pOptionalCluster->unMax && p_pOptionalCluster->unMax >= p_pOptionalCluster->unMin;
	const auto cpBegin = p_pOptionalCluster->vpTokens.begin()._Ptr;
	const auto ciOffset = p_code.GetOffset();
	unsigned int unCounter = 0;
	std::unique_ptr<bool[]> pbUsed;

	if (!p_pOptionalCluster->bRepeatToken)
		pbUsed.reset(new bool[p_pOptionalCluster->vpTokens.size()]{ false });

	for (auto i = cpBegin, cond = p_pOptionalCluster->vpTokens.end()._Ptr; i < cond; ++i)
	{
		//Check if token can be used twice
		if (p_pOptionalCluster->bRepeatToken || !pbUsed[i - cpBegin])
		{
			auto iTmpSequence = p_pHandler->StartSequence();

			switch (InterpretToken(p_pHandler, p_pRule, p_code, i->get(), p_uiTermId, p_pTemporaryRules))
			{
			case IR_SUCCESS:
				++unCounter;

				//Check boundaries
				if (unCounter >= p_pOptionalCluster->unMin)
				{
					bSuccessfulCluster = true;

					if (cbUpperLimit && unCounter == p_pOptionalCluster->unMax)
						return IR_SUCCESS;
				}

				//Mark token as used
				if (!p_pOptionalCluster->bRepeatToken)
					pbUsed[i - cpBegin] = true;

				i = cpBegin - 1;

				break;
			case IR_IGNORE:
			case IR_FAIL:
				p_pHandler->ClearSequence(iTmpSequence);

				break;
			}
		}
	}

	//Failed
	if (!bSuccessfulCluster)
	{
		p_code = ciOffset;

		p_pHandler->ClearSequence(iSequence);

		return p_pOptional ? IR_IGNORE : IR_FAIL;
	}

	return IR_SUCCESS;
}

CYinterpreter::Impl::INTERPRET_RETURN CYinterpreter::Impl::InterpreterHelper_CustomChecker(STemporaryHandler * p_pHandler, const SRule * p_pRule, ycode & p_code, SOptional * p_pOptional, SCustomChecker * p_pCustomChecker, const unsigned int & p_uiTermId)
{
	size_t iOffset = 0;
	size_t iCustomSize = 0;
	long long llCustomId = 0;

	//Check if custom characters were defined
	if (auto pToken = p_pCustomChecker->m_pCharacters.get())
	{
		//Handle charset
		if (auto pCharset = dynamic_cast<SCharset*>(pToken))
		{
			//Not this term
			if (!CheckCharset(pCharset, p_code, iOffset))
				return p_pOptional ? IR_IGNORE : IR_FAIL;
		}
		//Handle charrange
		else if (auto pCharRange = dynamic_cast<SCharRanges*>(pToken))
		{
			//Not this term
			if (!CheckCharRanges(pCharRange, p_code, iOffset))
				return p_pOptional ? IR_IGNORE : IR_FAIL;
		}
		else
			throw UnsupportedToken("Unsupported characters in SCustomChecker detected: termId=" + std::to_string(p_uiTermId), pToken);
	}

	ycode code = "";
	code.PointTo(p_code, iOffset ? iOffset : p_code.GetSize());

	//Check succeeded
	if (p_pCustomChecker->Check(code, iCustomSize, llCustomId, p_pRule->uiRule, p_uiTermId) && iCustomSize < code.GetSize())
	{
		code.Truncate(iCustomSize);
		p_code += iCustomSize;
		
		p_pHandler->AddReport({ p_pRule->uiRule, p_uiTermId, llCustomId, code, nullptr }, p_code.GetSize());
	}
	else
		return p_pOptional ? IR_IGNORE : IR_FAIL;

	return IR_SUCCESS;
}

CYinterpreter::Impl::INTERPRET_RETURN CYinterpreter::Impl::InterpreterHelper_RulePointer(STemporaryHandler * p_pHandler, ycode & p_code, SOptional * p_pOptional, SRulePointer * p_pRulePointer, const CYinterpreter * p_pTemporaryRules)
{
	SRule * pRule = nullptr;
	SRule * pTmpRule = nullptr;

	//Search rule
	for (auto r = vRules.begin()._Ptr, rcond = vRules.end()._Ptr; r < rcond; ++r)
	{
		if (p_pRulePointer->uiRule == r->uiRule)
		{
			pRule = r;

			break;
		}
	}

	//Temporary rules
	if (p_pTemporaryRules)
	{
		for (auto r = p_pTemporaryRules->m_pImpl->vRules.begin()._Ptr, rcond = p_pTemporaryRules->m_pImpl->vRules.end()._Ptr; r < rcond; ++r)
		{
			if (p_pRulePointer->uiRule == r->uiRule)
			{
				pTmpRule = r;

				break;
			}
		}
	}

	if (pRule || pTmpRule)
	{
		if (!pRule)
		{
			pRule = pTmpRule;
			pTmpRule = nullptr;
		}

		//Not this term
		if (!InterpretRule(p_pHandler, pRule, pTmpRule, p_code, p_pTemporaryRules))
			return p_pOptional ? IR_IGNORE : IR_FAIL;
	}
	//Undefined rule
	else
		throw UndefinedRule("Undefined rule.", p_pRulePointer->uiRule);

	return IR_SUCCESS;
}

bool CYinterpreter::Impl::CheckCharset(const SCharset * p_pCharset, const ycode & p_code, size_t & p_iOffset)
{
	const auto ciSize = p_code.GetSize();

	if (p_pCharset->unMinChars > ciSize)
		return 0;

	p_iOffset = 0;

	const auto cbUpperLimit = p_pCharset->unMaxChars && p_pCharset->unMaxChars >= p_pCharset->unMinChars;
	const auto ciCharsetSize = p_pCharset->charset.GetSize();

	for (size_t i = 0; i < ciSize; ++i)
	{
		for (size_t j = 0; j < ciCharsetSize; ++j)
		{
			if (p_code.CompareElement(i, p_pCharset->charset, j))
				goto gt_new_match;
		}

		//No more matches. Check for charset conditions
		if (p_iOffset && p_iOffset >= p_pCharset->unMinChars)
		{
			//Check for upper limit
			if (cbUpperLimit)
			{
				if (p_iOffset <= p_pCharset->unMaxChars)
					return true;

				p_iOffset = 0;

				return false;
			}
			//Success
			else
				return true;
		}
		//No matches
		else
		{
			p_iOffset = 0;

			return p_pCharset->unMinChars == 0;
		}


	gt_new_match:;
		++p_iOffset;

		//Check for upper limit
		if (cbUpperLimit)
		{
			//Success
			if (p_iOffset == p_pCharset->unMaxChars)
				return true;
		}
	}

	//Check minimum condition
	return p_iOffset >= p_pCharset->unMinChars;
}

bool CYinterpreter::Impl::CheckCharRanges(const SCharRanges * p_pCharRanges, const ycode & p_code, size_t & p_iOffset)
{
	const auto ciSize = p_code.GetSize();

	if (p_pCharRanges->unMinChars > ciSize)
		return nullptr;

	p_iOffset = 0;
	const auto cbUpperLimit = p_pCharRanges->unMaxChars && p_pCharRanges->unMaxChars >= p_pCharRanges->unMinChars;
	const auto cpBegin = p_pCharRanges->vRanges.begin()._Ptr;
	const auto cpEnd = p_pCharRanges->vRanges.end()._Ptr;
	const auto cpExcludeBegin = p_pCharRanges->vExcludeRanges.begin()._Ptr;
	const auto cpExcludeEnd = p_pCharRanges->vExcludeRanges.end()._Ptr;

	for (size_t i = 0; i < ciSize; ++i)
	{
		//Check exclude ranges
		for (auto j = cpExcludeBegin; j < cpExcludeEnd; ++j)
		{
			if (p_code.IsElementInRange(i, j->start, j->end))
				goto gt_no_more_matches;
		}

		//Check ranges
		for (auto j = cpBegin; j < cpEnd; ++j)
		{
			if (p_code.IsElementInRange(i, j->start, j->end))
				goto gt_new_match;
		}

	gt_no_more_matches:;
		//No more matches. Check for charset conditions
		if (p_iOffset && p_iOffset >= p_pCharRanges->unMinChars)
		{
			//Check for upper limit
			if (cbUpperLimit)
			{
				if (p_iOffset <= p_pCharRanges->unMaxChars)
					return true;

				p_iOffset = 0;

				return false;
			}
			//Success
			else
				return true;
		}
		//No matches
		else
			return p_pCharRanges->unMinChars == 0;


	gt_new_match:;
		++p_iOffset;

		//Check for upper limit
		if (cbUpperLimit)
		{
			//Success
			if (p_iOffset == p_pCharRanges->unMaxChars)
				return true;
		}
	}

	//Check minimum condition
	return p_iOffset >= p_pCharRanges->unMinChars;
}

bool CYinterpreter::Impl::InterpretRule(STemporaryHandler * p_pHandler, const SRule * p_pRule, const SRule * p_pTemporaryRule, ycode & p_code, const CYinterpreter * p_pTemporaryRules)
{
	const auto ciOffset = p_code.GetOffset();
	auto pRulePointer = p_pRule;
	ycode code = "";
	
	code.PointTo(p_code, p_code.GetSize());

	//Term loop
gt_term_loop:;
	for (auto i = pRulePointer->vpTerms.begin()._Ptr, cond = pRulePointer->vpTerms.end()._Ptr; i < cond; ++i)
	{
		auto iSequence = p_pHandler->StartSequence();
		
		for (auto j = (*i)->vpTokens.begin()._Ptr, jcond = (*i)->vpTokens.end()._Ptr; j < jcond; ++j)
		{
			switch (InterpretToken(p_pHandler, pRulePointer, p_code, j->get(), (*i)->cuiTermId, p_pTemporaryRules))
			{
			case IR_SUCCESS:
				break;
			case IR_FAIL:
				goto gt_not_this_term;
			case IR_IGNORE:
				break;
			}
		}

		//Unify this rule
		if (pRulePointer->bUnify)
		{
			code.Truncate(p_code.GetOffset() - code.GetOffset());
			p_pHandler->UniteSequence(iSequence, { pRulePointer->uiRule, (*i)->cuiTermId, 0, code, nullptr }, p_code.GetSize());
		}

		//Report this term
		return true;

	gt_not_this_term:;
		//Reset params
		p_code = ciOffset;

		//Clear report only for root rule
		p_pHandler->ClearSequence(iSequence);

		//Set second rule
		if (p_pTemporaryRule && i + 1 >= cond)
		{
			pRulePointer = p_pTemporaryRule;

			goto gt_term_loop;
		}
	}

	return false;
}

CYinterpreter::Impl::INTERPRET_RETURN CYinterpreter::Impl::InterpretToken(STemporaryHandler * p_pHandler, const SRule * p_pRule, ycode & p_code, SToken * p_pToken, const unsigned int & p_uiTermId, const CYinterpreter * p_pTemporaryRules)
{
	auto pOptional = dynamic_cast<SOptional*>(p_pToken);
	auto pFiller = dynamic_cast<SFiller*>(p_pToken);
	auto iStartSequence = p_pHandler->StartSequence();

	if (pOptional)
		p_pToken = pOptional->pToken.get();
	else if (pFiller)
		p_pToken = pFiller->pToken.get();

	//Open new rule
	if (auto pRulePointer = dynamic_cast<SRulePointer*>(p_pToken))
	{
		auto iReturn = InterpreterHelper_RulePointer(p_pHandler, p_code, pOptional, pRulePointer, p_pTemporaryRules);

		if (iReturn == IR_SUCCESS)
			goto gt_return_success;
		else
			return iReturn;
	}
	//Keyword detected
	else if (auto pKeyword = dynamic_cast<SKeyword*>(p_pToken))
	{
		if (pKeyword->keyword.GetSize() <= p_code.GetSize())
		{
			//Keyword match
			if (pKeyword->Compare(p_code))
			{
				if (!pFiller)
				{
					ycode code = "";
					code.PointTo(p_code, pKeyword->keyword.GetSize());

					p_pHandler->AddReport({ p_pRule->uiRule, p_uiTermId, pKeyword->cllTokenId, code, nullptr }, p_code.GetSize());
				}

				p_code += pKeyword->keyword.GetSize();
			}
			//Not this term
			else
				return pOptional ? IR_IGNORE : IR_FAIL;
		}
		else
			return pOptional ? IR_IGNORE : IR_FAIL;
	}
	//Characters detected
	else if (dynamic_cast<SCharcters*>(p_pToken))
	{
		//Handle charset
		if (auto pCharset = dynamic_cast<SCharset*>(p_pToken))
		{
			size_t iOffset = 0;

			if (CheckCharset(pCharset, p_code, iOffset))
			{
				//Report if it is no filler
				if (!pFiller)
				{
					ycode code = "";
					code.PointTo(p_code, iOffset);

					p_pHandler->AddReport({ p_pRule->uiRule, p_uiTermId, pCharset->cllTokenId, code, nullptr }, p_code.GetSize());
				}

				p_code += iOffset;
			}
			//Not this term
			else
				return pOptional ? IR_IGNORE : IR_FAIL;
		}
		//Handle charrange
		else if (auto pCharRange = dynamic_cast<SCharRanges*>(p_pToken))
		{
			size_t iOffset = 0;

			if (CheckCharRanges(pCharRange, p_code, iOffset))
			{
				if (!pFiller)
				{
					ycode code = "";
					code.PointTo(p_code, iOffset);

					p_pHandler->AddReport({ p_pRule->uiRule, p_uiTermId, pCharRange->cllTokenId, code, nullptr }, p_code.GetSize());
				}

				p_code += iOffset;
			}
			//Not this term
			else
				return pOptional ? IR_IGNORE : IR_FAIL;
		}
		else
			throw UnsupportedToken("Unsupported characters as token detected: termId=" + std::to_string(p_uiTermId), p_pToken);
	}
	//Operator detected
	else if (dynamic_cast<SOperator*>(p_pToken))
	{
		//Single operator
		if (auto pSingleOperator = dynamic_cast<SSingleOperator*>(p_pToken))
		{
			//Optional
			if (dynamic_cast<SOptional*>(p_pToken))
			{
				switch (InterpretToken(p_pHandler, p_pRule, p_code, pSingleOperator->pToken.get(), p_uiTermId, p_pTemporaryRules))
				{
				case IR_SUCCESS:
					goto gt_return_success;
				case IR_IGNORE:
				case IR_FAIL:
					return IR_IGNORE;
				}
			}
			//Filler
			else if ((pFiller = dynamic_cast<SFiller*>(p_pToken)) != nullptr)
			{
				auto iReturn = InterpretToken(p_pHandler, p_pRule, p_code, pFiller->pToken.get(), p_uiTermId, p_pTemporaryRules);

				p_pHandler->ClearSequence(iStartSequence);

				return iReturn;
			}
			//Loop
			else if (auto pLoop = dynamic_cast<SLoop*>(p_pToken))
			{
				auto iLastOffset = p_code.GetOffset();
				auto bSuccessfulCluster = pLoop->unMin == 0;
				const auto cbUpperLimit = pLoop->unMax && pLoop->unMax >= pLoop->unMin;
				auto iSequence = p_pHandler->StartSequence();
				unsigned int unCounter = 0;
				const auto ciOffset = p_code.GetOffset();

				do
				{
					switch (InterpretToken(p_pHandler, p_pRule, p_code, pLoop->pToken.get(), p_uiTermId, p_pTemporaryRules))
					{
					case IR_SUCCESS:
					{
						auto iOffset = p_code.GetOffset();

						if (iOffset == iLastOffset)
							goto gt_return_success;

						iLastOffset = iOffset;

						++unCounter;

						//Check boundaries
						if (unCounter >= pLoop->unMin)
						{
							bSuccessfulCluster = true;

							if (cbUpperLimit)
							{
								if (unCounter == pLoop->unMax)
									goto gt_return_success;
							}
						}

						break;
					}
					case IR_IGNORE:
					case IR_FAIL:
						if (!bSuccessfulCluster)
						{
							p_code = ciOffset;

							p_pHandler->ClearSequence(iSequence);

							return pOptional ? IR_IGNORE : IR_FAIL;
						}

						//Leave loop because minimum limit is reached
						unCounter = 0;

						break;
					}
				} while (unCounter);
			}
			//Id overwrite
			else if (dynamic_cast<IdOverwrite*>(pSingleOperator))
			{
				//Overwrite token id
				if (InterpretToken(p_pHandler, p_pRule, p_code, pSingleOperator->pToken.get(), p_uiTermId, p_pTemporaryRules) == IR_SUCCESS)
				{
					for (auto i = p_pHandler->vReports.begin()._Ptr + iStartSequence, cond = p_pHandler->vReports.end()._Ptr; i < cond; ++i)
						i->llTokenId = pSingleOperator->cllTokenId;

					return IR_SUCCESS;
				}

				return pOptional ? IR_IGNORE : IR_FAIL;
			}
			else
				throw UnsupportedToken("Unsupported single operator as token detected: termId=" + std::to_string(p_uiTermId), p_pToken);
		}
		//Multi operator
		else if (auto pMultipleOperator = dynamic_cast<SMultipleOperator*>(p_pToken))
		{
			//Or
			if (dynamic_cast<SOr*>(p_pToken))
			{
				const auto ciOffset = p_code.GetOffset();

				for (auto i = pMultipleOperator->vpTokens.begin()._Ptr, cond = pMultipleOperator->vpTokens.end()._Ptr; i < cond; ++i)
				{
					auto iSequence = p_pHandler->StartSequence();

					switch (InterpretToken(p_pHandler, p_pRule, p_code, i->get(), p_uiTermId, p_pTemporaryRules))
					{
					case IR_SUCCESS:
						goto gt_return_success;
					case IR_FAIL:
					case IR_IGNORE:
						p_pHandler->ClearSequence(iSequence);

						break;
					}
				}

				//Reset code position
				p_code = ciOffset;

				return pOptional ? IR_IGNORE : IR_FAIL;
			}
			//And
			else if (dynamic_cast<SAnd*>(p_pToken))
			{
				auto iSequence = p_pHandler->StartSequence();
				const auto ciOffset = p_code.GetOffset();

				for (auto i = pMultipleOperator->vpTokens.begin()._Ptr, cond = pMultipleOperator->vpTokens.end()._Ptr; i < cond; ++i)
				{
					switch (InterpretToken(p_pHandler, p_pRule, p_code, i->get(), p_uiTermId, p_pTemporaryRules))
					{
					case IR_SUCCESS:
					case IR_IGNORE:
						break;
					case IR_FAIL:
						//Reset code position
						p_code = ciOffset;

						p_pHandler->ClearSequence(iSequence);

						return pOptional ? IR_IGNORE : IR_FAIL;
					}
				}
			}
			//Optional Cluster
			else if (auto pOptionalCluster = dynamic_cast<SOptionalCluster*>(p_pToken))
			{
				auto iReturn = InterpreterHelper_OptionalCluster(p_pHandler, p_pRule, p_code, pOptional, pOptionalCluster, p_uiTermId, p_pTemporaryRules);

				if (iReturn == IR_SUCCESS)
					goto gt_return_success;
				else
					return iReturn;
			}
			//Union token
			else if (auto pTokenUnion = dynamic_cast<STokenUnion*>(p_pToken))
			{
				auto iSequence = p_pHandler->StartSequence();
				auto bAtLeastOneInserted = false;
				const auto ciOffset = p_code.GetOffset();

				for (auto i = pMultipleOperator->vpTokens.begin()._Ptr, cond = pMultipleOperator->vpTokens.end()._Ptr; i < cond; ++i)
				{
					switch (InterpretToken(pTokenUnion->bOutlineChildren ? spEmptyHandler.get() : p_pHandler, p_pRule, p_code, i->get(), p_uiTermId, p_pTemporaryRules))
					{
					case IR_SUCCESS:
						bAtLeastOneInserted = true;
					case IR_IGNORE:
						break;
					case IR_FAIL:
						p_code = ciOffset;

						//Clear
						if (!pTokenUnion->bOutlineChildren)
							p_pHandler->ClearSequence(iSequence);

						return pOptional ? IR_IGNORE : IR_FAIL;
					}
				}

				if (bAtLeastOneInserted)
				{
					ycode code = "";
					auto iTmpOffset = p_code.GetOffset();

					p_code = ciOffset;
					code.PointTo(p_code, iTmpOffset - ciOffset);
					p_code = iTmpOffset;

					//Unite
					if (!pTokenUnion->bOutlineChildren)
						p_pHandler->UniteSequence(iSequence, { p_pRule->uiRule, p_uiTermId, pMultipleOperator->cllTokenId, code, nullptr }, p_code.GetSize());
					else
						p_pHandler->AddReport({ p_pRule->uiRule, p_uiTermId, pMultipleOperator->cllTokenId, code, nullptr }, p_code.GetSize());
				}
				else
					return pOptional ? IR_IGNORE : IR_FAIL;
			}
			else
				throw UnsupportedToken("Unsupported multi operator as token detected: termId=" + std::to_string(p_uiTermId), p_pToken);
		}
		else
			throw UnsupportedToken("Unsupported operator as token detected: termId=" + std::to_string(p_uiTermId), p_pToken);
	}
	//Custom checker
	else if (auto pCustomChecker = dynamic_cast<SCustomChecker*>(p_pToken))
	{
		auto iReturn = InterpreterHelper_CustomChecker(p_pHandler, p_pRule, p_code, pOptional, pCustomChecker, p_uiTermId);

		if (iReturn == IR_SUCCESS)
			goto gt_return_success;
		else
			return iReturn;
	}
	//Unsupported term
	else
		throw UnsupportedToken("Unsupported token detected: termId=" + std::to_string(p_uiTermId), p_pToken);

gt_return_success:;
	if (pFiller)
		p_pHandler->ClearSequence(iStartSequence);

	return IR_SUCCESS;
}

bool CYinterpreter::Impl::FindRule(unsigned int p_uiRule, const CYinterpreter * p_pTemporaryRules, SRule *& p_pRule, SRule *& p_pTmpRule)
{
	p_pRule = nullptr;
	p_pTmpRule = nullptr;

	const std::vector<SRule> * pvRules = &vRules;
	SRule ** ppRule = &p_pRule;

gt_search_rule:;
	for (auto i = pvRules->begin()._Ptr, cond = pvRules->end()._Ptr; i < cond; ++i)
	{
		if (i->uiRule == p_uiRule)
		{
			*ppRule = i;

			if (p_pTemporaryRules)
			{
				pvRules = &p_pTemporaryRules->m_pImpl->vRules;
				ppRule = &p_pTmpRule;
				p_pTemporaryRules = nullptr;

				goto gt_search_rule;
			}

			return true;
		}
	}

	//Search temporary rules
	if (p_pTemporaryRules)
	{
		pvRules = &p_pTemporaryRules->m_pImpl->vRules;
		p_pTemporaryRules = nullptr;

		goto gt_search_rule;
	}

	return p_pRule != nullptr;
}

CYinterpreter::CYinterpreter()
{
	m_pImpl = new Impl();
}

CYinterpreter::~CYinterpreter()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

bool CYinterpreter::Interpret(unsigned int p_uiRule, CRuleHandler * p_pHandler, const ycode & p_code, const CYinterpreter * p_pTemporaryRules) const
{
	SRule * pRootRule = nullptr;
	SRule * pTmpRoot = nullptr;

	//Find root
	if (!m_pImpl->FindRule(p_uiRule, p_pTemporaryRules, pRootRule, pTmpRoot))
		return false;

	m_pImpl->bRulesModified = false;

	if (p_pTemporaryRules)
		p_pTemporaryRules->m_pImpl->bRulesModified = false;

	//Interpret
	if (pRootRule && pRootRule->vpTerms.size() && p_pHandler && p_code.GetSize())
	{
		const auto ciSize = p_code.GetSize();
		size_t iLastSize;
		ycode code = "";
		code.PointTo(p_code, p_code.GetSize());

		do
		{
			iLastSize = code.GetSize();

			STemporaryHandler tmpHandler;

			//Begin reporting
			p_pHandler->CommenceReporting();

			//Find root, if rules were modified
			if (m_pImpl->bRulesModified || (p_pTemporaryRules && p_pTemporaryRules->m_pImpl->bRulesModified))
			{
				if (!m_pImpl->FindRule(p_uiRule, p_pTemporaryRules, pRootRule, pTmpRoot))
					return false;

				m_pImpl->bRulesModified = false;

				if (p_pTemporaryRules)
					p_pTemporaryRules->m_pImpl->bRulesModified = false;
			}

			if (m_pImpl->InterpretRule(&tmpHandler, pRootRule, pTmpRoot, code, p_pTemporaryRules))
			{
				//Report to handler
				if (tmpHandler.vReports.size())
				{
					p_pHandler->Report(tmpHandler.vReports);

					//Delete token union reports
					for (auto i = tmpHandler.vReports.begin()._Ptr, cond = tmpHandler.vReports.end()._Ptr; i < cond; ++i)
					{
						if (i->pvTokenUnion)
							STemporaryHandler::Delete(i);

						delete i->pvTokenUnion;
						i->pvTokenUnion = nullptr;
					}
				}

				p_pHandler->CompleteReport();
			}
			//Check problem
			else if (tmpHandler.problemCode.GetOffset() > code.GetOffset() && tmpHandler.problemCode.GetOffset() < ciSize)
			{
				auto iOffset = p_pHandler->CancelReport(&tmpHandler.problemCode);

				if (iOffset + tmpHandler.problemCode.GetOffset() < ciSize)
					code = tmpHandler.problemCode.GetOffset() + iOffset;
				//Cancel
				else
					return false;
			}
			else
			{
				p_pHandler->CancelReport(code.GetSize() ? &code : nullptr);

				return false;
			}
		} while (code.GetSize() && code.GetSize() != iLastSize);

		return true;
	}

	return false;
}

bool CYinterpreter::AddRule(unsigned int p_uiRule, const std::vector<std::shared_ptr<STerm>> & p_vpTerms, bool p_bUnify)
{
	if (p_vpTerms.size())
	{
		//Check for duplicates
		for (auto i = m_pImpl->vRules.begin()._Ptr, cond = m_pImpl->vRules.end()._Ptr; i < cond; ++i)
		{
			//Replace terms
			if (p_uiRule == i->uiRule)
			{
				i->vpTerms = p_vpTerms;

				return true;
			}
		}

		//Add rule
		m_pImpl->vRules.push_back({ p_uiRule, p_vpTerms, p_bUnify });
		m_pImpl->bRulesModified = true;

		return true;
	}

	return false;
}

bool CYinterpreter::RemoveRule(unsigned int p_uiRule)
{
	for (auto i = m_pImpl->vRules.begin(), cond = m_pImpl->vRules.end(); i < cond; ++i)
	{
		if (i->uiRule == p_uiRule)
		{
			m_pImpl->vRules.erase(i);
			m_pImpl->bRulesModified = true;

			return true;
		}
	}

	return false;
}

std::vector<std::shared_ptr<STerm>>* CYinterpreter::GetRule(unsigned int p_uiRule)
{
	for (auto i = m_pImpl->vRules.begin()._Ptr, cond = m_pImpl->vRules.end()._Ptr; i < cond; ++i)
	{
		if (i->uiRule == p_uiRule)
			return &i->vpTerms;
	}

	return nullptr;
}

}
}