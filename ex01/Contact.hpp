#ifndef CPP00_EX01_CONTACT_HPP_
# define CPP00_EX01_CONTACT_HPP_

# include <string>
# include <iostream>
# include <cstddef>
# include <sstream>
# include "Utils.hpp"

enum ContactFieldName {
    kFirstName,
    kLastName,
    kNickname,
    kPhoneNumber,
    kDarkestSecret
};

class Contact {
    public:
        Contact(void);

        bool    SetFields(void);
        void    Copy(const Contact item);
        void    PrintFieldFixedWidth(
            ContactFieldName field,
            const size_t width,
            char padding_char,
            std::string abbrev_str
        );
        void    PrintInfo(std::size_t index);

    private:
        static const std::string kInfoTopFrame[3];
        static const std::string kInfoMidFrame[3];
        static const std::string kInfoBottomFrame[3];

        std::string first_name_;
        std::string last_name_;
        std::string nickname_;
        std::string phone_number_;
        std::string darkest_secret_;

        std::string *GetField(ContactFieldName field);
};

#endif
