#ifndef CPP00_EX01_PHONEBOOK_HPP_
# define CPP00_EX01_PHONEBOOK_HPP_

# include <string>
# include <iostream>
# include <sstream>
# include <cstddef>
# include <stdlib.h>
# include <ctype.h>
# include "Contact.hpp"
# include "Utils.hpp"

const size_t kMaxContactNumber = 8;

class PhoneBook {
    public:
        PhoneBook(void);
        void        Start(void);

    private:
        Contact     contacts_[kMaxContactNumber];
        std::size_t total_index_;
        std::size_t store_index_;
        
        static const std::string kUsageTopFrame[3];
        static const std::string kUsageMidFrame[3];
        static const std::string kUsageBottomFrame[3];
        void        ExecAdd(void);
        void        ExecSearch(void);
        void        PrintSearchTable(void);
        void        SearchByIndex(void);
        void        PrintUsageHelp(void);
        void        AddContact(Contact item);
};

#endif
