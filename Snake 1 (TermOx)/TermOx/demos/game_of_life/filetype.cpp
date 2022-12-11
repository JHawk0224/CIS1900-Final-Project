#include "filetype.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <string>

namespace {

/// Remove all control characters from the string.
void remove_controls(std::string& s)
{
    const auto end = std::remove_if(std::begin(s), std::end(s),
                                    [](char c) { return std::iscntrl(c); });
    s.erase(end, std::end(s));
}

}  // namespace

namespace gol {

auto get_filetype(const std::string& filename) -> FileType
{
    auto result     = FileType::Unknown;
    auto input_file = std::ifstream{filename};
    if (input_file.fail())
        return result;
    auto first_line = std::string{};
    std::getline(input_file, first_line);
    remove_controls(first_line);
    if (first_line == "#Life 1.05")
        result = FileType::Life_1_05;
    else if (first_line == "#Life 1.06")
        result = FileType::Life_1_06;
    else if (first_line.size() > 5 && first_line.substr(0, 6) == "!Name:")
        result = FileType::Plaintext;
    else {
        while (!input_file.fail() && !first_line.empty() &&
               first_line[0] == '#') {
            std::getline(input_file, first_line);
        }
        if (first_line.size() > 3 && first_line.substr(0, 3) == "x =")
            result = FileType::RLE;
    }
    return result;
}

auto get_extension(const std::string& filename) -> std::string
{
    auto result   = std::string{""};
    const auto at = std::find(std::rbegin(filename), std::rend(filename), '.');
    if (at != std::rend(filename)) {
        result = std::string{at.base(), std::end(filename)};
    }
    return result;
}

}  // namespace gol
