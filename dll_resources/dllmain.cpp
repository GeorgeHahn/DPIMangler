#include <Windows.h>
#include "MinHook.h"

bool initialized = false;

typedef int (WINAPI *SETPROCESSDPIAWARE)(VOID);
typedef int (WINAPI *SETPROCESSDPIAWARENESS)(VOID); // TODO: For W8.1 users, hook SetProcessDpiAwareness and nuke it too

// Pointer for calling original SETPROCESSDPIAWARE.
SETPROCESSDPIAWARE fpSetProcessDPIAware = NULL;

// New function which overrides SetProcessDPIAware.
int WINAPI NukeSetProcessDPIAware()
{
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (initialized == true)
            break;

        initialized = true;

        //MessageBoxW(NULL, L"Hooking", L"DPIMangler", MB_OK);

        // Initialize MinHook.
        if (MH_Initialize() != MH_OK)
        {
            MessageBoxW(NULL, L"Initialization error", L"DPIMangler", MB_OK);
            return 1;
        }

        // Create a hook for SetProcessDPIAware, in disabled state.
        if (MH_CreateHook(&SetProcessDPIAware, &NukeSetProcessDPIAware,
            reinterpret_cast<void**>(&fpSetProcessDPIAware)) != MH_OK)
        {
            MessageBoxW(NULL, L"Error creating hook", L"DPIMangler", MB_OK);
            return 1;
        }

        // Enable the hook for SetProcessDPIAware.
        if (MH_EnableHook(&SetProcessDPIAware) != MH_OK)
        {
            MessageBoxW(NULL, L"Error enabling hook", L"DPIMangler", MB_OK);
            return 1;
        }

        //MessageBoxW(NULL, L"Hooked...", L"DPIManger", MB_OK);

        break;
    case DLL_PROCESS_DETACH:

        // Disable the hook for SetProcessDPIAware.
        if (MH_DisableHook(&SetProcessDPIAware) != MH_OK)
        {
            MessageBoxW(NULL, L"Error disabling hook", L"DPIMangler", MB_OK);
            return 1;
        }

        // Uninitialize MinHook.
        if (MH_Uninitialize() != MH_OK)
        {
            MessageBoxW(NULL, L"Error uninitializing minhook", L"DPIMangler", MB_OK);
            return 1;
        }
        break;
    }

	return TRUE;
}
