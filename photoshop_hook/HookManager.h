//HookManager.h
#pragma once
#include <Windows.h>
#include "MinHook\MinHook.h"
#include <map>
#include <string>
#include <cstdio>

class HookManager {
private:
    struct HookInfo {
        LPVOID target;
        LPVOID detour;
        LPVOID* original;
    };

    std::map<std::string, HookInfo> hooks;

public:
    bool AddHook(const std::string& hookName, LPVOID target, LPVOID detour, LPVOID* original);

    bool InitializeHooks();

    bool EnableHooks();
};
