#ifndef CPP00_EX01_UTILS_HPP_
# define CPP00_EX01_UTILS_HPP_

# include <iostream>
# include <string>

namespace Utils {
    bool        WrapGetLine(std::string *buffer);
    bool        PrintLinesWithinRect(
        std::string top_tiles[3],
        std::string mid_tiles[3],
        std::string bottom_tiles[3],
        std::string lines[],
        std::size_t lines_len,
        unsigned int padding
    );
    bool        PrintStringRepeatedly(std::string str, std::size_t iteration);
    std::size_t MaxLength(std::string strs[], std::size_t len);
    std::string WidenString(std::string left, std::string right, std::size_t width);
}

#endif
