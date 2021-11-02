#include "Contact.hpp"

const std::string Contact::kInfoTopFrame[3]     = {"╭", "─", "╮"};
const std::string Contact::kInfoMidFrame[3]     = {"│", " ", "│"};
const std::string Contact::kInfoBottomFrame[3]  = {"╰", "─", "╯"};

Contact::Contact(void):
    first_name_(""),
    last_name_(""),
    nickname_(""),
    phone_number_(""),
    darkest_secret_("")
{}

bool    Contact::SetFields(void) {
    std::cout << std::endl;
    std::cout << "Please input contact data. (type \".q\" to quit)" << std::endl;
    if (!Utils::AskAndGetLine(&first_name_,
        "First Name: ", Utils::IsValidName)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&last_name_,
        "Last Name: ", Utils::IsValidName)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&nickname_,
        "Nickname: ", Utils::IsValidName)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&phone_number_,
        "Phone Number: ", Utils::IsValidPhoneNumber)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&darkest_secret_,
        "Darkest Secret: ", NULL)) {
        return false;
    }
    return true;
}

void    Contact::Copy(const Contact item) {
    first_name_     = item.first_name_;
    last_name_      = item.last_name_;
    nickname_       = item.nickname_;
    phone_number_   = item.phone_number_;
    darkest_secret_ = item.darkest_secret_;
}

void    Contact::PrintFieldFixedWidth(
    ContactFieldName field,
    const size_t width,
    char padding_char,
    std::string abbrev_str
) {
    const std::string *field_value = GetField(field);
    if (field_value == NULL) { return; }
    Utils::PrintFieldFixedWidth(*field_value, width, padding_char, abbrev_str);
}

void    Contact::PrintInfo(std::size_t index) {
    std::stringstream transformer;
    transformer << index;
    const std::string index_line = "Contact Index #" + transformer.str();
    const std::string titles[] = {
        index_line,
        "First Name: ",
        "Last Name: ",
        "Nickame: ",
        "Phone Number: ",
        "Darkest Secret: "
    };
    const std::string values[] = {
        first_name_,
        last_name_,
        nickname_,
        phone_number_,
        darkest_secret_
    };
    std::size_t row_width = Utils::MaxLengthOf(titles, 6) + Utils::MaxLengthOf(values, 5);
    const std::string lines[] = {
        Utils::CenterString(index_line, row_width),
        "",
        Utils::WidenString(titles[1], values[0], row_width),
        Utils::WidenString(titles[2], values[1], row_width),
        Utils::WidenString(titles[3], values[2], row_width),
        Utils::WidenString(titles[4], values[3], row_width),
        Utils::WidenString(titles[5], values[4], row_width),
    };
    Utils::PrintLinesWithinRect(
        Contact::kInfoTopFrame,
        Contact::kInfoMidFrame,
        Contact::kInfoBottomFrame,
        lines, 7, 1);
}

std::string   *Contact::GetField(ContactFieldName field) {
    switch (field) {
        case kFirstName:
            return &first_name_;
        case kLastName:
            return &last_name_;
        case kNickname:
            return &nickname_;
        case kPhoneNumber:
            return &phone_number_;
        case kDarkestSecret:
            return &darkest_secret_;
    }
    return NULL;
}
