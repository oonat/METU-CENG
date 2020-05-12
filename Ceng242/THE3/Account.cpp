#include "Account.h"

Account::Account(){
_id = -1;
_activity = nullptr;
_monthly_activity_frequency = nullptr;
}



void swap_helper(Transaction* t1, Transaction* t2){
	Transaction tmp = *t1;
	*t1 = *t2;
    *t2 = tmp;
}


void bubblesort_helper(Transaction* source, int length){
	for(int i = 0; i < length-1; i++){
		for(int j = 0; j < length-i-1; j++){
			if(source[j] > source[j+1])
				swap_helper(&source[j], &source[j+1]);
		}
	}
}



Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
_id = id;

if(activity == nullptr || monthly_activity_frequency == nullptr){

_activity = nullptr;
_monthly_activity_frequency = nullptr;

}else{
_monthly_activity_frequency = new int[12];
_activity = new Transaction*[12];

for(int i=0; i<12; i++)
	_monthly_activity_frequency[i] = monthly_activity_frequency[i];

for(int i=0; i<12; i++){
	if(_monthly_activity_frequency[i] == 0)
		_activity[i] = nullptr;
	else{
	_activity[i] = new Transaction[_monthly_activity_frequency[i]];
	for(int k=0; k<_monthly_activity_frequency[i]; k++)
		_activity[i][k] = activity[i][k];
}
}


//sort activities
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);
}

}



Account::~Account(){


//delete subarrays of activity
if(_activity != nullptr){
	for(int i = 0; i<12; i++)
		delete [] _activity[i];
}

//delete activity array
if(_activity != nullptr)
	delete [] _activity;


// delete freq array
if(_monthly_activity_frequency != nullptr)
	delete [] _monthly_activity_frequency;


}




Account::Account(const Account& rhs){
_id = rhs._id;

if(rhs._activity == nullptr || rhs._monthly_activity_frequency == nullptr){
_activity = nullptr;
_monthly_activity_frequency = nullptr;

}else{
_monthly_activity_frequency = new int[12];
_activity = new Transaction*[12]; 

// get frequency array from rhs
for(int i = 0; i<12; i++)
	_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];

// allocate and write activity for each month
for(int i = 0; i<12; i++){
	if(_monthly_activity_frequency[i] == 0)
		_activity[i] = nullptr;
	else{
	_activity[i] = new Transaction[_monthly_activity_frequency[i]];
	for(int k = 0; k < _monthly_activity_frequency[i]; k++)
		_activity[i][k] = rhs._activity[i][k];
}
}

// sort activities
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);

}

}



Account::Account(const Account& rhs, time_t start_date, time_t end_date){
_id = rhs._id;

if(rhs._activity == nullptr || rhs._monthly_activity_frequency == nullptr){
_activity = nullptr;
_monthly_activity_frequency = nullptr;

}else{
_monthly_activity_frequency = new int[12];
_activity = new Transaction*[12]; 

int counter, freq_count;

// calculate monthly freqs
for(int i = 0; i<12; i++){
	freq_count = 0;
	for(int k = 0; k < rhs._monthly_activity_frequency[i]; k++){
		if(rhs._activity[i][k]<end_date && rhs._activity[i][k]>start_date)
			freq_count++;
	}
	_monthly_activity_frequency[i] = freq_count;	
}

for(int i = 0; i<12; i++){
	if(_monthly_activity_frequency[i] == 0)
		_activity[i] = nullptr;
	else{
	counter = 0;
	_activity[i] = new Transaction[_monthly_activity_frequency[i]];
	for(int k = 0; k < rhs._monthly_activity_frequency[i]; k++){
		if(rhs._activity[i][k]<end_date && rhs._activity[i][k]>start_date)
			_activity[i][counter++] = rhs._activity[i][k];
	}
	}
}


// sort activites
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);

}

}


Account::Account(Account&& rhs){

_id = rhs._id;
_monthly_activity_frequency = rhs._monthly_activity_frequency;
_activity = rhs._activity; 

if((_activity != nullptr) && (_monthly_activity_frequency != nullptr)){
// sort activities
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);
}

rhs._monthly_activity_frequency = nullptr;
rhs._activity = nullptr;

}




Account& Account::operator=(Account&& rhs){

if(this == &rhs)
	return *this;

if(_activity != nullptr)
	for(int i=0; i<12; i++)
		delete [] _activity[i];

if(_activity != nullptr)
	delete [] _activity;

if(_monthly_activity_frequency != nullptr)
	delete [] _monthly_activity_frequency;

_id = rhs._id;

_activity = rhs._activity;
_monthly_activity_frequency = rhs._monthly_activity_frequency;

if((_activity != nullptr) && (_monthly_activity_frequency != nullptr)){
// sort activities
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);
}

rhs._activity = nullptr;
rhs._monthly_activity_frequency = nullptr;


