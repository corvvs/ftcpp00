#ifndef CPP00_EX01_CONTACT_HPP_
# define CPP00_EX01_CONTACT_HPP_

# include <string>
# include <iostream>
# include <cstddef>
# include <sstream>
# include "Utils.hpp"

const size_t kContactFieldNumber = 5;
enum ContactFieldName {
    kFirstName = 0,
    kLastName,
    kNickname,
    kPhoneNumber,
    kDarkestSecret
};

class Contact {
    public:
        Contact(void);

        bool                ScanFields(void);
        void                CopyFrom(const Contact item);
        void                PrintDetailedInfo(std::size_t index);
        const std::string&  GetField(ContactFieldName field);

    private:
        static const std::string kFields[kContactFieldNumber];
        static const std::string kInfoTopFrame[3];
        static const std::string kInfoMidFrame[3];
        static const std::string kInfoBottomFrame[3];

        std::string first_name_;
        std::string last_name_;
        std::string nickname_;
        std::string phone_number_;
        std::string darkest_secret_;

};

#endif
