
#include "framework.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

namespace
{

    // define the command line arguments
    struct Args
    {
        Args(std::string filename)
            : filename(filename) {}

        std::string filename;
    };    

    void PrintUsage()
    {   
        std::cout << " ====================" << std::endl;
        std::cout << " | Output last line |" << std::endl;
        std::cout << " ====================" << std::endl;
        std::cout << std::endl;
        std::cout << " Usage:    LastLine.exe filename" << std::endl;
        std::cout << std::endl;
        std::cout << " Example:  LastLine.exe test.txt" << std::endl;
        std::cout << std::endl;
    }

    std::unique_ptr<Args> ParseArgs(int argc, char** argv)
    {
        std::vector<std::string> arg_vec(argv + 1, argv + argc);
        if (arg_vec.size() != 1)
        {
            throw std::runtime_error("Incorrect number of command line arguments");
        }
        return std::make_unique<Args>(arg_vec[0]);
    }
}


int main(int argc, char** argv)
{
    // parse the command line args
    std::unique_ptr<Args> args;
    try
    {
        args = ParseArgs(argc, argv);
    }
    catch (std::exception e)
    {
        std::cout << "### ERROR ### " << e.what() << std::endl;
        PrintUsage();
        return -1;
    }

    // open source file.
    std::ifstream ifs(args->filename);
    if (!ifs)
    {
        std::cout << "### ERROR ### Failed to open file: " << args->filename << std::endl;
        PrintUsage();
        return -2;
    }

    // read each line of the file and output the last non-empty line
    std::string line{};
    std::string last_nonempty_line{};
    while (ifs && getline(ifs, line)) 
    {
        if (!line.empty())
        {
            last_nonempty_line = line;
        }
    }
    std::cout << last_nonempty_line << std::endl;
}

