#pragma once

#include <vector>
#include <memory>

#include "yinterpreter_code.h"
#include "yinterpreter_token.h"


namespace yu
{
namespace interpret
{

/**	A struct that contains all elements of a report.	*/
struct SReport
{
	unsigned int uiRule;	///< Defines the responsible rule.
	long long llTermId;	///< Defines the responsible term id.
	long long llTokenId;	///< Defines the reposible token id.
	ycode code;
	const std::vector<SReport> * pvTokenUnion;	///< Defines the token union.
};

class CYinterpreter;

/**	An output handler for the interpreted code.	*/
class CRuleHandler
{
public:
	/**
	 * Will be called for starting the reporting.
	*/
	virtual void CommenceReporting() = 0;
	/**
	 * Completes the report with success.
	*/
	virtual void CompleteReport() = 0;
	/**
	 * Reports.
	 *
	 * @param	p_vReports	Defines the reports.
	*/
	virtual void Report(const std::vector<yu::interpret::SReport> & p_vReports) = 0;
	/**
	 * Cancels the report.
	 *
	 * @param	p_code	Defines where the problem happened if non-null.
	 *
	 * @return	 The offset if the problem should be skipped, otherwise 0 if the interpretation should be stopped.
	*/
	virtual size_t CancelReport(const ycode * p_pCode) = 0;
};

/**
 * @brief	A class that interprets code by the user-defined rules.
 * @details	This class is not safe for multithreading (adding rules and interpreting at the same time, but interpreting in two threads works fine).
 * @author	Yunus Ayar
 * @version
 * @license
*/
class CYinterpreter
{
public:
	/**
	 * Constructor.
	*/
	DLL_INTERPRETER_API CYinterpreter();
	DLL_INTERPRETER_API ~CYinterpreter();

	/**
	 * Interprets the code.
	 *
	 * @remarks	When the interpreter calls the CRuleHandler functions, the handler may add, modify or remove rules from this interpreter as well as from the temporary interpreter.
	 *
	 * @warning	Adding, modifying or removing rules asynchronously may end in undefined behavior.
	 *
	 * @since	1.0.0.1
	 *
	 * @date	25-Sep-16
	 *
	 * @param	p_uiRootRule	Defines the rule that should be used as the root.
	 * @param	[in,out]	p_pHandler	Defines the handler for the interpreted code.
	 * @param	p_code	Defines the code.
	 * @param	p_pTemporaryRules	(Optional)	Defines the temporary rules.
	 *
	 * @throw	EUndefinedRule	An unresolved rule name has been used.
	 * @throw	EUnsupportedToken	An illegal token has been loaded into a rule.
	 * @throw	EWrongEncoding	The encoding of the elements differs.
	 *
	 * @return	true if the whole code was interpreted without fail, otherwise false.
	*/
	DLL_INTERPRETER_API bool Interpret(unsigned int p_uiRootRule, CRuleHandler * p_pHandler, const ycode & p_code, const CYinterpreter * p_pTemporaryRules = nullptr) const;
	/**
	 * Adds a rule or replaces the terms of the existing one.
	 *
	 * @see	For modifying the terms of a rule use CYinterpreter::GetRule().
	 *
	 * @since	1.0.0.1
	 *
	 * @date	25-Sep-16
	 *
	 * @param	p_uiRule	Defines the unique rule.
	 * @param	p_vpTerms	Defines the terms of the rule. Only one term must be fullfilled for the rule to activate.
	 * @param	p_bUnify	(Optional)	Defines wheter the rule should be unified to a token union or not.
	 *
	 * @throw	EWrongEncoding	The encoding of the elements differs.
	 *
	 * @return	true if the rule was added, otherwise false.
	*/
	DLL_INTERPRETER_API bool AddRule(unsigned int p_uiRule, const std::vector<std::shared_ptr<STerm>> & p_vpTerms, bool p_bUnify = false);
	/**
	 * Removes the rule by its name.
	 *
	 * @since	1.3.6.36
	 *
	 * @date	27-Sep-16
	 *
	 * @param	p_uiRule	Defines the unique rule.
	 *
	 * @throw	EWrongEncoding	The encoding of the elements differs.
	 *
	 * @return	true if the rule was removed, otherwise false.
	*/
	DLL_INTERPRETER_API bool RemoveRule(unsigned int p_uiRule);
	/**
	 * Returns a pointer to the terms of the rule.
	 *
	 * @since	1.0.0.1
	 *
	 * @date	25-Sep-16
	 *
	 * @param	p_uiRule	Defines the rule.
	 *
	 * @throw	EWrongEncoding	The encoding of the elements differs.
	 *
	 * @return	A pointer to the term if the rule exists, otherwise null.
	*/
	DLL_INTERPRETER_API std::vector<std::shared_ptr<STerm>> * GetRule(unsigned int p_uiRule);

private:
	struct Impl;

	Impl * m_pImpl;
};

}
}

typedef yu::interpret::CYinterpreter yinterpreter;
