#pragma once
#include <Shlwapi.h>
#include "..\Log\tstring.h"

namespace NS_Yutils{

tstring GetModuleFilePath(HINSTANCE hModule = 0); 
tstring GetModuleFilePathWithSlash(HINSTANCE hModule = 0); 

};