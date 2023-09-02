#include "Utilities.h"

Utility::Utility() 
{
    // Конструктор (если вам нужно что-то инициализировать)
}

BOOL Utility::AllocateAndSetupConsole() 
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    return TRUE;
}

void Utility::ShowInitializationDots() 
{
    int MAX_ATTEMPTS = 3;
    int SLEEP_DURATION_MS = 500;
    printf("Installing hooks");
    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        Sleep(SLEEP_DURATION_MS);
        printf(".");
    }
    printf("\n");
}

std::string Utility::IndentText(const char* text, int spaces) 
{
    std::string indentedText;
    std::string indentation(spaces, ' ');

    std::string input(text);
    size_t pos = 0;
    while ((pos = input.find("\n")) != std::string::npos) {
        indentedText += indentation + input.substr(0, pos + 1);
        input.erase(0, pos + 1);
    }
    if (!input.empty()) {
        indentedText += indentation + input;
    }

    return indentedText;
}

std::string Utility::WideToAnsi(const wchar_t* wide) 
{
    int len = WideCharToMultiByte(CP_ACP, 0, wide, -1, nullptr, 0, nullptr, nullptr);
    if (len <= 0) return "";

    std::vector<char> buffer(len);
    WideCharToMultiByte(CP_ACP, 0, wide, -1, &buffer[0], len, nullptr, nullptr);

    return std::string(buffer.begin(), buffer.end() - 1);
}