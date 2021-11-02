#include "Contact.hpp"

const std::string Contact::kFields[] = {
    "First Name",
    "Last Name",
    "Nickame",
    "Phone Number",
    "Darkest Secret"
};
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

bool    Contact::ScanFields(void) {
    std::cout << std::endl;
    std::cout << "Please input contact data. (or type \".q\" to quit)" << std::endl;
    std::size_t prompt_width = Utils::MaxLengthOf(Contact::kFields, kContactFieldNumber) + 2;
    if (!Utils::AskAndGetLine(&first_name_,
        Utils::AlignString(Contact::kFields[0] + ": ", prompt_width),
        Utils::IsValidName)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&last_name_,
        Utils::AlignString(Contact::kFields[1] + ": ", prompt_width),
        Utils::IsValidName)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&nickname_,
        Utils::AlignString(Contact::kFields[2] + ": ", prompt_width),
        Utils::IsValidName)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&phone_number_,
        Utils::AlignString(Contact::kFields[3] + ": ", prompt_width),
        Utils::IsValidPhoneNumber)) {
        return false;
    }
    if (!Utils::AskAndGetLine(&darkest_secret_,
        Utils::AlignString(Contact::kFields[4] + ": ", prompt_width),
        NULL)) {
        return false;
    }
    return true;
}

void    Contact::CopyFrom(const Contact item) {
    first_name_     = item.first_name_;
    last_name_      = item.last_name_;
    nickname_       = item.nickname_;
    phone_number_   = item.phone_number_;
    darkest_secret_ = item.darkest_secret_;
}

void    Contact::PrintDetailedInfo(std::size_t index) {
    std::stringstream transformer;
    transformer << index;
    const std::string index_line = index > 0
        ? "Contact Index #" + transformer.str()
        : "Your Contact";
    const std::string titles[] = {
        index_line,
        Contact::kFields[0] + ": ",
        Contact::kFields[1] + ": ",
        Contact::kFields[2] + ": ",
        Contact::kFields[3] + ": ",
        Contact::kFields[4] + ": ",
    };
    const std::string values[] = {
        first_name_,
        last_name_,
        nickname_,
        phone_number_,
        darkest_secret_
    };
    std::size_t row_width =
        Utils::MaxLengthOf(titles, 1 + kContactFieldNumber) +
        Utils::MaxLengthOf(values, kContactFieldNumber);
    const std::string lines[] = {
        Utils::CenterString(index_line, row_width),
        "",
        Utils::SpereadStrings(titles[1], values[0], row_width),
        Utils::SpereadStrings(titles[2], values[1], row_width),
        Utils::SpereadStrings(titles[3], values[2], row_width),
        Utils::SpereadStrings(titles[4], values[3], row_width),
        Utils::SpereadStrings(titles[5], values[4], row_width),
    };
    Utils::PrintLinesWithinRect(
        Contact::kInfoTopFrame,
        Contact::kInfoMidFrame,
        Contact::kInfoBottomFrame,
        lines, 2 + kContactFieldNumber, 1);
}

const std::string&  Contact::GetField(ContactFieldName field) {
    switch (field) {
        case kFirstName:
            return first_name_;
        case kLastName:
            return last_name_;
        case kNickname:
            return nickname_;
        case kPhoneNumber:
            return phone_number_;
        case kDarkestSecret:
            return darkest_secret_;
    }
    // exception
    return first_name_;
}
