#include "PhoneBook.hpp"

const std::string PhoneBook::kCommands[] = {
    "ADD",
    "SEARCH",
    "EXIT"
};
const CommandFunc PhoneBook::kCommandFuncs[] = {
    &PhoneBook::ExecAdd,
    &PhoneBook::ExecSearch,
    &PhoneBook::ExecExit,
};
const std::string PhoneBook::kUsageTopFrame[3]      = {"┌", "─", "┐"};
const std::string PhoneBook::kUsageMidFrame[3]      = {"│", " ", "│"};
const std::string PhoneBook::kUsageBottomFrame[3]   = {"└", "─", "┘"};

bool    IsValidIndex(const std::string& val) {
    if (val.length() >= 2) {
        Utils::PrintWarning("too long");
        return false;
    }
    if (val.length() == 0) {
        Utils::PrintWarning("blank is not acceptable");
        return false;
    }
    for (std::size_t i = 0; i < val.length(); i += 1) {
        if (!isdigit(val[i])) {
            Utils::PrintWarning("only accepts '0-9'");
            return false;
        }
    }
    return true;
}

PhoneBook::PhoneBook(void): total_index_(0), store_index_(0) {}

void    PhoneBook::Start(void) {
    std::string read_str;
    while (true) {
        std::cout << "enter a command: ";
        if (!Utils::WrapGetLine(&read_str)) {
            std::cout << std::endl;
            exit(1);
        }
        if (read_str.length() == 0) {
            continue;
        }
        DispatchCommand(read_str);
    }
}

void    PhoneBook::DispatchCommand(const std::string command) {
    for (std::size_t i = 0; i < kCommandNumber; i += 1) {
        if (command == PhoneBook::kCommands[i]) {
            (this->*PhoneBook::kCommandFuncs[i])();
            return;
        }
    }
    PrintUsageHelp();
}

void    PhoneBook::ExecAdd(void) {
    Contact temp = Contact();
    if (!temp.ScanFields()) {
        return;
    }
    contacts_[store_index_].CopyFrom(temp);
    Utils::PrintAffirmative("accepted your contact:");
    temp.PrintDetailedInfo(0);
    store_index_ = (store_index_ + 1) % kMaxContactNumber;
    total_index_ += 1;
}

void    PhoneBook::ExecSearch(void) {
    PrintSearchTable();
    if (total_index_ == 0) {
        return;
    }
    const std::size_t index = ScanIndex();
    if (index == 0) {
        return;
    }
    SearchByIndex(index);
}

void    PhoneBook::ExecExit(void) {
    std::cout << std::endl;
    std::cout << "Thank you for using." << std::endl;
    exit(0);
}

void    PrintTableSeparatorRow(const std::size_t col_len, bool with_crosspoint) {
    const std::size_t col_num = 1 + kTableFieldNumber;
    std::cout << "o";
    for (std::size_t i = 0; i < col_num; i += 1) {
        Utils::PrintFieldFixedWidth("", col_len, '-', ".");
        if (i + 1 < col_num) {
            if (with_crosspoint) {
                std::cout << "o";
            } else {
                std::cout << "-";
            }
        }
    }
    std::cout << "o";
    std::cout << std::endl;
}

void    PhoneBook::PrintSearchTable(void) {
    const std::size_t col_len = 10;
    const std::string col_names[1 + kTableFieldNumber] = {
        "index", "first name", "last name", "nickname",
    };
    std::cout << std::endl;
    PrintTableSeparatorRow(col_len, true);
    std::cout << "|";
    for (std::size_t i = 0; i < 1 + kTableFieldNumber; i += 1) {
        Utils::PrintFieldFixedWidth(col_names[i], col_len, ' ', ".");
        std::cout << "|";
    }
    std::cout << std::endl;
    PrintTableSeparatorRow(col_len, true);
    if (total_index_ == 0) {
        std::cout << "|";
        std::cout << Utils::CenterString("** No Contacts Yet **", (1 + kTableFieldNumber) * (col_len + 1) - 1);
        std::cout << "|";
        std::cout << std::endl;
        PrintTableSeparatorRow(col_len, false);
        return;
    }
    std::size_t item_num = (total_index_ >= kMaxContactNumber) ? kMaxContactNumber : total_index_;
    for (std::size_t k = 0; k < item_num; k += 1) {
        std::size_t item_index = (total_index_ + kMaxContactNumber - item_num + k) % kMaxContactNumber;
        Contact item = contacts_[item_index];
        std::stringstream transformer;
        transformer << k + 1;
        std::cout << "|";
        Utils::PrintFieldFixedWidth(transformer.str(), col_len, ' ', ".");
        std::cout << "|";
        ContactFieldName table_fields[] = {
            kFirstName,
            kLastName,
            kNickname
        };
        for (std::size_t i = 0; i < kTableFieldNumber; i += 1) {
            Utils::PrintFieldFixedWidth(
                item.GetField(table_fields[i]),
                col_len, ' ', ".");
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    PrintTableSeparatorRow(col_len, true);
}

std::size_t PhoneBook::ScanIndex(void) {
    std::string receiver;
    std::size_t index;
    const std::size_t item_num = 
        (total_index_ >= kMaxContactNumber) ? kMaxContactNumber : total_index_;
    std::stringstream joiner;
    joiner
        << "enter an index("
        << 1 << "-" << item_num
        << ") to show detailed info (or type \".q\" to quit): ";
    const std::string prompt = joiner.str();
    while (true) {
        if (!Utils::AskAndGetLine(&receiver, prompt, IsValidIndex)) {
            return 0;
        }
        std::cout << std::endl;
        std::stringstream transformer;
        transformer << receiver;
        transformer >> index;
        if (index == 0 || index > total_index_ || index > kMaxContactNumber) {
            std::cout
                << Utils::kTextYellow
                << index
                << " is out of range"
                << Utils::kTextReset
                << std::endl;
            continue;
        }
        break;
    }
    return index;
}


void    PhoneBook::SearchByIndex(const std::size_t index) {
    const std::size_t item_num = 
        (total_index_ >= kMaxContactNumber) ? kMaxContactNumber : total_index_;
    const std::size_t offset = total_index_ - item_num;
    const std::size_t actual_index = (index - 1 + kMaxContactNumber - offset) % kMaxContactNumber;
    contacts_[actual_index].PrintDetailedInfo(index);
}

void    PhoneBook::PrintUsageHelp(void) {
    const std::string command_names[] = {
        PhoneBook::kCommands[0] + ": ",
        PhoneBook::kCommands[1] + ": ",
        PhoneBook::kCommands[2] + ": "
    };
    const std::string command_descs[] = {
        "input a new contact",
        "list and show one from stored",
        "finish this program",
    };
    std::size_t name_len = Utils::MaxLengthOf(command_names, kCommandNumber);
    std::size_t desc_len = Utils::MaxLengthOf(command_descs, kCommandNumber);
    std::string str_list[] = {
        Utils::CenterString("** Available Commands **", name_len + desc_len),
        "",
        Utils::AlignString(command_names[0], name_len) + Utils::AlignString(command_descs[0], desc_len, true),
        Utils::AlignString(command_names[1], name_len) + Utils::AlignString(command_descs[1], desc_len, true),
        Utils::AlignString(command_names[2], name_len) + Utils::AlignString(command_descs[2], desc_len, true),
    };
    Utils::PrintLinesWithinRect(
        PhoneBook::kUsageTopFrame,
        PhoneBook::kUsageMidFrame,
        PhoneBook::kUsageBottomFrame,
        str_list,
        2 + kCommandNumber, 1);
}
