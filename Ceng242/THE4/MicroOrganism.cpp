#include "MicroOrganism.h"


MicroOrganism::MicroOrganism(int id_param){

microorganism_id = id_param;

connected_cell = NULL;

}



MicroOrganism::MicroOrganism(int id, const vector<Wall*>& edges){

Wall* new_wall;
std::vector<Wall*>::const_iterator it;

microorganism_id = id;

for(it = edges.begin(); it != edges.end(); ++it){
	new_wall = (*it)->Clone();
	edge_list.push_back(new_wall);
}

connected_cell = NULL;

}


ostream& operator<<(ostream& os, const MicroOrganism& rhs){

if(rhs.connected_cell == NULL){
os<<"The microorganism "<<rhs.microorganism_id<<" could not be placed into any cell!";
}else{
os<<"The microorganism "<<rhs.microorganism_id<<" was successfully placed into the cell "<<(rhs.connected_cell->GetCellID())<<".";
}


return os;
	
}


MicroOrganism::~MicroOrganism() {}

