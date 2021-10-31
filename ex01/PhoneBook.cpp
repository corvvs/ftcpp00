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
