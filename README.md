## Overview

`photoshop-error-detect` is a project aimed at hooking and monitoring specific functionalities inside Adobe Photoshop to detect and report errors, specifically related to PNG files. It uses the `MinHook` library for function hooking.

## Contents

1. [Getting Started](#getting-started)
2. [Components](#components)
    - [Main Entry](#main-entry)
    - [Hook Management](#hook-management)
    - [Hooks](#hooks)
    - [Pattern Scanning](#pattern-scanning)
    - [Utilities](#utilities)
3. [Building & Running](#building--running)
4. [Contributing](#contributing)
5. [Contact](#contact)
   
## Getting Started

1. Ensure you have Visual Studio or any suitable C++ IDE installed.
2. Clone this repository:
    ```
    git clone https://github.com/movex111/photoshop-error-detect/
    ```
4. Open the project file in your IDE.
5. Build the project.

## Components

### Main Entry

`dllmain.cpp` is the entry point for the DLL. It uses the `DllMain` function which is called when the DLL is loaded into the application. This is where hooks are added and initialized.

### Hook Management

`HookManager.cpp` & `HookManager.h`:
- Manages the list of hooks to be injected.
- Provides methods to add, initialize, and enable the hooks.

### Hooks

The actual hooks are found in `hooks.cpp` & `hooks.h`. They represent the modified behavior we want to introduce.

Currently, there are three basic hooks:

1. `hooked_MessageBoxA`: Intercepts the standard Windows MessageBoxA function. This hook allows us to inspect and potentially modify the text being displayed in a message box.
2. `hooked_CreateWindowEx`: Intercepts the Windows `CreateWindowEx` function. This hook checks if the text of a window being created contains the string "Not a PNG file" and outputs it to the console if it does. This can be useful to detect specific error messages being displayed by Photoshop.
3. `hooked_PSDialogBox`: This is not a Windows API function but instead appears to be a custom function used by Photoshop. The hook intercepts this function based on a memory pattern search using the `PatternScanner` class. When this function is called, the hook outputs its parameters to the console.

Inside these hook functions, additional filtering can be applied. For example, in `hooked_CreateWindowEx`, we specifically look for the text "Not a PNG file" and only print information if this text is found.

### Pattern Scanning

The `PatternScanner` class appears to be responsible for locating specific patterns of bytes within the memory of a module. These patterns usually correspond to certain instructions or sequences of instructions in assembly language. Useful for finding addresses of functions or data in cases where they cannot be directly referenced.

Let's break down the example you've given:

```cpp
uintptr_t address_PSDialogBox = scanner.FindPattern("40 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 C0 ?? ?? ?? 48 81 EC 40 ?? ?? ?? 48 C7 45 E8");
```

This means you're looking for a sequence of bytes in memory that matches the given pattern. Let's break it down:

```
| Bytes                   | Assembly Instruction                  |
|-------------------------|---------------------------------------|
| 40 55                   | push rbp                              |
| 56                      | push rsi                              |
| 57                      | push rdi                              |
| 41 54                   | push r12                              |
| 41 55                   | push r13                              |
| 41 56                   | push r14                              |
| 41 57                   | push r15                              |
| 48 8D AC 24 C0 ?? ?? ?? | lea rbp, [rsp-???]                    | (The exact offset is unknown due to the ?? placeholders)
| 48 81 EC 40 ?? ?? ??    | sub rsp, ???                          | (The exact value is unknown due to the ?? placeholders)
| 48 C7 45 E8             | mov qword ptr [rbp-18], ???           | (The exact value is unknown due to the lack of further bytes)
```

The `??` placeholders denote bytes that can be anything; in other words, these are wildcard bytes that you're not specifying in your pattern. They allow you to find patterns in memory that are mostly consistent, but might have minor variations depending on factors like different versions of the software, system state, etc.

This is an advanced technique used in reverse engineering and hacking. The goal here, as it appears, is to hook specific functions within a running process, such as Photoshop, to monitor, modify, or intercept its behavior.
### Utilities

`Utilities.cpp` & `Utilities.h`:
- Contains utility functions, like setting up a console for the application, formatting text, and converting strings.
  
## Building & Running

1. After opening the project in your IDE, set the configuration to `Release` or `Debug` based on your needs.
2. Build the project.
3. To use this DLL with Photoshop, you'll need to inject it into the running Photoshop process using a DLL injector.

## Contributing

If you want to contribute to the development of `photoshop-error-detect`, please follow these steps:

1. Fork the repository.
2. Create a new branch for your features or fixes.
3. Commit your changes and push to your forked repository.
4. Open a pull request detailing the changes made.

## Contact

For direct questions or feedback, you can reach me on Telegram: `@str_va`.

---

**Note**: Always use this project in an ethical manner. Unauthorized use or distribution of this project for malicious intent or without permission is strictly prohibited.
