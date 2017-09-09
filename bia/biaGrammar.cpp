#include "biaGrammar.h"
#include "biaCompiler.h"


namespace bia
{
namespace api
{
namespace grammar
{

yinterpreter BiaGrammar::sBiaGrammar;

void BiaGrammar::InitializeGrammar()
{
	auto pWhiteSpaceRequired = nt(new Filler(nt(new Charset(0, u8" \r\t\n", 1))));
	auto pWhiteSpaceOptional = nt(new Filler(nt(new Charset(0, u8" \r\t\n"))));
	auto pAllDigitsOptional = nt((new CharRanges(BGI_NUMBER))->AddRange('0', '9'));
	auto pQuote = nt(new Keyword(BGI_QUOTE, u8"\""));
	auto pSingleQuote = nt(new Keyword(BGI_QUOTE, u8"'"));
	auto pExclamationMark = nt(new Keyword(BGI_EXCLAMATION_MARK, "!"));
	auto pBracketOpen = nt(new Filler(nt(new Keyword(0, u8"("))));
	auto pBracketClose = nt(new Filler(nt(new Keyword(0, u8")"))));
	auto pScopeOpen = nt(new Filler(nt(new Keyword(0, u8"{"))));
	auto pScopeClose = nt(new Filler(nt(new Keyword(0, u8"}"))));
	auto pSemicolon = nt(new Filler(nt(new Keyword(0, u8";"))));
	auto pBiaOperator = nt(new Or({
		nt(new And({
			pWhiteSpaceOptional,
			nt(new Charset(BGI_OPERATOR, u8"+-*/%&|°^#~§$?!<>:=", 1)),
			pWhiteSpaceOptional
		})),
		nt(new And({
			pWhiteSpaceRequired,
			nt((new CharRanges(BGI_OPERATOR, 1))->AddRange('^', 'z')->AddRange('~', '~')->AddRange('!', '\'')->AddRange('*', '-')->AddRange('/', '/')->AddRange(':', 'Z')->AddRange('|', '|')),
			pWhiteSpaceRequired
		}))
	}));
	auto pBiaNumber = nt(new TokenUnion(BGI_NUMBER, {
		nt(new Filler(nt(new Optional(nt(new Keyword(BGI_MATH_MINUS, "-")))))),
		nt(new Or({
			nt(new And({
				nt((new CharRanges(BGI_NUMBER, 1))->AddRange('1', '9')),
				pAllDigitsOptional
			})),
			nt(new Keyword(BGI_NUMBER, u8"0"))
		})),
		nt(new Optional(nt(new And({
			nt(new Keyword(BGI_DOT_OPERATOR, u8".")),
			pAllDigitsOptional,
			nt(new Charset(BGI_NUMBER_LITERAL, u8"fFdD", 0, 1))
		}))))
	}));
	auto pBiaString = nt(new TokenUnion(BGI_STRING, {
		nt(new Or({
			nt(new And({
				pQuote,
				nt(new compiler::UTF8StringChecker<'"'>(0)),
				pQuote
			})),
			nt(new And({
				pSingleQuote,
				nt(new compiler::UTF8StringChecker<'\''>(0)),
				pSingleQuote
			}))
		}))
	}));
	auto pBiaIdentifier = nt(new TokenUnion(BGI_IDENTIFIER, {
		nt((new CharRanges(0, 1))->AddRange('a', 'z')->AddRange('A', 'Z')->AddRange('_', '_')),
		nt((new CharRanges(0))->AddRange('a', 'z')->AddRange('A', 'Z')->AddRange('_', '_')->AddRange('0', '9')),
	}, true));
	auto pBiaValue = nt(new TokenUnion(BGI_R_VALUE, { nt(new RulePointer(BGI_R_VALUE)) }));
	auto pBiaParameter = nt(new TokenUnion(BGI_PARAMETER_LIST, {
		pWhiteSpaceOptional,
		nt(new Keyword(0, u8"(")),
		pWhiteSpaceOptional,
		nt(new Optional(nt(new And({
			pBiaValue,
			pWhiteSpaceOptional,
			nt(new Loop(nt(new And({
				nt(new Filler(nt(new Keyword(0, u8",")))),
				pWhiteSpaceOptional,
				pBiaValue
			}))))
		})))),
		pBracketClose
	}));
	auto pBiaItemAccess = nt(new TokenUnion(BGI_ITEM_ACCESS, {
		pWhiteSpaceOptional,
		nt(new Keyword(0, u8"[")),
		pWhiteSpaceOptional,
		pBiaValue,
		pWhiteSpaceOptional,
		nt(new Loop(nt(new And({
			nt(new Filler(nt(new Keyword(0, u8",")))),
			pWhiteSpaceOptional,
			pBiaValue
		})))),
		nt(new Filler(nt(new Keyword(0, u8"]")))),
	}));
	auto pBiaIdentifierAccessVariations = nt(new Optional(nt(new Or({
		pBiaParameter,
		pBiaItemAccess
	}))));
	auto pBiaCustomOperator = nt(new compiler::CustomOperatorChecker(BGI_OPERATOR));
	auto pBiaMember = nt(new TokenUnion(BGI_MEMBER_CALL, {
		nt(new Optional(pBiaCustomOperator)),
		pBiaIdentifier,
		pBiaIdentifierAccessVariations,
		nt(new Loop(nt(new And({
			pWhiteSpaceOptional,
			nt(new Filler(nt(new Keyword(0, u8".")))),
			pWhiteSpaceOptional,
			pBiaIdentifier,
			pBiaIdentifierAccessVariations
		}))))
	}));
	auto pBiaVariableDeclaration = nt(new TokenUnion(BGI_VARIABLE_DECLARATION, {
		nt(new Filler(nt(new Keyword(0, "var")))),
		pWhiteSpaceRequired,
		pBiaIdentifier,
		pWhiteSpaceOptional,
		nt(new Filler(nt(new Keyword(0, u8"=")))),
		pWhiteSpaceOptional,
		pBiaValue
	}));
	auto pBiaVariableAssignment = nt(new TokenUnion(BGI_VARIABLE_ASSIGNMENT, {
		pBiaMember,
		pWhiteSpaceOptional,
		nt(new compiler::AssignChecker(0)),
		pWhiteSpaceOptional,
		pBiaValue
	}));
	auto pBiaInstantiation = nt(new TokenUnion(BGI_INSTANTIATION, {
		nt(new Filler(nt(new Keyword(0, "new")))),
		pWhiteSpaceRequired,
		pBiaIdentifier,
		nt(new Optional(nt(new And({
			pWhiteSpaceOptional,
			nt(new Filler(nt(new Keyword(0, u8".")))),
			pWhiteSpaceOptional,
			pBiaIdentifier,
		})))),
		pWhiteSpaceOptional,
		pBiaParameter
	}));
	auto pBiaValue_ = nt(new Or({
		pBiaString,
		nt(new Keyword(BGI_KEY_TRUE, u8"true")),
		nt(new Keyword(BGI_KEY_FALSE, u8"false")),
		nt(new Keyword(BGI_KEY_NULL, u8"null")),
		pBiaNumber,
		pBiaInstantiation,
		//pBiaIdentifier,
		nt(new TokenUnion(BGI_COPYOF, {
			nt(new Filler(nt(new Keyword(0, "copyof")))),
			pWhiteSpaceOptional,
			pBracketOpen,
			pWhiteSpaceOptional,
			pBiaMember,
			pWhiteSpaceOptional,
			pBracketClose
		})),
		pBiaMember
	}));
	auto pBiaStatements = nt(new And({
		pWhiteSpaceOptional,
		pScopeOpen,
		nt(new TokenUnion(BGI_R_ROOT, { nt(new Loop(nt(new RulePointer(BGI_R_ROOT)))) }, false)),
		pScopeClose,
		pWhiteSpaceOptional
	}));
	auto pBiaLoopRegisters = nt(new TokenUnion(BGI_LOOP_REGISTERS, {
		pWhiteSpaceOptional,
		nt(new Keyword(0, "register")),
		pWhiteSpaceOptional,
		nt(new Optional(nt(new And({
			nt(new Optional(pExclamationMark)),
			pBracketOpen,



			pBracketClose
		}))))
	}));

	//Algebraic expressions
	auto pMathExpression = nt(new TokenUnion(BGI_MATH_EXPRESSION, { nt(new RulePointer(BGI_R_MATH_EXPRESSION)) }));
	auto pMathFactor = nt(new Or({
		nt(new And({
			pBracketOpen,
			pMathExpression,
			pBracketClose
		})),
		pBiaValue_
	}));
	auto pMathTerm = nt(new TokenUnion(BGI_MATH_TERM, {
		pMathFactor,
		pWhiteSpaceOptional,
		nt(new Loop(nt(new And({
			nt(new Or({
				nt(new Keyword(0, "*")),
				nt(new Charset(0, "/", 1, 2)),
				nt(new Keyword(0, "%"))
			})),
			pWhiteSpaceOptional,
			pMathFactor
		}))))
	}));

	sBiaGrammar.AddRule(BGI_R_MATH_EXPRESSION, {
		NewTerm(0, {
			pWhiteSpaceOptional,
			pMathTerm,
			pWhiteSpaceOptional,
			nt(new Loop(nt(new And({
				pBiaCustomOperator,
				pWhiteSpaceOptional,
				pMathTerm,
				pWhiteSpaceOptional
			}))))
		})
	});

	sBiaGrammar.AddRule(BGI_R_ROOT, {
		NewTerm(BGI_TERM_WHILE, {
			pWhiteSpaceOptional,
			nt(new TokenUnion(0, {
				nt(new Filler(nt(new Keyword(0, u8"while")))),
				pWhiteSpaceOptional,
				pBracketOpen,
				pBiaValue,
				pBracketClose,
				pBiaStatements
			}))
		}),
		NewTerm(BGI_TERM_IF, {
			pWhiteSpaceOptional,
			nt(new TokenUnion(0, {
				nt(new Filler(nt(new Keyword(0, u8"if")))),
				pWhiteSpaceOptional,
				pBracketOpen,
				pBiaValue,
				pBracketClose,
				pBiaStatements,
				nt(new Loop(nt(new And({
					nt(new Filler(nt(new Keyword(0, u8"else")))),
					pWhiteSpaceRequired,
					nt(new Filler(nt(new Keyword(0, u8"if")))),
					pWhiteSpaceOptional,
					pBracketOpen,
					pBiaValue,
					pBracketClose,
					pBiaStatements
				})))),
				nt(new Optional(nt(new And({
					nt(new Keyword(BGI_KEY_ELSE, u8"else")),
					pBiaStatements
				}))))
			}))
		}),
		NewTerm(BGI_TERM_FOR, {
			pWhiteSpaceOptional,
			nt(new TokenUnion(0, {
				nt(new Filler(nt(new Keyword(0, u8"for")))),
				pWhiteSpaceOptional,
				pBracketOpen,
				pWhiteSpaceOptional,
				nt(new Or({
					nt(new Optional(pBiaVariableDeclaration)),
					nt(new Optional(pBiaVariableAssignment))
				})),
				pSemicolon,
				pWhiteSpaceOptional,
				pBiaValue,
				pSemicolon,
				pWhiteSpaceOptional,
				nt(new Optional(nt(new IdOverwrite(BGI_FOR_LOOP_RIGHT, 
					pBiaValue
					//pBiaVariableAssignment
				)))),
				pBracketClose,
				//nt(new Optional(pBiaLoopRegisters)),
				pBiaStatements
			}))
		}),
		NewTerm(BGI_TERM_RANGE_LOOP, {
			pWhiteSpaceOptional,
			nt(new TokenUnion(0, {
				nt(new Filler(nt(new Keyword(0, u8"range")))),
				pWhiteSpaceOptional,
				pBracketOpen,
				pWhiteSpaceOptional,
				nt(new Or({
					nt(new Optional(pBiaVariableDeclaration)),
					nt(new Optional(pBiaVariableAssignment))
				})),
				pSemicolon,
				pWhiteSpaceOptional,
				pBiaNumber,
				pWhiteSpaceOptional,
				pSemicolon,
				pWhiteSpaceOptional,
				pBiaNumber,
				pWhiteSpaceOptional,
				pBracketClose,
				pBiaStatements
			}))
		}),
		NewTerm(BGI_TERM_PRINT, {
			pWhiteSpaceOptional,
			nt(new Filler(nt(new Keyword(0, "print")))),
			pWhiteSpaceRequired,
			pBiaValue,
			pSemicolon,
			pWhiteSpaceOptional
		}),
		NewTerm(BGI_TERM_RETURN, {
			pWhiteSpaceOptional,
			nt(new TokenUnion(0, {
				nt(new Keyword(0, "return")),
				pWhiteSpaceRequired,
				nt(new Optional(pBiaValue))
			})),
			pSemicolon,
			pWhiteSpaceOptional
		}),
		NewTerm(BGI_TERM_IMPORT, {
			pWhiteSpaceOptional,
			nt(new Filler(nt(new Keyword(0, "import")))),
			pWhiteSpaceRequired,
			nt(new TokenUnion(0, {
				nt(new Optional(nt(new And({
					pBiaIdentifier,
					pWhiteSpaceRequired,
					nt(new Filler(nt(new Keyword(0, "from")))),
					pWhiteSpaceRequired
				})))),
				nt(new IdOverwrite(BGI_IMPORT_MODULE, pBiaIdentifier)),
				nt(new Optional(nt(new And({
					pWhiteSpaceRequired,
					nt(new Filler(nt(new Keyword(0, "as")))),
					pWhiteSpaceRequired,
					pBiaIdentifier
				})))),
			})),
			pWhiteSpaceOptional,
			pSemicolon,
			pWhiteSpaceOptional
		}),
		NewTerm(BGI_TERM_FUNCTION_DEFINITION, {
			pWhiteSpaceOptional,
			nt(new Filler(nt(new Keyword(0, u8"def")))),
			pWhiteSpaceRequired,
			pBiaIdentifier,
			nt(new TokenUnion(BGI_PARAMETER_LIST, {
				pWhiteSpaceOptional,
				nt(new Keyword(0, u8"(")),
				pWhiteSpaceOptional,
				nt(new Optional(nt(new And({
					pBiaIdentifier,
					pWhiteSpaceOptional,
					nt(new Loop(nt(new And({
						nt(new Filler(nt(new Keyword(0, u8",")))),
						pWhiteSpaceOptional,
						pBiaIdentifier
					}))))
				})))),
				pBracketClose
			})),
			pBiaStatements
		}),
		NewTerm(BGI_TERM_VARIABLE_DECLARATION, {
			pWhiteSpaceOptional,
			pBiaVariableDeclaration,
			pSemicolon,
			pWhiteSpaceOptional
		}),
		NewTerm(BGI_TERM_VARIABLE_ASSIGNEMENT, {
			pWhiteSpaceOptional,
			pBiaVariableAssignment,
			pSemicolon,
			pWhiteSpaceOptional
		}),
		NewTerm(BGI_TERM_DELETE, {
			pWhiteSpaceOptional,
			nt(new Filler(nt(new Keyword(0, "delete")))),
			pWhiteSpaceRequired,
			pBiaIdentifier,
			pSemicolon,
			pWhiteSpaceOptional
		}),
		NewTerm(BGI_TERM_CALL, {
			pWhiteSpaceOptional,
			pBiaValue,
			pSemicolon,
			pWhiteSpaceOptional
		})
	});


	auto pValueHelper = nt(new Or({
		nt(new TokenUnion(BGI_VALUE, {
			pWhiteSpaceOptional,
			pMathExpression,
			pWhiteSpaceOptional,
			nt(new Optional(nt(new And({
				nt(new Or({
					nt(new Keyword(0, "===")),
					nt(new Keyword(0, "==")),
					nt(new Keyword(0, "!=")),
					nt(new Keyword(0, "<=")),
					nt(new Keyword(0, ">=")),
					nt(new Keyword(0, "<")),
					nt(new Keyword(0, ">")),
				})),
				pWhiteSpaceOptional,
				pMathExpression,
				pWhiteSpaceOptional
			}))))
		})),
		nt(new And({
			pWhiteSpaceOptional,
			pBracketOpen,
			pBiaValue,
			pBracketClose,
			pWhiteSpaceOptional
		}))		
	}));
	sBiaGrammar.AddRule(BGI_R_VALUE, {
		NewTerm(0, {
			pValueHelper,
			nt(new Loop(nt(new And({
				nt(new Or({
					nt(new Keyword(BGI_CONDITIONAL_AND, "&&")),
					nt(new Keyword(BGI_CONDITIONAL_OR, "||"))
				})),
				pValueHelper
			}))))
		})
	});
}

}
}
}