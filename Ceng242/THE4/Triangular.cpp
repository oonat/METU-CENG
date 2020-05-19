#include "Triangular.h"


Triangular::Triangular(int id_param, const vector<Wall*>& edges_param, const NucleoBase& rna_param):MicroOrganism(id_param, edges_param){

head_rna = new NucleoBase(rna_param);

}



Triangular::~Triangular(){

std::vector<Wall*>::iterator it;

for(it = edge_list.begin(); it != edge_list.end(); ++it){
	delete *it;
}

edge_list.clear();

delete head_rna;

}



void Triangular::ConnectToCell(Cell* const given_cell){

if(this->DoesFitInto(*given_cell)){

Wall* new_wall;

connected_cell = given_cell;

std::vector<Wall*>::iterator it;
std::vector<Wall*>::const_iterator const_it;

for(it = edge_list.begin(); it != edge_list.end(); ++it){
	delete *it;
}

edge_list.clear();

for(const_it = given_cell->GetCellWall().begin(); const_it != given_cell->GetCellWall().end(); ++const_it){
	new_wall = (*const_it)->Clone();
	edge_list.push_back(new_wall);
}


}

}



bool Triangular::DoesFitInto(const Cell& given_cell) const{

bool doesfit = true;
vector<float> lcell;
vector<float> lmicro;

Cell* tmp = new Cell(given_cell);
tmp->StrengthenCellWall();

if((tmp->GetCellWall()).size() == 3){

	for(int i = 0; i<3; i++){
		if(dynamic_cast<const CurvyWall*>((tmp->GetCellWall())[i]) != NULL)
			doesfit = false;
			break;
		}

	for(int k = 0; k<3; k++){
		lcell.push_back((tmp->GetCellWall())[k]->GetLength());
		lmicro.push_back((edge_list)[k]->GetLength());
	}

	float temporary;

	for(int j = 0; j<2; j++){
		for(int t = 0; t<2-j; t++){
			if(lcell[t] > lcell[t+1]){
				temporary = lcell[t];
				lcell[t] = lcell[t+1];
				lcell[t+1] = temporary;
			}

			if(lmicro[t] > lmicro[t+1]){
				temporary = lmicro[t];
				lmicro[t] = lmicro[t+1];
				lmicro[t+1] = temporary;
			}

		}
	}

	for(int k = 0; k<3; k++){
		if(fabs(lcell[k] - lmicro[k]) >= EPSILON){
			doesfit = false;
			break;
		}
	}

	
	

}else{
	doesfit = false;
}


delete tmp;

return doesfit;

}



void Triangular::React(){

delete connected_cell;

connected_cell = NULL;
}



const NucleoBase& Triangular::GetRNA() const{
return *head_rna;
}



void Triangular::Mutate(Triangular& rhs){


	NucleoBase* rna_last = head_rna->GetLast();
	NucleoBase* head_rhs = rhs.head_rna;
	NucleoBase* last_rhs = (rhs.head_rna)->GetLast();


	// find starting
	NucleoBase* tmp = head_rna;
	NucleoBase* tmp_rhs = head_rhs;

	while(tmp->nbase == tmp_rhs->nbase){
		tmp = tmp->next;
		tmp_rhs = tmp_rhs->next;
	}

	NucleoBase* startpoint = tmp;
	NucleoBase* startpoint_rhs = tmp_rhs;



	// find end
	tmp = rna_last;
	tmp_rhs = last_rhs;

	while(tmp->nbase == tmp_rhs->nbase){
		tmp = tmp->prev;
		tmp_rhs = tmp_rhs->prev;
	}

	NucleoBase* endpoint = tmp;
	NucleoBase* endpoint_rhs = tmp_rhs;




	// build start
	tmp = head_rna->next;

	NucleoBase* new_headrna = new NucleoBase(head_rna->nbase,NULL);
	NucleoBase* new_headrna_rhs = new NucleoBase(head_rhs->nbase,NULL);

	NucleoBase* prev_this = new_headrna;
	NucleoBase* prev_rhs = new_headrna_rhs;

	NucleoBase* newbase;
	NucleoBase* newbase_rhs;

	while(tmp != startpoint){
		newbase = new NucleoBase(tmp->nbase, prev_this);
		newbase_rhs = new NucleoBase(tmp->nbase, prev_rhs);

		prev_this->next = newbase;
		prev_rhs->next = newbase_rhs;

		prev_this = newbase;
		prev_rhs = newbase_rhs;

		tmp = tmp->next;
	}



	// build end
	tmp = endpoint->next->next;

	NucleoBase* connectpoint = new NucleoBase(endpoint->next->nbase,NULL);
	NucleoBase* connectpoint_rhs = new NucleoBase(endpoint_rhs->next->nbase,NULL);

	prev_this = connectpoint;
	prev_rhs = connectpoint_rhs;


	while(tmp != NULL){
		newbase = new NucleoBase(tmp->nbase, prev_this);
		newbase_rhs = new NucleoBase(tmp->nbase, prev_rhs);

		prev_this->next = newbase;
		prev_rhs->next = newbase_rhs;

		prev_this = newbase;
		prev_rhs = newbase_rhs;

		tmp = tmp->next;
	}



	// traverse
	tmp = startpoint;
	tmp_rhs = startpoint_rhs;

	prev_this = new_headrna->GetLast();
	prev_rhs =	new_headrna_rhs->GetLast();

	while(tmp != endpoint->next && tmp_rhs != endpoint_rhs->next){
		if((tmp->nbase == 'G' && tmp_rhs->nbase == 'S') || (tmp->nbase == 'S' && tmp_rhs->nbase == 'G') || (tmp->nbase == 'A' && tmp_rhs->nbase == 'U') || (tmp->nbase == 'U' && tmp_rhs->nbase == 'A')){
			newbase = new NucleoBase(tmp_rhs->nbase, prev_this);
			newbase_rhs = new NucleoBase(tmp->nbase, prev_rhs);

			prev_this->next = newbase;
			prev_rhs->next = newbase_rhs;

			prev_this = newbase;
			prev_rhs = newbase_rhs;

		}
		tmp = tmp->next;
		tmp_rhs = tmp_rhs->next;
	}

	prev_this->next = connectpoint;
	prev_rhs->next = connectpoint_rhs;

	connectpoint->prev = prev_this;
	connectpoint_rhs->prev = prev_rhs;

	delete head_rna;
	delete head_rhs;

	head_rna = new_headrna;
	rhs.head_rna = new_headrna_rhs;

}
