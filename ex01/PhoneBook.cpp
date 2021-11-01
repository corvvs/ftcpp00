#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void): total_index_(0), store_index_(0)
{}

void    PhoneBook::Start(void) {
    std::string read_str;

    while (true) {
        std::cout << "enter a command: ";
        if (!Utils::WrapGetLine(&read_str)) {
            std::cout << std::endl;
            exit(1);
        }
        if (read_str == "EXIT") {
            std::cout << std::endl;
            std::cout << "Thank you for using." << std::endl;
            exit(0);
        } else if (read_str == "ADD") {
            ExecAdd();
        } else if (read_str == "SEARCH") {
            ExecSearch();
        } else if (read_str.length() > 0) {
            PrintUsageHelp();
        }
    }
}

void    PhoneBook::ExecAdd(void) {
    Contact temp = Contact();
    if (!temp.SetFields()) {
        return;
    }
    contacts_[store_index_].Copy(temp);
    std::cout
        << "accepted your contact:"
        << std::endl;
    temp.PrintInfo(store_index_ + 1);
    store_index_ = (store_index_ + 1) % kMaxContactNumber;
    total_index_ += 1;
}

void    PhoneBook::ExecSearch(void) {
    PrintSearchTable();
    if (total_index_ == 0) {
        return;
    }
    SearchByIndex();
}

void    PrintTableSeparatorRow(const std::size_t col_len, bool with_crosspoint) {
    std::cout << "+";
    for (std::size_t i = 0; i < 4; i += 1) {
        Utils::PrintFieldFixedWidth("", col_len, '-', ".");
        if (with_crosspoint) {
            std::cout << "+";
        } else {
            std::cout << "-";
        }
    }
    std::cout << std::endl;
}

void    PhoneBook::PrintSearchTable(void) {
    const std::size_t col_len = 10;
    const std::string col_names[4] = {
        "index", "first name", "last name", "nickname",
    };
    std::cout << std::endl;
    PrintTableSeparatorRow(col_len, true);
    std::cout << "|";
    for (std::size_t i = 0; i < 4; i += 1) {
        Utils::PrintFieldFixedWidth(col_names[i], col_len, ' ', ".");
        std::cout << "|";
    }
    std::cout << std::endl;
    PrintTableSeparatorRow(col_len, true);
    if (total_index_ == 0) {
        std::cout << "|";
        std::cout << Utils::CenterString("** No Contacts Yet **", 4 * (col_len + 1) - 1);
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
        ContactFieldName fields[] = {
            kFirstName,
            kLastName,
            kNickname
        };
        for (std::size_t i = 1; i < 4; i += 1) {
            item.PrintFieldFixedWidth(fields[i - 1], col_len, ' ', ".");
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    PrintTableSeparatorRow(col_len, true);
}

void    PhoneBook::SearchByIndex(void) {
    std::string receiver;
    std::size_t index;
    std::size_t item_num = (total_index_ >= kMaxContactNumber) ? kMaxContactNumber : total_index_;
    std::cout
        << "enter an index("
        << 1 << "-" << item_num
        << ") to show detailed info, or type \".q\" to quit: ";
    while (true) {
        if (!Utils::WrapGetLine(&receiver)) {
            return;
        }
        if (receiver == ".q") {
            return;
        }
        if (receiver.length() >= 2) {
            std::cout << std::endl << "please enter an integer: ";
            continue;
        }
        bool accepted = true;
        for (std::size_t i = 0; i < receiver.length(); i += 1) {
            if (!isdigit(receiver[i])) {
                std::cout << std::endl
                    << 1 << "-" << item_num
                    << " please enter an integer: ";
                accepted = false;
                break;
            }
        }
        if (!accepted) {
            continue;
        }
        std::stringstream transformer;
        transformer << receiver;
        transformer >> index;
        if (index < 1 || item_num < index) {
            std::cout << std::endl
                << "please enter an index in range "
                << 1 << "-" << item_num
                << ": ";
            continue;
        }
        break;
    }
    std::cout << std::endl;
    const std::size_t offset = total_index_ - item_num;
    const std::size_t actual_index = (index - 1 + kMaxContactNumber - offset) % kMaxContactNumber;
    contacts_[actual_index].PrintInfo(index);
}

void    PhoneBook::PrintUsageHelp(void) {
    std::string command_names[] = {
        "ADD: ",
        "SEARCH: ",
        "EXIT: ",
    };
    std::string command_descs[] = {
        "input a new contact",
        "list and show one from stored",
        "finish this program",
    };
    std::size_t row_width = Utils::MaxLength(command_names, 3)
        + Utils::MaxLength(command_descs, 3);
    Utils::PrintLinesWithinRect(
        kUsageTopFrame,
        kUsageMidFrame,
        kUsageBottomFrame,
        (std::string[]){
            Utils::CenterString("** Available Commands **", row_width),
            "",
            Utils::WidenString(command_names[0], command_descs[0], row_width),
            Utils::WidenString(command_names[1], command_descs[1], row_width),
            Utils::WidenString(command_names[2], command_descs[2], row_width),
        }, 5, 1);
}
