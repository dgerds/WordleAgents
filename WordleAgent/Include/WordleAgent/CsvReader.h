
#include "WordleAgent/framework.h"

class CsvReader
{
public:

    // constructor
    CsvReader(const std::string& filename);

    // get a reference to the content
    const std::vector<std::string>& GetContent() const
    {
        return m_content;
    }

private:

    std::vector<std::string> m_content;
};
