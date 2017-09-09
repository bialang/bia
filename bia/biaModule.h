#pragma once

#include <string>
#include <utility>

#include "biaMemberHolder.h"


typedef unsigned long long(_cdecl*BiaModuleVersion)();
typedef const char*(_cdecl*BiaModuleDefinition)(bia::api::framework::BiaMemberHolder*);
#define BIA_MODULE_VERSION 1ull
#define BIA_MODULE_VERSION_NAME "___GetBiaModuleVersion"
#define BIA_MODULE_DEFINITION_NAME "___BiaModuleDefinition_"
#define BIA_MODULE_DEFINE_VERSION extern "C" __declspec(dllexport) unsigned long long _cdecl ___GetBiaModuleVersion() { return BIA_MODULE_VERSION; }
#define BIA_MODULE_DEFINE_MAIN extern "C" __declspec(dllexport) const char * _cdecl ___BiaModuleDefinition_(bia::api::framework::BiaMemberHolder * p_pOutput) {
#define BIA_MODULE_DEFINE_SPECIFIC(specific) extern "C" __declspec(dllexport) const char * _cdecl ___BiaModuleDefinition_##specific(bia::api::framework::BiaMemberHolder * p_pOutput) {
#define BIA_MODULE_DEFINE_END(name) return #name; }