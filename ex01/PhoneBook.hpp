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

const size_t kCommandNumber = 3;
const size_t kMaxContactNumber = 8;
const size_t kTableFieldNumber = 3;

class PhoneBook;
typedef void (PhoneBook::*CommandFunc)(void);

class PhoneBook {
    public:
        PhoneBook(void);
        void        Start(void);

    private:
        static const std::string kCommands[kCommandNumber];
        static const CommandFunc kCommandFuncs[kCommandNumber];
        static const std::string kUsageTopFrame[3];
        static const std::string kUsageMidFrame[3];
        static const std::string kUsageBottomFrame[3];

        Contact     contacts_[kMaxContactNumber];
        std::size_t total_index_;
        std::size_t store_index_;

        void        DispatchCommand(const std::string command);
        void        ExecAdd(void);
        void        ExecSearch(void);
        void        ExecExit(void);

        void        PrintSearchTable(void);
        std::size_t ScanIndex(void);
        void        SearchByIndex(const std::size_t index);

        void        PrintUsageHelp(void);
};

#endif
