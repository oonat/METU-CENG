#include "Tissue.h"



Tissue::Tissue(){

}



Tissue::Tissue(float xmin, float xmax, float ymin, float ymax){
min_x = xmin;
max_x = xmax;
min_y = ymin;
max_y = ymax;


}



Tissue::Tissue(const Tissue& rhs){


min_x = rhs.min_x;
max_x = rhs.max_x;
min_y = rhs.min_y;
max_y = rhs.max_y;

std::vector<Cell*>::const_iterator it;

for(it = rhs.cell_list.begin(); it != rhs.cell_list.end(); ++it){
	cell_list.push_back(*it);
}

}



Tissue::~Tissue(){

std::vector<Cell*>::iterator it;

int array_size = cell_list.size();

for(int i = 0; i<array_size; i++)
	delete cell_list[0];


cell_list.clear();

}



float* Tissue::GetCoordinates(){

float* arr = new float[4];

arr[0] = min_x;
arr[1] = max_x;
arr[2] = min_y;
arr[3] = max_y;

return arr;
}



void Tissue::AddCell(Cell& rhs_cell){

cell_list.push_back(&rhs_cell);

}



void Tissue::RemoveCell(Cell& rhs_cell){

std::vector<Cell*>::iterator tissue_it;

// find cell and erase
for(tissue_it = cell_list.begin(); tissue_it != cell_list.end(); ++tissue_it){
	if(*tissue_it == &rhs_cell){
		cell_list.erase(tissue_it);
		break;
	}
}


}



const Cell& Tissue::GetCell(int id_param) const{

std::vector<Cell*>::const_iterator it;

for(it = cell_list.begin(); it != cell_list.end(); ++it){
	if((*it)->GetCellID() == id_param)
		return *(*it);
}


throw DeadCellException();
}



void Tissue::Interact(const vector<MicroOrganism*>& rhs){

	std::vector<Cell*>::const_iterator cell_it;
	std::vector<MicroOrganism*>::const_iterator micro_it;

	for(micro_it = rhs.begin(); micro_it != rhs.end(); ++micro_it){
		for(cell_it = cell_list.begin(); cell_it != cell_list.end(); ++cell_it){
			if((*micro_it)->DoesFitInto(*(*cell_it))){
				(*micro_it)->ConnectToCell(*cell_it);
				break;
			}
		}
}


}



void Tissue::CreatePartitions(const vector<MicroOrganism*>&){

}



void Tissue::TreatByPlasma(Tissue){

}
