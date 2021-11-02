#ifndef CPP00_EX01_UTILS_HPP_
# define CPP00_EX01_UTILS_HPP_

# include <iostream>
# include <iomanip>
# include <string>
# include <sstream>

namespace Utils {
    const std::string kQuitAsk = ".q";

    bool        WrapGetLine(std::string *buffer);
    bool        AskAndGetLine(
        std::string *buffer,
        const std::string prompt,
        bool (*validator)(const std::string)
    );
    bool        PrintLine(
        const std::string left_mid_right[3],
        const std::size_t inner_width
    );
    bool        PrintLinesWithinRect(
        const std::string top_tiles[3],
        const std::string mid_tiles[3],
        const std::string bottom_tiles[3],
        const std::string lines[],
        const std::size_t lines_len,
        const unsigned int padding
    );
    bool        PrintStringRepeatedly(std::string str, std::size_t iteration);
    std::size_t MaxLengthOf(
        const std::string strs[],
        const std::size_t len
    );
    std::string WidenString(
        const std::string left,
        const std::string right,
        std::size_t width
    );
    std::string CenterString(const std::string str, std::size_t width);
    void        PrintFieldFixedWidth(
        const std::string str,
        const size_t width,
        char padding_char,
        const std::string abbrev_str
    );
    bool        IsValidName(std::string val);
    bool        IsValidPhoneNumber(std::string val);
    bool        IsValidSecret(std::string val);
}

#endif
