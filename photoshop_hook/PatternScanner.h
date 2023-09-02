//PatternScanner.h
#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <psapi.h>
#include <sstream>
#include <iostream>

class PatternScanner {
public:
    PatternScanner(HMODULE module);

    uintptr_t FindPattern(const char* pattern);

private:
    void LoadModuleInfo();

    void ParsePattern(const char* pattern, std::vector<int>& outBytes, std::string& outMask);

    HMODULE module_;
    uintptr_t startAddress_;
    uintptr_t endAddress_;
};

