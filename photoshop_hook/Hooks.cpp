#include "Hooks.h"
#include "Utilities.h"

MessageBoxAFn original_MessageBoxA = NULL;
CreateWindowExFn original_CreateWindowEx = NULL;
PSDialogBoxFn original_PSDialogBox = NULL;


int WINAPI hooked_MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) 
{
    printf(Utility::IndentText("[*] Hooked_MessageBoxA:\n", 3).c_str());
    printf("%s\n", Utility::IndentText(lpText, 6).c_str());

    return original_MessageBoxA(hWnd, lpText, lpCaption, uType);
}

HWND WINAPI hooked_CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    std::string convertedStr = Utility::WideToAnsi(lpWindowName);
    if (convertedStr.find("Not a PNG file") != std::string::npos) {
        printf(Utility::IndentText("[*] Hooked_CreateWindowEx:\n", 3).c_str());
        printf("%s\n", Utility::IndentText(convertedStr.c_str(), 6).c_str());
    }

    return original_CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

__int64 __fastcall hooked_PSDialogBox(HWND hWnd, LONG_PTR param)
{
    printf(Utility::IndentText("[*] hooked_PSDialogBox:\n", 3).c_str());
    printf("%s: %lu\n", Utility::IndentText("dwExStyle", 6).c_str(), param);

    return original_PSDialogBox(hWnd, param);
}