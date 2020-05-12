#include "Transaction.h"

Transaction::Transaction(){
_amount = -1;
_date = -1;
}

Transaction::Transaction(double amount, time_t date){
_amount = amount;
_date = date;
}

Transaction::Transaction(const Transaction& rhs){
_amount = rhs._amount;
_date = rhs._date;
}

bool Transaction::operator<(const Transaction& rhs) const{
return _date < rhs._date;
}

bool Transaction::operator>(const Transaction& rhs) const{
return _date > rhs._date;
}

bool Transaction::operator<(const time_t date) const{
return _date < date;
}

bool Transaction::operator>(const time_t date) const{
return _date > date;
}

double Transaction::operator+(const Transaction& rhs){
return _amount + rhs._amount;
}

double Transaction::operator+(const double add){
return _amount + add;
}

Transaction& Transaction::operator=(const Transaction& rhs){
_amount = rhs._amount;
_date = rhs._date;
return *this;
}


std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
struct tm new_time = *localtime(&transaction._date);

os<<transaction._amount<<"\t-\t"<<new_time.tm_hour<<":"<<new_time.tm_min<<":"<<new_time.tm_sec<<"-"<<new_time.tm_mday<<"/"<<(new_time.tm_mon+1)<<"/"<<(1900+new_time.tm_year)<<std::endl;
return os;
}