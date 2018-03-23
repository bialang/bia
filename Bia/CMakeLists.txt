#cmake_minimum_required(VERSION 3.1)

set(Bia_HEADER_FILES "biaConfig.hpp" "utf8.h")
set(Bia_SOURCE_FILES "")

# compiler namespace
set(Bia_HEADER_FILES_COMPILER "biaCompiler.hpp" "biaConstantOperation.hpp" "biaLocalVariableHandler.hpp" "biaTempCounter.hpp")
set(Bia_SOURCE_FILES_COMPILER "biaCompiler.cpp")

source_group("Header Files\\compiler" FILES ${Bia_HEADER_FILES_COMPILER})
source_group("Source Files\\compiler" FILES ${Bia_SOURCE_FILES_COMPILER})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_COMPILER})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_COMPILER})


# force namespace
set(Bia_HEADER_FILES_EXCEPTION "biaException.hpp")

source_group("Header Files\\exception" FILES ${Bia_HEADER_FILES_EXCEPTION})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_EXCEPTION})


# force namespace
set(Bia_HEADER_FILES_FORCE "biaInitiator.hpp" "biaDisguisedCaller.hpp")

source_group("Header Files\\force" FILES ${Bia_HEADER_FILES_FORCE})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FORCE})


# framework namespace
set(Bia_HEADER_FILES_FRAMEWORK "biaMember.hpp" "biaMemberCreator.hpp" "biaNamespace.hpp" "biaUndefined.hpp")
set(Bia_SOURCE_FILES_FRAMEWORK "biaNamespace.cpp" "biaUndefined.cpp")

source_group("Header Files\\framework" FILES ${Bia_HEADER_FILES_FRAMEWORK})
source_group("Source Files\\framework" FILES ${Bia_SOURCE_FILES_FRAMEWORK})

set(Bia_HEADER_FILES_EXECUTABLE "biaFunction.hpp" "biaStaticFunction.hpp" "biaMemberFunction.hpp" "biaLambdaFunction.hpp")

source_group("Header Files\\framework\\executable" FILES ${Bia_HEADER_FILES_EXECUTABLE})

set(Bia_HEADER_FILES_NATIVE "biaCString.hpp" "biaDouble.hpp" "biaFloat.hpp" "biaInt.hpp" "biaIntRef.hpp" "biaNativeOperator.hpp" "biaNativeType.hpp" "biaNativeVariable.hpp")
set(Bia_SOURCE_FILES_NATIVE "biaCString.cpp" "biaDouble.cpp" "biaFloat.cpp" "biaInt.cpp")

source_group("Header Files\\framework\\native" FILES ${Bia_HEADER_FILES_NATIVE})
source_group("Source Files\\framework\\native" FILES ${Bia_SOURCE_FILES_NATIVE})

set(Bia_HEADER_FILES_OBJECT "biaClass.hpp" "biaClassMemberHolder.hpp" "biaClassRaw.hpp" "biaClassTemplate.hpp")

source_group("Header Files\\framework\\object" FILES ${Bia_HEADER_FILES_OBJECT})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FRAMEWORK} ${Bia_HEADER_FILES_EXECUTABLE} ${Bia_HEADER_FILES_NATIVE} ${Bia_HEADER_FILES_OBJECT})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_FRAMEWORK} ${Bia_SOURCE_FILES_NATIVE})


# grammar namespace
set(Bia_HEADER_FILES_GRAMMAR "biaGrammar.hpp" "biaInterpreter.hpp" "biaInterpreterIdentifiers.hpp" "biaInterpreterRule.hpp" "biaInterpreterStringSet.hpp" "biaInterpreterTokens.hpp" "biaReportBundle.hpp")
set(Bia_SOURCE_FILES_GRAMMAR "biaGrammar.cpp" "biaInterpreterRule.cpp")

source_group("Header Files\\grammar" FILES ${Bia_HEADER_FILES_GRAMMAR})
source_group("Source Files\\grammar" FILES ${Bia_SOURCE_FILES_GRAMMAR})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_GRAMMAR})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_GRAMMAR})


# machine namespace
set(Bia_HEADER_FILES_MACHINE "biaAllocator.hpp" "biaMachineCode.hpp" "biaMachineContext.hpp" "biaMachineSchein.hpp" "biaNameManager.hpp" "biaTemporaryStorage.hpp" "biaVariableHandler.hpp")
set(Bia_SOURCE_FILES_MACHINE "biaAllocator.cpp" "biaMachineCode.cpp" "biaMachineContext.cpp" "biaMachineSchein.cpp" "biaNameManager.cpp")

source_group("Header Files\\machine" FILES ${Bia_HEADER_FILES_MACHINE})
source_group("Source Files\\machine" FILES ${Bia_SOURCE_FILES_MACHINE})

set(Bia_HEADER_FILES_ARCHITECTURE "biaArchitecture.hpp" "biaToolset.hpp")

source_group("Header Files\\machine\\architecture" FILES ${Bia_HEADER_FILES_ARCHITECTURE})

set(Bia_HEADER_FILES_DISASSEMBLER "biaMachineDecoder.hpp")
set(Bia_SOURCE_FILES_DISASSEMBLER "biaMachineDecoder.cpp")

source_group("Header Files\\machine\\disassembler" FILES ${Bia_HEADER_FILES_DISASSEMBLER})
source_group("Source Files\\machine\\disassembler" FILES ${Bia_SOURCE_FILES_DISASSEMBLER})

set(Bia_HEADER_FILES_LINK "biaInstantiate.hpp" "biaLink.hpp" "biaOperator.hpp" "biaPrint.hpp")
set(Bia_SOURCE_FILES_LINK "biaInstantiate.cpp" "biaOperator.cpp")

source_group("Header Files\\machine\\link" FILES ${Bia_HEADER_FILES_LINK})
source_group("Source Files\\machine\\link" FILES ${Bia_SOURCE_FILES_LINK})

set(Bia_HEADER_FILES_MODULAR "biaModule.hpp" "biaModuleHandler.hpp")
set(Bia_SOURCE_FILES_MODULAR "biaModule.cpp")

source_group("Header Files\\machine\\modular" FILES ${Bia_HEADER_FILES_MODULAR})
source_group("Source Files\\machine\\modular" FILES ${Bia_SOURCE_FILES_MODULAR})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_MACHINE} ${Bia_HEADER_FILES_ARCHITECTURE} ${Bia_HEADER_FILES_DISASSEMBLER} ${Bia_HEADER_FILES_LINK} ${Bia_HEADER_FILES_MODULAR})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_MACHINE} ${Bia_SOURCE_FILES_DISASSEMBLER} ${Bia_SOURCE_FILES_LINK} ${Bia_SOURCE_FILES_MODULAR})

# stream namespace
set(Bia_HEADER_FILES_STREAM "biaInputStream.hpp" "biaOutputStream.hpp" "biaOutputStreamBuffer.hpp")
set(Bia_SOURCE_FILES_STREAM "biaOutputStreamBuffer.cpp")

source_group("Header Files\\stream" FILES ${Bia_HEADER_FILES_STREAM})
source_group("Source Files\\stream" FILES ${Bia_SOURCE_FILES_STREAM})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_STREAM})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_STREAM})


# utility namespace
set(Bia_HEADER_FILES_UTILITY "biaHash.hpp" "biaHasher.hpp" "biaTypeTraits.hpp")

source_group("Header Files\\utility" FILES ${Bia_HEADER_FILES_UTILITY})
 
 set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_UTILITY})
 
 # Add library
 add_library(Bia ${Bia_HEADER_FILES} ${Bia_SOURCE_FILES})