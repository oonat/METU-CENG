#include "Cell.h"
#include "Exception.h"
#include "Tissue.h"


Cell::Cell(int id_param, const vector<Wall*>& wall_array, Tissue* tissue_param){

Wall* new_wall;
std::vector<Wall*>::const_iterator it;

cell_id = id_param;

cell_tissue = tissue_param;

for(it = wall_array.begin(); it != wall_array.end(); ++it){
	new_wall = (*it)->Clone();
	cell_wall.push_back(new_wall);
}


}

Cell::Cell(const Cell& rhs){

Wall* new_wall;
std::vector<Wall*>::const_iterator it;

cell_id = rhs.cell_id;

cell_tissue = rhs.cell_tissue;

for(it = rhs.cell_wall.begin(); it != rhs.cell_wall.end(); ++it){
	new_wall = (*it)->Clone();
	cell_wall.push_back(new_wall);
}


}



int Cell::GetCellID() const{
return cell_id;
}



Tissue* Cell::GetTissue() const{
return cell_tissue;
}



const vector<Wall*>& Cell::GetCellWall() const{
return cell_wall;
}




void Cell::RenewCellWall(vector<Wall*>& rhs){

std::vector<Wall*>::iterator it;

if(cell_wall != rhs){

// delete the old pointers
for(it = cell_wall.begin(); it != cell_wall.end(); ++it){
	delete *it;
}

cell_wall.clear();

cell_wall = rhs;
    
}
}


void Cell::StrengthenCellWall(){

vector<Wall*> new_wall;
Wall* tmp;
const Wall* plus_tmp;

std::vector<Wall*>::iterator it = cell_wall.begin();

new_wall.push_back((*it)->Clone());

for(it = cell_wall.begin()+1; it != cell_wall.end(); ++it){


	try{

	plus_tmp = &(*(new_wall.back())+*(*it));

	tmp = plus_tmp->Clone();

	delete plus_tmp;

	}catch(ApplePearException){

	tmp = (*it)->Clone();
	new_wall.push_back(tmp);
	continue;
	}

delete new_wall.back();
new_wall.pop_back();
new_wall.push_back(tmp);

}


if(new_wall.size() > 1){
it = new_wall.begin();

try{

	plus_tmp = &(*(*it)+*(new_wall.back()));

	tmp = plus_tmp->Clone();

	delete plus_tmp;

}catch(ApplePearException){
	this->RenewCellWall(new_wall);
	return;
}

delete new_wall.back();
new_wall.pop_back();
delete *it;
*it = tmp;

}

this->RenewCellWall(new_wall);


}




Cell::~Cell(){

cell_tissue->RemoveCell(*this);

std::vector<Wall*>::iterator it;

for(it = cell_wall.begin(); it != cell_wall.end(); ++it){
	delete *it;
}

cell_wall.clear();

}


ostream& operator<<(ostream& os, const Cell& cellparam){

std::vector<Wall*>::const_iterator it;

for(it = cellparam.cell_wall.begin(); it != cellparam.cell_wall.end(); ++it){
	if(it == cellparam.cell_wall.end()-1){
		os<<((*it)->GetInitialParticle());
	}else{
		os<<((*it)->GetInitialParticle())<<" - ";
	}
}

return os;
}
