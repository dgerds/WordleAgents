
#include "WordleAgent/AgentFactoryDll.h"
#include <stdexcept>

#ifdef _WIN32
#elif __linux__
#define __stdcall 
typedef int HINSTANCE;
typedef int HMODULE;
HMODULE LoadLibrary(const char *libFileName) {
  return 0;
}
void* GetProcAddress(HMODULE id, const char *func) {
  return 0;
}
#endif

namespace
{
    typedef AgentFactory* (__stdcall* get_factory_func_t)();
}


std::unique_ptr<AgentFactory> AgentFactoryDll::LoadPlugin(const std::string& dll_plugin_name)
{
    // load the library
    HINSTANCE hGetProcIDDLL = LoadLibrary(dll_plugin_name.c_str());
    if (!hGetProcIDDLL) {
        throw std::runtime_error("Unable to load DLL: " + dll_plugin_name);
    }

    // find the function to create the custom factory
    get_factory_func_t get_factory_func = (get_factory_func_t)GetProcAddress(hGetProcIDDLL, "DllGetAgentFactory");
    if (!get_factory_func) {
        throw std::runtime_error("Unable to load find function 'DllGetAgentFactory' in DLL:" + dll_plugin_name);
    }

    // call the function to create the custom factory and return it
    return std::unique_ptr<AgentFactory>(get_factory_func());
}
