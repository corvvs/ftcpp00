#include "Utils.hpp"

bool    Utils::WrapGetLine(std::string *buffer) {
    std::string temp;
    if (!std::getline(std::cin, temp)) {
        return false;
    }
    if (std::cin.bad()) {
        return false;
    }
    std::size_t start = 0;
    std::size_t end = temp.length();
    while (start < end && temp[start] == ' ') {
        start += 1;
    }
    while (start < end && temp[end - 1] == ' ') {
        end -= 1;
    }
    *buffer = temp.substr(start, end - start);
    return true;
}

bool    Utils::PrintLine(
    std::string left_mid_right[3],
    std::size_t inner_width
) {
    if (!Utils::PrintStringRepeatedly(left_mid_right[0], 1)) {
        return false;
    }
    if (!Utils::PrintStringRepeatedly(left_mid_right[1], inner_width)) {
        return false;
    }
    if (!Utils::PrintStringRepeatedly(left_mid_right[2], 1)) {
        return false;
    }
    std::cout << std::endl;
    if (std::cout.bad()) {
        return false;
    }
    return (true);
}

bool    Utils::PrintLinesWithinRect(
    std::string top_tiles[3],
    std::string mid_tiles[3],
    std::string bottom_tiles[3],
    std::string lines[],
    std::size_t lines_len,
    unsigned int padding
) {
    std::size_t max_line_len = Utils::MaxLength(lines, lines_len);
    std::size_t inner_width = max_line_len + 2 * padding;
    if (!PrintLine(top_tiles, inner_width)) {
        return false;
    }
    for (std::size_t i = 0; i < padding; i += 1) {
        if (!PrintLine(mid_tiles, inner_width)) {
            return false;
        }
    }
    for (std::size_t i = 0; i < lines_len; i += 1) {
        if (!Utils::PrintStringRepeatedly(mid_tiles[0], 1)) {
            return false;
        }
        if (!Utils::PrintStringRepeatedly(mid_tiles[1], padding)) {
            return false;
        }
        std::cout << lines[i];
        if (std::cout.bad()) {
            return false;
        }
        if (!Utils::PrintStringRepeatedly(mid_tiles[1], max_line_len - lines[i].length())) {
            return false;
        }
        if (!Utils::PrintStringRepeatedly(mid_tiles[1], padding)) {
            return false;
        }
        if (!Utils::PrintStringRepeatedly(mid_tiles[2], 1)) {
            return false;
        }
        std::cout << std::endl;
    }
    for (std::size_t i = 0; i < padding; i += 1) {
        if (!PrintLine(mid_tiles, inner_width)) {
            return false;
        }
    }
    if (PrintLine(bottom_tiles, inner_width)) {
        return false;
    }
    return true;
}

bool    Utils::PrintStringRepeatedly(std::string str, std::size_t iteration) {
    for (std::size_t i = 0; i < iteration; i += 1) {
        std::cout << str;
        if (std::cout.bad()) {
            return false;
        }
    }
    return true;
}

std::size_t Utils::MaxLength(std::string strs[], std::size_t len) {
    std::size_t MaxLength = 0;
    for (std::size_t i = 0; i < len; i += 1) {
        if (MaxLength < strs[i].length()) {
            MaxLength = strs[i].length();
        }
    }
    return MaxLength;
}

std::string Utils::WidenString(std::string left, std::string right, std::size_t width) {
    std::string widened = std::string(left);
    for (std::size_t i = widened.length() + right.length(); i < width; i += 1) {
        widened.append(" ");
    }
    widened.append(right);
    return widened;
}

void    Utils::PrintFieldFixedWidth(
    std::string str,
    const size_t width,
    char padding_char,
    std::string abbrev_str
) {
    const std::size_t field_len = str.length();
    if (field_len > width) {
        if (width > 0) {
            std::cout << str.substr(0, width - 1) << abbrev_str;
        }
    } else {
        std::cout
            << std::setfill(padding_char)
            << std::setw(width)
            << std::right
            << str;
    }
}
