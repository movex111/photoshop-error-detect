// Utilities.h
#pragma once
#include <string>
#include <Windows.h>
#include <vector>

class Utility {
public:
    Utility();

    static std::string IndentText(const char* text, int spaces);
    static std::string WideToAnsi(const wchar_t* wide);
    static BOOL AllocateAndSetupConsole();
    static void ShowInitializationDots();

private:
};