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
    while (start < end && isspace(temp[start])) {
        start += 1;
    }
    while (start < end && isspace(temp[end - 1])) {
        end -= 1;
    }
    *buffer = temp.substr(start, end - start);
    return true;
}

bool    Utils::AskAndGetLine(
    std::string *buffer,
    const std::string prompt,
    bool (*validator)(const std::string)
) {
    while (true) {
        std::cout << prompt;
        if (!WrapGetLine(buffer)) {
            return false;
        }
        if (*buffer == Utils::kQuitAsk) {
            return false;
        }
        if (validator && !validator(*buffer)) {
            continue;
        }
        break;
    }
    return true;
}

bool    Utils::PrintLine(
    const std::string left_mid_right[3],
    const std::size_t inner_width
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
    const std::string top_tiles[3],
    const std::string mid_tiles[3],
    const std::string bottom_tiles[3],
    const std::string lines[],
    const std::size_t lines_len,
    const unsigned int padding
) {
    const std::size_t max_line_len = Utils::MaxLengthOf(lines, lines_len);
    const std::size_t inner_width = max_line_len + 2 * padding;
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

std::size_t Utils::MaxLengthOf(const std::string strs[], const std::size_t len) {
    std::size_t max_len = 0;
    for (std::size_t i = 0; i < len; i += 1) {
        if (max_len < strs[i].length()) {
            max_len = strs[i].length();
        }
    }
    return max_len;
}

std::string Utils::WidenString(
    const std::string left,
    const std::string right,
    std::size_t width
) {
    std::string widened = std::string(left);
    for (std::size_t i = widened.length() + right.length(); i < width; i += 1) {
        widened.append(" ");
    }
    widened.append(right);
    return widened;
}

std::string Utils::CenterString(const std::string str, std::size_t width) {
    std::stringstream joiner;
    const std::size_t len_str = str.length();
    if (len_str > width) {
        joiner << str;
        return joiner.str();
    }
    const std::size_t rest = width - len_str;
    const std::size_t padding_left = rest / 2;
    const std::size_t padding_right = rest - padding_left;
    for (std::size_t i = 0; i < padding_left; i += 1) {
        joiner << " ";
    }
    joiner << str;
    for (std::size_t i = 0; i < padding_right; i += 1) {
        joiner << " ";
    }
    return joiner.str();
}

void    Utils::PrintFieldFixedWidth(
    const std::string str,
    const size_t width,
    char padding_char,
    const std::string abbrev_str
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

bool    Utils::IsValidName(std::string val) {
    if (val.length() == 0) {
        return false;
    }
    return true;
}

bool    Utils::IsValidPhoneNumber(std::string val) {
    std::size_t n = val.length();
    // positive length
    if (n == 0) {
        return false;
    }
    // digits and hyphen
    // continuous hyphen
    bool is_hyphen = true;
    for (std::size_t i = 0; i < n; i += 1) {
        if (!(isdigit(val[i]) || val[i] == '-')) {
            return false;
        }
        if (is_hyphen && val[i] == '-') {
            return false;
        }
        is_hyphen = (val[i] == '-');
    }
    // no leading / trailing hyphen.
    if (val[0] == '-' || val[n - 1] == '-') {
        return false;
    }
    return true;
}

bool    Utils::IsValidSecret(std::string val) {
    if (val.length() == 0) {
        return false;
    }
    return true;
}
