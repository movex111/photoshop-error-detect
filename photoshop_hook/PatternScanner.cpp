#include "PatternScanner.h"

PatternScanner::PatternScanner(HMODULE module) : module_(module) 
{
    LoadModuleInfo();
}

uintptr_t PatternScanner::FindPattern(const char* patternStr) 
{
    std::vector<int> bytes;
    std::string mask;

    ParsePattern(patternStr, bytes, mask);

    size_t patternLength = mask.size();
    for (uintptr_t i = startAddress_; i < endAddress_ - patternLength; ++i) {
        bool found = true;
        for (size_t j = 0; j < patternLength; ++j) {
            if (mask[j] != '?' && bytes[j] != static_cast<unsigned char>(*reinterpret_cast<char*>(i + j))) {
                found = false;
                break;
            }
        }

        if (found) {
            return i;
        }
    }
    return NULL;
}

void PatternScanner::LoadModuleInfo() 
{
    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), module_, &moduleInfo, sizeof(moduleInfo));

    startAddress_ = (uintptr_t)moduleInfo.lpBaseOfDll;
    endAddress_ = startAddress_ + moduleInfo.SizeOfImage;
}

void PatternScanner::ParsePattern(const char* patternStr, std::vector<int>& outBytes, std::string& outMask) 
{
    std::stringstream ss(patternStr);
    std::string byteStr;
    while (ss >> byteStr) {
        if (byteStr == "??") {
            outBytes.push_back(-1);
            outMask += '?';
        }
        else {
            outBytes.push_back(std::stoi(byteStr, 0, 16));
            outMask += 'x';
        }
    }
}
