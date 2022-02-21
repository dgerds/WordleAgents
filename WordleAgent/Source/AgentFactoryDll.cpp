
#include "WordleAgent\AgentFactoryDll.h"
#include <stdexcept>


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
