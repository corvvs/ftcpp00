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
# define kUsageTopFrame     (std::string[]){"┌", "─", "┐"}
# define kUsageMidFrame     (std::string[]){"│", " ", "│"}
# define kUsageBottomFrame  (std::string[]){"└", "─", "┘"}

class PhoneBook {
    public:
        PhoneBook(void);
        void        Start(void);

    private:
        Contact     contacts_[kMaxContactNumber];
        std::size_t total_index_;
        std::size_t store_index_;

        void        ExecAdd(void);
        void        ExecSearch(void);
        void        PrintSearchTable(void);
        void        SearchByIndex(void);
        void        PrintUsageHelp(void);
        void        AddContact(Contact item);
};

#endif
