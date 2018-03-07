cmake_minimum_required(VERSION 3.1)

# Project info
project(Bia)
set(Bia_VERSION_MAJOR 3)
set(Bia_VERSION_MINOR 60)

add_executable(Bia Bia/main.cpp)

# source and header files
target_include_directories(Bia PRIVATE "Bia")

# compiler namespace
set(Bia_HEADER_FILES_COMPILER "Bia/biaCompiler.hpp" "Bia/biaConstantOperation.hpp" "Bia/biaLocalVariableHandler.hpp" "Bia/biaTempCounter.hpp")
set(Bia_SOURCE_FILES_COMPILER "Bia/biaCompiler.cpp")

source_group("Header Files\\compiler" FILES ${Bia_HEADER_FILES_COMPILER})
source_group("Source Files\\compiler" FILES ${Bia_SOURCE_FILES_COMPILER})

target_sources(Bia PRIVATE ${Bia_SOURCE_FILES_COMPILER})


# force namespace
set(Bia_HEADER_FILES_EXCEPTION "Bia/biaException.hpp")

source_group("Header Files\\exception" FILES ${Bia_HEADER_FILES_EXCEPTION})


# force namespace
set(Bia_HEADER_FILES_FORCE "Bia/biaDisguisedCaller.hpp")

source_group("Header Files\\force" FILES ${Bia_HEADER_FILES_FORCE})


# framework namespace
set(Bia_HEADER_FILES_FRAMEWORK "Bia/biaMember.hpp" "Bia/biaMemberCreator.hpp" "Bia/biaMemberHolder.hpp" "Bia/biaNamespace.hpp" "Bia/biaUndefined.hpp")
set(Bia_SOURCE_FILES_FRAMEWORK "Bia/biaMemberHolder.cpp" "Bia/biaNamespace.cpp" "Bia/biaUndefined.cpp")

source_group("Header Files\\framework" FILES ${Bia_HEADER_FILES_FRAMEWORK})
source_group("Source Files\\framework" FILES ${Bia_SOURCE_FILES_FRAMEWORK})

set(Bia_HEADER_FILES_EXECUTABLE "Bia/biaFunction.hpp" "Bia/biaStaticFunction.hpp" "Bia/biaMemberFunction.hpp" "Bia/biaLambdaFunction.hpp")

source_group("Header Files\\framework\\executable" FILES ${Bia_HEADER_FILES_EXECUTABLE})

set(Bia_HEADER_FILES_NATIVE "Bia/biaNativeOperator.hpp" "Bia/biaNativeVariable.hpp" "Bia/biaInt.hpp" "Bia/biaFloat.hpp" "Bia/biaDouble.hpp" "Bia/biaCString.hpp")
set(Bia_SOURCE_FILES_NATIVE "Bia/biaInt.cpp" "Bia/biaFloat.cpp" "Bia/biaDouble.cpp" "Bia/biaCString.cpp")

source_group("Header Files\\framework\\native" FILES ${Bia_HEADER_FILES_NATIVE})
source_group("Source Files\\framework\\native" FILES ${Bia_SOURCE_FILES_NATIVE})

set(Bia_HEADER_FILES_OBJECT "Bia/biaClass.hpp" "Bia/biaClassRaw.hpp" "Bia/biaClassTemplate.hpp")

source_group("Header Files\\framework\\object" FILES ${Bia_HEADER_FILES_OBJECT})

target_sources(Bia PRIVATE ${Bia_SOURCE_FILES_FRAMEWORK} ${Bia_SOURCE_FILES_NATIVE})


# grammar namespace
set(Bia_HEADER_FILES_GRAMMAR "Bia/biaGrammar.hpp" "Bia/biaInterpreter.hpp" "Bia/biaInterpreterIdentifiers.hpp" "Bia/biaInterpreterRule.hpp" "Bia/biaInterpreterStringSet.hpp" "Bia/biaInterpreterTokens.hpp" "Bia/biaReportBundle.hpp")
set(Bia_SOURCE_FILES_GRAMMAR "Bia/biaGrammar.cpp" "Bia/biaInterpreterRule.cpp")

