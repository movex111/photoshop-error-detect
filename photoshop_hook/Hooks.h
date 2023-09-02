// Hooks.h
#pragma once
#include <Windows.h>
#include "MinHook\MinHook.h"

// typedef
typedef int(WINAPI* MessageBoxAFn)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
extern MessageBoxAFn original_MessageBoxA;

typedef HWND(WINAPI* CreateWindowExFn)(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
extern CreateWindowExFn original_CreateWindowEx;

typedef __int64(__fastcall* PSDialogBoxFn)(HWND, LONG_PTR);
extern PSDialogBoxFn original_PSDialogBox;

// Наши функции-заменители для оригинальных функций
int WINAPI hooked_MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
HWND WINAPI hooked_CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
__int64 __fastcall hooked_PSDialogBox(HWND hWnd, LONG_PTR param);

