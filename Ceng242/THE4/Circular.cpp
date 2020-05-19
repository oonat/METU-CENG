#include "Circular.h"


Circular::Circular(int id_param, float radius_param):MicroOrganism(id_param){

Wall* curvy = new CurvyWall(2*PI*radius_param, radius_param);

edge_list.push_back(curvy);

organism_radius = radius_param;

}



Circular::~Circular(){

std::vector<Wall*>::iterator it;

for(it = edge_list.begin(); it != edge_list.end(); ++it){
	delete *it;
}

edge_list.clear();

}



void Circular::ConnectToCell(Cell* const given_cell){

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



bool Circular::DoesFitInto(const Cell& given_cell) const{

bool doesfit;

Cell* tmp = new Cell(given_cell);
tmp->StrengthenCellWall();

if((tmp->GetCellWall()).size() == 1){

	Wall* border_wall = ((tmp->GetCellWall()).front());

	if(dynamic_cast<CurvyWall*>(border_wall) == NULL){
		doesfit = false;
	}else{
		
		CurvyWall* casted_border = (CurvyWall*)(border_wall);

		if(fabs(casted_border->GetRadius() - organism_radius) < EPSILON)
			doesfit = true;
		else
			doesfit = false;
		
	}


}else{
	doesfit = false;
}


delete tmp;

return doesfit;

}



void Circular::React(){

if(connected_cell != NULL){

vector<Wall*> new_edges;

Particle* center = new Particle(((CurvyWall*)(connected_cell->GetCellWall().front()))->GetCenter());
float cell_radius = ((CurvyWall*)(connected_cell->GetCellWall().front()))->GetRadius();

Particle* new_border = new Particle(center->X()+2*cell_radius, center->Y());

Wall* new_wall = new CurvyWall(*new_border, *new_border, *center);

new_edges.push_back(new_wall);

connected_cell->RenewCellWall(new_edges);


delete center;
delete new_border;
}
}



bool Circular::DoesContain(const Particle& rhs) const{


if(connected_cell != NULL){
	CurvyWall* casted_wall = (CurvyWall*)(edge_list.front());
	if(rhs.FindDistance(casted_wall->GetCenter()) < organism_radius || fabs(rhs.FindDistance(casted_wall->GetCenter()) - organism_radius) < EPSILON)
		return true;
}


return false;
}
