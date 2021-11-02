#include "Account.hpp"

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit):
    _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
    _accountIndex = _nbAccounts;
    _nbAccounts += 1;
    _totalAmount += initial_deposit;

    // index:4;amount:1234;created
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";";
    std::cout << "amount:" << _amount << ";";
    std::cout << "created";
    std::cout << std::endl;
}

Account::Account(): 
    _accountIndex(0), _amount(0), _nbDeposits(0), _nbWithdrawals(0) {}

int     Account::getNbAccounts( void ) {
    return _nbAccounts;
}

int     Account::getTotalAmount( void ) {
    return _totalAmount;
}

int     Account::getNbDeposits( void ) {
    return _totalNbDeposits;
}

int     Account::getNbWithdrawals( void ) {
    return _totalNbWithdrawals;
}

// [eg.]
// accounts:8;total:20049;deposits:0;withdrawals:0
void    Account::displayAccountsInfos( void ) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";";
    std::cout << "total:" << _totalAmount << ";";
    std::cout << "deposits:" << _totalNbDeposits << ";";
    std::cout << "withdrawals:" << _totalNbWithdrawals;
    std::cout << std::endl;
}

// index:7;amount:8942;closed
Account::~Account( void ) {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";";
    std::cout << "amount:" << _amount << ";";
    std::cout << "closed";
    std::cout << std::endl;
}

// index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
void    Account::makeDeposit( int deposit ) {
    if (deposit <= 0) {
        return;
    }
    // index:4;p_amount:1234;deposit:87;amount:1321;nb_deposits:1
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";";
    std::cout << "p_amount:" << _amount << ";";
    _amount += deposit;
    _nbDeposits += 1;
    _totalAmount += deposit;
    _totalNbDeposits += 1;
    std::cout << "deposit:" << deposit << ";";
    std::cout << "amount:" << _amount << ";";
    std::cout << "nb_deposits:" << _nbDeposits;
    std::cout << std::endl;
}

bool    Account::makeWithdrawal( int withdrawal ) {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";";
    if (withdrawal <= 0 || _amount < withdrawal) {
        // index:0;p_amount:47;withdrawal:refused
        std::cout << "p_amount:" << _amount << ";";
        std::cout << "withdrawal:refused";
        std::cout << std::endl;
        return false;
    }
    // index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
    std::cout << "p_amount:" << _amount << ";";
    _amount -= withdrawal;
    _nbWithdrawals += 1;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals += 1;
    std::cout << "withdrawal:" << withdrawal << ";";
    std::cout << "amount:" << _amount << ";";
    std::cout << "nb_withdrawals:" << _nbWithdrawals;
    std::cout << std::endl;
    return true;
}

int     Account::checkAmount( void ) const {
    return _amount;
}

// index:0;amount:42;deposits:0;withdrawals:0
void    Account::displayStatus( void ) const {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";";
    std::cout << "amount:" << _amount << ";";
    std::cout << "deposits:" << _nbDeposits << ";";
    std::cout << "withdrawals:" << _nbWithdrawals;
    std::cout << std::endl;
}

void    Account::_displayTimestamp() {
    time_t t = time(nullptr);
    const tm* local_time = localtime(&t);
    std::cout << "[";
    std::cout << 1900 + local_time->tm_year;
    std::cout << std::setw(2) << std::setfill('0') << local_time->tm_mon + 1;
    std::cout << std::setw(2) << std::setfill('0') << local_time->tm_mday;
    std::cout << "_";
    std::cout << std::setw(2) << std::setfill('0') << local_time->tm_hour;
    std::cout << std::setw(2) << std::setfill('0') << local_time->tm_min;
    std::cout << std::setw(2) << std::setfill('0') << local_time->tm_sec;
    std::cout << "] ";
}