source_group("Header Files\\grammar" FILES ${Bia_HEADER_FILES_GRAMMAR})
source_group("Source Files\\grammar" FILES ${Bia_SOURCE_FILES_GRAMMAR})

target_sources(Bia PRIVATE ${Bia_SOURCE_FILES_GRAMMAR})


# machine namespace
set(Bia_HEADER_FILES_MACHINE "Bia/biaAllocator.hpp" "Bia/biaMachineCode.hpp" "Bia/biaMachineContext.hpp" "Bia/biaMachineSchein.hpp" "Bia/biaNameManager.hpp" "Bia/biaStorage.hpp" "Bia/biaTemporaryStorage.hpp" "Bia/biaVariableHandler.hpp")
set(Bia_SOURCE_FILES_MACHINE "Bia/biaAllocator.cpp" "Bia/biaMachineCode.cpp" "Bia/biaMachineContext.cpp" "Bia/biaMachineSchein.cpp" "Bia/biaNameManager.cpp")

source_group("Header Files\\machine" FILES ${Bia_HEADER_FILES_MACHINE})
source_group("Source Files\\machine" FILES ${Bia_SOURCE_FILES_MACHINE})

set(Bia_HEADER_FILES_ARCHITECTURE "Bia/biaArchitecture.hpp" "Bia/biaToolset.hpp")

source_group("Header Files\\machine\\architecture" FILES ${Bia_HEADER_FILES_ARCHITECTURE})

set(Bia_HEADER_FILES_DISASSEMBLER "Bia/biaDisassembler.hpp" "Bia/biaMachineDecoder.hpp")
set(Bia_SOURCE_FILES_DISASSEMBLER "Bia/biaMachineDecoder.cpp")

source_group("Header Files\\machine\\disassembler" FILES ${Bia_HEADER_FILES_DISASSEMBLER})
source_group("Source Files\\machine\\disassembler" FILES ${Bia_SOURCE_FILES_DISASSEMBLER})

set(Bia_HEADER_FILES_LINK "Bia/biaInstantiate.hpp" "Bia/biaLink.hpp" "Bia/biaOperator.hpp" "Bia/biaPrint.hpp")
set(Bia_SOURCE_FILES_LINK "Bia/biaInstantiate.cpp" "Bia/biaOperator.cpp")

source_group("Header Files\\machine\\link" FILES ${Bia_HEADER_FILES_LINK})
source_group("Source Files\\machine\\link" FILES ${Bia_SOURCE_FILES_LINK})

set(Bia_HEADER_FILES_MODULAR "Bia/biaModule.hpp" "Bia/biaModuleHandler.hpp")
set(Bia_SOURCE_FILES_MODULAR "Bia/biaModule.cpp")

source_group("Header Files\\machine\\modular" FILES ${Bia_HEADER_FILES_MODULAR})
source_group("Source Files\\machine\\modular" FILES ${Bia_SOURCE_FILES_MODULAR})

target_sources(Bia PRIVATE ${Bia_SOURCE_FILES_MACHINE} ${Bia_SOURCE_FILES_DISASSEMBLER} ${Bia_SOURCE_FILES_LINK} ${Bia_SOURCE_FILES_MODULAR})


# stream namespace
set(Bia_HEADER_FILES_STREAM "Bia/biaInputStream.hpp" "Bia/biaOutputStream.hpp" "Bia/biaOutputStreamBuffer.hpp")
set(Bia_SOURCE_FILES_STREAM "Bia/biaOutputStreamBuffer.cpp")

source_group("Header Files\\stream" FILES ${Bia_HEADER_FILES_STREAM})
source_group("Source Files\\stream" FILES ${Bia_SOURCE_FILES_STREAM})

target_sources(Bia PRIVATE ${Bia_SOURCE_FILES_STREAM})


# utility namespace
set(Bia_HEADER_FILES_UTILITY "Bia/biaHash.hpp" "Bia/biaHasher.hpp" "Bia/biaTypeTraits.hpp")

source_group("Header Files\\utility" FILES ${Bia_HEADER_FILES_UTILITY})