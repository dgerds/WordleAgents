
#include "WordleAgent/framework.h"
#include "WordleAgent/AgentFactory.h"


class AgentFactoryDll
{
public:
    static std::unique_ptr<AgentFactory> LoadPlugin(const std::string& dll_plugin_name);
};