return *this;
}




Account& Account::operator=(const Account& rhs){


if(this == &rhs)
	return *this;


if(_activity != nullptr)
	for(int i = 0; i<12; i++)
		delete [] _activity[i];

if(_activity != nullptr)
	delete [] _activity;

if(_monthly_activity_frequency != nullptr)
	delete [] _monthly_activity_frequency;



_id = rhs._id;

if(rhs._activity == nullptr || rhs._monthly_activity_frequency == nullptr){
_activity = nullptr;
_monthly_activity_frequency = nullptr;

}else{

_monthly_activity_frequency = new int[12];
_activity = new Transaction*[12]; 

// get frequency array from rhs
for(int i = 0; i<12; i++)
	_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];

// allocate and write activity for each month
for(int i = 0; i<12; i++){
	if(_monthly_activity_frequency[i] == 0)
		_activity[i] = nullptr;
	else{
	_activity[i] = new Transaction[_monthly_activity_frequency[i]];
	for(int k = 0; k < _monthly_activity_frequency[i]; k++)
		_activity[i][k] = rhs._activity[i][k];
}
}

// sort activites
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);

}

return *this;

}




bool Account::operator==(const Account& rhs) const{
	return _id == rhs._id;
}

bool Account::operator==(int id) const{
	return _id == id;
}


Account& Account::operator+=(const Account& rhs){

int counter;

// if rhs is null
if(rhs._activity == nullptr || rhs._monthly_activity_frequency == nullptr)
	return *this;

// if this is null
if(_activity == nullptr || _monthly_activity_frequency == nullptr){
	int tmp = _id;
	*this = rhs;
	_id = tmp;
	return *this;
}



Account temp(*this);

if(_activity != nullptr){
	for(int i = 0; i<12; i++)
		delete [] _activity[i];
}

if(_activity != nullptr)
	delete [] _activity;

if(_monthly_activity_frequency != nullptr)
	delete [] _monthly_activity_frequency;


_monthly_activity_frequency = new int[12];
_activity = new Transaction*[12];


if( this == &rhs){

for(int i = 0; i<12; i++)
	_monthly_activity_frequency[i]= 2*temp._monthly_activity_frequency[i];

for(int i = 0; i<12; i++){
	if(_monthly_activity_frequency[i] == 0)
		_activity[i] = nullptr;
	else{
	_activity[i] = new Transaction[_monthly_activity_frequency[i]];
    counter = 0;

	for(int j = 0; j<temp._monthly_activity_frequency[i]; j++){
		_activity[i][counter++] = temp._activity[i][j];
		_activity[i][counter++] = temp._activity[i][j];
	}

}
}


}else{


for(int i = 0; i<12; i++)
	_monthly_activity_frequency[i]= temp._monthly_activity_frequency[i] + rhs._monthly_activity_frequency[i];


for(int i = 0; i<12; i++){
	if(_monthly_activity_frequency[i] == 0)
		_activity[i] = nullptr;
	else{
	_activity[i] = new Transaction[_monthly_activity_frequency[i]];
    counter = 0;

	for(int t1 = 0; t1<rhs._monthly_activity_frequency[i]; t1++)
		_activity[i][counter++] = rhs._activity[i][t1];

	for(int t2 = 0; t2<temp._monthly_activity_frequency[i]; t2++)
		_activity[i][counter++] = temp._activity[i][t2];
}
}

}

// sort activites
for(int i = 0; i < 12; i++)
	bubblesort_helper(_activity[i], _monthly_activity_frequency[i]);



return *this;
}



double Account::balance(){
	double counter = 0;
	for(int i=0; i<12; i++){
		for(int k=0; k<_monthly_activity_frequency[i]; k++)
			counter= _activity[i][k]+counter;
	}

	return counter;
}

double Account::balance(time_t end_date){
	double counter = 0;
	for(int i=0; i<12; i++){
		for(int k=0; k<_monthly_activity_frequency[i]; k++){
			if(_activity[i][k]<end_date)
				counter= _activity[i][k]+counter;
		}
	}

	return counter;
}


double Account::balance(time_t start_date, time_t end_date){
	double counter = 0;
	for(int i=0; i<12; i++){
		for(int k=0; k<_monthly_activity_frequency[i]; k++){
			if(_activity[i][k]<end_date && _activity[i][k]>start_date)
				counter= _activity[i][k]+counter;
		}
	}

	return counter;
}



std::ostream& operator<<(std::ostream& os, const Account& account){
	if(account._activity == nullptr || account._monthly_activity_frequency == nullptr)
		os<<-1<<std::endl;
	else{
		os<<account._id<<std::endl;
		for(int i=0; i<12; i++){
			for(int k=0; k<account._monthly_activity_frequency[i]; k++)
				os<<account._activity[i][k];
		}
	}


	return os;
}