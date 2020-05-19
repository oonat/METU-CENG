#include "NucleoBase.h"


NucleoBase::NucleoBase(char nbase_param, NucleoBase* prev_param){
nbase = nbase_param;
prev = prev_param;
next = NULL;

}

NucleoBase::NucleoBase(string rna_param, NucleoBase* prev_param){


this->prev = prev_param;
this->next = NULL;
nbase = rna_param[0];

if(prev_param != NULL)
	prev_param->next = this;


NucleoBase* new_base;
NucleoBase* prev_base = this;

for(int i = 1; i<rna_param.size(); i++){

new_base = new NucleoBase(rna_param[i], prev_base);
prev_base->next = new_base;
prev_base = new_base;

}

}



NucleoBase::NucleoBase(const NucleoBase& rhs){

const NucleoBase* tmp = rhs.next;

this->prev = NULL;
this->next = NULL;

nbase = rhs.nbase;

NucleoBase* new_base;
NucleoBase* prev_base = this;

while(tmp != NULL){

new_base = new NucleoBase(tmp->nbase, prev_base);
prev_base->next = new_base;
prev_base = new_base;

tmp = tmp->next;
}

}



NucleoBase::~NucleoBase(){

delete next;


}



NucleoBase* NucleoBase::GetLast(){

NucleoBase* tmp = this;

while(tmp->next != NULL)
	tmp = tmp->next;

return tmp;

}



ostream& operator<<(ostream& os, const NucleoBase& starting_nucleobase){

const NucleoBase* tmp = &starting_nucleobase;

while(tmp != NULL){
	os<<tmp->nbase;
	tmp = tmp->next;
}


return os;
}
