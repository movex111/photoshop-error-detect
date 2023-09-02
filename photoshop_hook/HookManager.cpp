#include "HookManager.h"

bool HookManager::AddHook(const std::string& hookName, LPVOID target, LPVOID detour, LPVOID* original) 
{
    HookInfo info = { target, detour, original };
    hooks[hookName] = info;
    return true;
}

bool HookManager::InitializeHooks() 
{
    if (MH_Initialize() != MH_OK) {
        printf("[-] Failed to initialize MinHook\n");
        return false;
    }

    for (const auto& pair : hooks) {
        const HookInfo& info = pair.second;
        if (MH_CreateHook(info.target, info.detour, info.original) != MH_OK) {
            printf("[-] Failed to create hook %s\n", pair.first.c_str());
            return false;
        }
        printf("[+] Success create hook %s\n", pair.first.c_str());
    }
    return true;
}

bool HookManager::EnableHooks() 
{
    for (const auto& pair : hooks) {
        const HookInfo& info = pair.second;
        if (MH_EnableHook(info.target) != MH_OK) {
            printf("[-] Failed to enable hook %s\n", pair.first.c_str());
            return false;
        }
    }
    return true;
}
