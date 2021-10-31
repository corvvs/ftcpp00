#include "PhoneBook.hpp"

PhoneBook::PhoneBook(): total_index_(0), store_index_(0)
{}

void    PhoneBook::Start() {
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
            this->ExecAdd();
        } else if (read_str == "SEARCH") {
            this->ExecSearch();
        } else if (read_str.length() > 0) {
            this->PrintUsageHelp();
        }
    }
}

void    PhoneBook::ExecAdd() {
    Contact temp = Contact();
    if (!temp.SetFields()) {
        return;
    }
    temp.PrintInfo();
    this->contacts_[this->store_index_].Copy(temp);
    std::cout
        << "accepted your contact, and stored into index "
        << this->store_index_ + 1
        << std::endl;
    this->store_index_ = (this->store_index_ + 1) % kMaxContactNumber;
    this->total_index_ += 1;
}

void    PhoneBook::ExecSearch() {
    this->PrintSearchTable();
    this->SearchByIndex();
}

void    PrintTableSeparatorRow(const std::size_t col_len) {
    std::cout << "+";
    for (std::size_t i = 0; i < 4; i += 1) {
        Utils::PrintFieldFixedWidth("", col_len, '-', ".");
        std::cout << "+";
    }
    std::cout << std::endl;
}

void    PhoneBook::PrintSearchTable() {
    const std::size_t col_len = 10;
    const std::string col_names[4] = {
        "index", "first name", "last name", "nickname",
    };
    std::cout << std::endl;
    PrintTableSeparatorRow(col_len);
    std::cout << "|";
    for (std::size_t i = 0; i < 4; i += 1) {
        Utils::PrintFieldFixedWidth(col_names[i], col_len, ' ', ".");
        std::cout << "|";
    }
    std::cout << std::endl;
    PrintTableSeparatorRow(col_len);
    if (this->total_index_ == 0) {
        return;
    }
    std::size_t item_num = (this->total_index_ >= kMaxContactNumber) ? kMaxContactNumber : this->total_index_;
    for (std::size_t k = 0; k < item_num; k += 1) {
        std::size_t item_index = (this->total_index_ + kMaxContactNumber - item_num + k) % kMaxContactNumber;
        Contact item = this->contacts_[item_index];
        std::cout << "|";
        std::stringstream transformer;
        transformer << k + 1;
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
    PrintTableSeparatorRow(col_len);
}

void    PhoneBook::SearchByIndex() {
    std::string receiver;
    std::size_t index;
    std::size_t item_num = (this->total_index_ >= kMaxContactNumber) ? kMaxContactNumber : this->total_index_;
    std::cout
        << "enter an index("
        << 1 << "-" << item_num
        << ") to show detailed info, or type \"q\" to quit: ";
    while (true) {
        if (!Utils::WrapGetLine(&receiver) || receiver == "q") {
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
    const std::size_t offset = this->total_index_ - item_num;
    const std::size_t actual_index = (index - 1 + kMaxContactNumber - offset) % kMaxContactNumber;
    this->contacts_[actual_index].PrintInfo();
}

void    PhoneBook::PrintUsageHelp() {
    std::string command_names[] = {
        "ADD: ",
        "SEARCH: ",
        "EXIT: ",
    };
    std::string command_descs[] = {
        "input new contact.",
        "list and show one from contacts.",
        "finish.",
    };
    std::size_t row_width = Utils::MaxLength(command_names, 3)
        + Utils::MaxLength(command_descs, 3);
    Utils::PrintLinesWithinRect(
        kUsageTopFrame,
        kUsageMidFrame,
        kUsageBottomFrame,
        (std::string[]){
            "[Available Commands]",
            Utils::WidenString(command_names[0], command_descs[0], row_width),
            Utils::WidenString(command_names[1], command_descs[1], row_width),
            Utils::WidenString(command_names[2], command_descs[2], row_width),
        }, 4, 1);
}
