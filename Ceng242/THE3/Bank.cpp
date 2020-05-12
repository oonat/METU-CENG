#include "Bank.h"

Bank::Bank(){
_bank_name = "not_defined";
_user_count = 0;
_users = nullptr;
}

Bank::Bank(std::string bank_name, Account* const users, int user_count){
_bank_name = bank_name;
_user_count = user_count;
if(user_count == 0)
	_users = nullptr;
else{
_users = new Account[_user_count];

for(int i=0; i<_user_count; i++)
	_users[i] = users[i];
}

}


Bank::~Bank(){

delete [] _users;

}

Bank::Bank(const Bank& rhs){
_bank_name = rhs._bank_name;
_user_count = rhs._user_count;
if(rhs._user_count == 0)
	_users = nullptr;
else{
_users = new Account[_user_count];

for(int i=0; i<_user_count; i++)
	_users[i] = rhs._users[i];
}
}


Bank& Bank::operator+=(const Bank& rhs){

if(rhs._users == nullptr)
	return *this;

for(int i=0; i<rhs._user_count; i++)
	*this+= rhs._users[i];

return *this;
}


Bank& Bank::operator+=(const Account& new_acc){

for(int i = 0 ; i<_user_count; i++)
	if(_users[i] == new_acc){
		_users[i]+= new_acc;
		return *this;
	}

Bank tmp(*this);
delete [] _users;

_user_count+=1;
_users = new Account[_user_count];

for(int i=0; i<_user_count-1; i++)
	_users[i] = tmp._users[i];

_users[_user_count-1] = new_acc;

return *this;

}



Account& Bank::operator[](int account_id){
for(int i=0; i<_user_count; i++)
	if(_users[i] == account_id)
		return _users[i];

return _users[0];
}



bool eligible_helper(Account& user){

struct tm end_date = {0};
end_date.tm_year = 119; end_date.tm_mon = 1; end_date.tm_mday = 1;

double arr[12];
double counter = 0;

for(int i = 0; i<12; i++){
	arr[i] = user.balance(mktime(&end_date)) - counter;
	counter = user.balance(mktime(&end_date));
	end_date.tm_mon+=1;
}

for(int i = 0; i<11; i++){
	if(arr[i]<0 && arr[i+1]<0)
		return false;
}

return true;

}




std::ostream& operator<<(std::ostream& os, const Bank& bank){

double tot_balance = 0;
int eligible_num = 0;

for(int i=0; i<bank._user_count; i++){
	tot_balance+= bank._users[i].balance();
	if(eligible_helper(bank._users[i]))
		eligible_num++;
}

os<<bank._bank_name<<"\t"<<eligible_num<<"\t"<<tot_balance<<std::endl;

return os;

}