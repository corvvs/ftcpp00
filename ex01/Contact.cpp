#include "Contact.hpp"

Contact::Contact():
    first_name_(""),
    last_name_(""),
    nickname_(""),
    phone_number_(""),
    darkest_secret_("")
{}

bool    Contact::SetFields() {
    std::cout << std::endl;
    std::cout << "Please input contact data." << std::endl;
    std::cout << "First Name:" << std::endl;
    if (!Utils::WrapGetLine(&(this->first_name_))
        || !this->IsValidName(this->first_name_)) {
        return false;
    }
    std::cout << "Last Name:" << std::endl;
    if (!Utils::WrapGetLine(&(this->last_name_))
        || !this->IsValidName(this->last_name_)) {
        return false;
    }
    std::cout << "Nickname:" << std::endl;
    if (!Utils::WrapGetLine(&(this->nickname_))
        || !this->IsValidName(this->nickname_)) {
        return false;
    }
    std::cout << "Phone Number:" << std::endl;
    if (!Utils::WrapGetLine(&(this->phone_number_))
        || !this->IsValidPhoneNumber(this->phone_number_)) {
        return false;
    }
    std::cout << "Darkest Secret:" << std::endl;
    if (!Utils::WrapGetLine(&(this->darkest_secret_))) {
        return false;
    }
    return true;
}

void    Contact::Copy(const Contact item) {
    this->first_name_ = item.first_name_;
    this->last_name_ = item.last_name_;
    this->nickname_ = item.nickname_;
    this->phone_number_ = item.phone_number_;
    this->darkest_secret_ = item.darkest_secret_;
}

void    Contact::PrintFieldFixedWidth(
    ContactFieldName field,
    const size_t width,
    char padding_char,
    std::string abbrev_str
) {
    const std::string *field_value = this->GetField(field);
    if (field_value == NULL) { return; }
    Utils::PrintFieldFixedWidth(*field_value, width, padding_char, abbrev_str);
}

void    Contact::PrintInfo() {
    std::size_t row_width = Utils::MaxLength((std::string[]){
        "First Name: ",
        "Last Name: ",
        "Nickame: ",
        "Phone Number: ",
        "Darkest Secret: ",
    }, 5) + Utils::MaxLength((std::string[]){
        this->first_name_,
        this->last_name_,
        this->nickname_,
        this->phone_number_,
        this->darkest_secret_,
    }, 5);
    Utils::PrintLinesWithinRect(
        kInfoTopFrame,
        kInfoMidFrame,
        kInfoBottomFrame,
        (std::string[]){
            Utils::WidenString("First Name: "    , this->first_name_, row_width),
            Utils::WidenString("Last Name: "     , this->last_name_, row_width),
            Utils::WidenString("Nickame: "       , this->nickname_, row_width),
            Utils::WidenString("Phone Number: "  , this->phone_number_, row_width),
            Utils::WidenString("Darkest Secret: ", this->darkest_secret_, row_width),
        }, 5, 1);
}

std::string   *Contact::GetField(ContactFieldName field) {
    switch (field) {
        case kFirstName:
            return &(this->first_name_);
        case kLastName:
            return &(this->last_name_);
        case kNickname:
            return &(this->nickname_);
        case kPhoneNumber:
            return &(this->phone_number_);
        case kDarkestSecret:
            return &(this->darkest_secret_);
    }
    return NULL;
}

bool    Contact::IsValidName(std::string val) {
    if (val.length() == 0) {
        return false;
    }
    return true;
}

bool    Contact::IsValidPhoneNumber(std::string val) {
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

bool    Contact::IsValidSecret(std::string val) {
    if (val.length() == 0) {
        return false;
    }
    return true;
}
