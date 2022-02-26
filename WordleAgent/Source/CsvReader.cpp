
#include "WordleAgent/CsvReader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <regex>


// constructor
CsvReader::CsvReader(const std::string& filename)
{
    const std::regex comma(",");

    // open source file.
    std::ifstream ifs(filename);
    if (!ifs)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // read each line of the file
    std::string line{};
    while (ifs && getline(ifs, line))
    {
        // tokenize the line and add to the content vector
        std::vector<std::string> row{ std::sregex_token_iterator(line.begin(), line.end(), comma, -1), std::sregex_token_iterator() };
        m_content.insert(m_content.end(), row.begin(), row.end());
    }
}

