#pragma once

#include <string>
#include <sstream>
#include <fstream>

namespace util
{
    const std::string file_as_string(const std::string& filename)
    {
        std::ifstream file(filename);

        if (!file.good())
        {
            std::stringstream ss;
            ss << "Cannot open or read file \"" << filename << "\"" << std::endl;
            throw std::runtime_error(ss.str());
        }

        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        std::string buffer(size, ' ');
        file.seekg(0);
        file.read(&buffer[0], size);
        return buffer;
    }
}
