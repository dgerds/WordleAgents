// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "MyAgentFactory.h"

#ifdef _WIN32
#elif __linux__
typedef bool BOOL;
#define APIENTRY
#define __stdcall
typedef void* LPVOID;
typedef int HMODULE;
typedef uint32_t DWORD;
#define TRUE true
static const int DLL_PROCESS_ATTACH = 0;
static const int DLL_THREAD_ATTACH = 1;
static const int DLL_THREAD_DETACH = 2;
static const int DLL_PROCESS_DETACH = 3;
#define __declspec
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C"
{
#ifdef _WIN32
    __declspec(dllexport) 
#elif __linux__
#endif
	    MyAgentFactory* __stdcall DllGetAgentFactory()
    {
        return new MyAgentFactory();
    }
}
