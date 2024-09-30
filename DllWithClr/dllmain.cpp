#include "gui.h"
#include "pch.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;

bool main(const HMODULE hModule) noexcept {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    DllWithClr::Form form;
    Application::Run(% form);
    //code here when gui closed
    FreeLibraryAndExitThread(hModule, 0); // unload
}

#pragma managed(push, off)
BOOL WINAPI DllMain(const HMODULE hModule ,const DWORD  ul_reason_for_call, const LPVOID lpParameter) noexcept {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        const auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), hModule, 0, nullptr);
        if (thread)
            CloseHandle(thread);
    }
    return 1;
}
#pragma managed(pop)