#include "MinHook\MinHook.h"
#include "Hooks.h"
#include "Utilities.h"
#include "HookManager.h"
#include "PatternScanner.h"

HookManager hookManager;
PatternScanner scanner(GetModuleHandle(nullptr));  // Для текущего модуля

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) 
{
    switch (reason) 
    {
        case DLL_PROCESS_ATTACH:
            if (!Utility::AllocateAndSetupConsole())
                return FALSE;

            Utility::ShowInitializationDots();

            uintptr_t address_PSDialogBox = scanner.FindPattern("40 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 C0 ?? ?? ?? 48 81 EC 40 ?? ?? ?? 48 C7 45 E8");

            if (address_PSDialogBox) 
                hookManager.AddHook("PSDialogBox", (LPVOID)address_PSDialogBox, &hooked_PSDialogBox, reinterpret_cast<LPVOID*>(&original_PSDialogBox));
            else
                printf("[-] Pattern not found.\n");

            hookManager.AddHook("MessageBoxA", &MessageBoxA, &hooked_MessageBoxA, reinterpret_cast<LPVOID*>(&original_MessageBoxA));
            hookManager.AddHook("CreateWindowEx", &CreateWindowEx, &hooked_CreateWindowEx, reinterpret_cast<LPVOID*>(&original_CreateWindowEx));

            if (!hookManager.InitializeHooks())
                return FALSE;

            if (!hookManager.EnableHooks()) 
                return FALSE;

            break;
        }
    return TRUE;
}
