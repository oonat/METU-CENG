#include "Squadratic.h"


Squadratic::Squadratic(int id_param, const vector<Wall*>& edges_param):MicroOrganism(id_param, edges_param){

child_1 = NULL;
child_2 = NULL;
child_3 = NULL;
child_4 = NULL;

}


Squadratic::Squadratic(int id_param, float length_param):MicroOrganism(id_param){

Wall* w1 = new Wall(length_param);
Wall* w2 = new Wall(length_param);
Wall* w3 = new Wall(length_param);
Wall* w4 = new Wall(length_param);

edge_list.push_back(w1);
edge_list.push_back(w2);
edge_list.push_back(w3);
edge_list.push_back(w4);

child_1 = NULL;
child_2 = NULL;
child_3 = NULL;
child_4 = NULL;


}



Squadratic::Squadratic(const Squadratic& rhs):MicroOrganism(rhs.microorganism_id, rhs.edge_list){

if(rhs.child_1 != NULL)
	child_1 = new Squadratic(*(rhs.child_1));
else
	child_1 = NULL;



if(rhs.child_2 != NULL)
	child_2 = new Squadratic(*(rhs.child_2));
else
	child_2 = NULL;



if(rhs.child_3 != NULL)
	child_3 = new Squadratic(*(rhs.child_3));
else
	child_3 = NULL;



if(rhs.child_4 != NULL)
	child_4 = new Squadratic(*(rhs.child_4));
else
	child_4 = NULL;


}



Squadratic::~Squadratic(){

std::vector<Wall*>::iterator it;

for(it = edge_list.begin(); it != edge_list.end(); ++it){
	delete *it;
}

edge_list.clear();

delete child_1;
delete child_2;
delete child_3;
delete child_4;

}



void Squadratic::ConnectToCell(Cell* const given_cell){

if(this->DoesFitInto(*given_cell)){

Wall* new_wall;

connected_cell = given_cell;

Cell* tmp = new Cell(*given_cell);
tmp->StrengthenCellWall();

std::vector<Wall*>::iterator it;
std::vector<Wall*>::const_iterator const_it;

for(it = edge_list.begin(); it != edge_list.end(); ++it){
	delete *it;
}

edge_list.clear();

for(const_it = tmp->GetCellWall().begin(); const_it != tmp->GetCellWall().end(); ++const_it){
	new_wall = (*const_it)->Clone();
	edge_list.push_back(new_wall);
}


delete tmp;

}

}



bool Squadratic::DoesFitInto(const Cell& given_cell) const{

bool doesfit = true;
float this_edge = edge_list.front()->GetLength();

Cell* tmp = new Cell(given_cell);
tmp->StrengthenCellWall();

std::vector<Wall*>::const_iterator const_it;



if((tmp->GetCellWall()).size() == 4){
	
	// length control
	for(const_it = tmp->GetCellWall().begin(); const_it != tmp->GetCellWall().end(); ++const_it){
		if((*const_it)->GetLength() != this_edge){
			doesfit = false;
			break;
		}
	}

	// angle control
	for(const_it = tmp->GetCellWall().begin(); const_it != tmp->GetCellWall().end() - 1; ++const_it){
		if(fabs((*const_it)->FindAngleBetween(*(*(const_it + 1))) - M_PI/2) >= EPSILON){
			doesfit = false;
			break;
		}
	}


	if(fabs((tmp->GetCellWall().back())->FindAngleBetween(*(tmp->GetCellWall().front())) - M_PI/2) >= EPSILON)
		doesfit = false;


}else{
	doesfit = false;
}


delete tmp;
return doesfit;
}



void Squadratic::React(){


int i;

Particle w1((fabs(edge_list[0]->GetInitialParticle().X() + edge_list[0]->GetFinalParticle().X())/2),(fabs(edge_list[0]->GetInitialParticle().Y() + edge_list[0]->GetFinalParticle().Y())/2));
Particle w2((fabs(edge_list[1]->GetInitialParticle().X() + edge_list[1]->GetFinalParticle().X())/2),(fabs(edge_list[1]->GetInitialParticle().Y() + edge_list[1]->GetFinalParticle().Y())/2));
Particle w3((fabs(edge_list[2]->GetInitialParticle().X() + edge_list[2]->GetFinalParticle().X())/2),(fabs(edge_list[2]->GetInitialParticle().Y() + edge_list[2]->GetFinalParticle().Y())/2));
Particle w4((fabs(edge_list[3]->GetInitialParticle().X() + edge_list[3]->GetFinalParticle().X())/2),(fabs(edge_list[3]->GetInitialParticle().Y() + edge_list[3]->GetFinalParticle().Y())/2));
Particle middle((fabs(w1.X() + w3.X())/2),(fabs(w1.Y() + w3.Y()))/2);

vector<Wall*> arr_1;
vector<Wall*> arr_2;
vector<Wall*> arr_3;
vector<Wall*> arr_4;

arr_1.push_back(new Wall(edge_list[0]->GetInitialParticle(), w1));
arr_1.push_back(new Wall(w1, middle));
arr_1.push_back(new Wall(middle, w4));
arr_1.push_back(new Wall(w4, edge_list[0]->GetInitialParticle()));

arr_2.push_back(new Wall(w1, edge_list[0]->GetFinalParticle()));
arr_2.push_back(new Wall(edge_list[0]->GetFinalParticle(), w2));
arr_2.push_back(new Wall(w2, middle));
arr_2.push_back(new Wall(middle, w1));

arr_3.push_back(new Wall(w2, edge_list[2]->GetInitialParticle()));
arr_3.push_back(new Wall(edge_list[2]->GetInitialParticle(), w3));
arr_3.push_back(new Wall(w3, middle));
arr_3.push_back(new Wall(middle, w2));

arr_4.push_back(new Wall(w3, edge_list[2]->GetFinalParticle()));
arr_4.push_back(new Wall(edge_list[2]->GetFinalParticle(), w4));
arr_4.push_back(new Wall(w4, middle));
arr_4.push_back(new Wall(middle, w3));

child_1 = new Squadratic(4*microorganism_id , arr_1);
child_2 = new Squadratic(4*microorganism_id + 1, arr_2);
child_3 = new Squadratic(4*microorganism_id + 2, arr_3);
child_4 = new Squadratic(4*microorganism_id + 3, arr_4);


for(i = 0; i<4; i++){
	delete arr_1[i];
}

arr_1.clear();


for(i = 0; i<4; i++){
	delete arr_2[i];
}

arr_2.clear();


for(i = 0; i<4; i++){
	delete arr_3[i];
}

arr_3.clear();


for(i = 0; i<4; i++){
	delete arr_4[i];
}

arr_4.clear();



}


bool Squadratic::is_inside(const Squadratic* micro, float min_x, float max_x, float min_y, float max_y) const{
	
	vector<Particle> arr;
	arr.push_back(micro->edge_list[0]->GetInitialParticle());
	arr.push_back(micro->edge_list[0]->GetFinalParticle());
	arr.push_back(micro->edge_list[2]->GetInitialParticle());
	arr.push_back(micro->edge_list[2]->GetFinalParticle());

	float min_x_this = arr[0].X();
	float max_x_this = arr[0].X();
	float min_y_this = arr[0].Y();
	float max_y_this = arr[0].Y();

	for(int i = 1; i<4; i++){
		if(arr[i].X() < min_x_this)
			min_x_this = arr[i].X();
		else if (arr[i].X() > max_x_this)
			max_x_this = arr[i].X();

		if(arr[i].Y() < min_y_this)
			min_y_this = arr[i].Y();
		else if (arr[i].Y() > max_y_this)
			max_y_this = arr[i].Y();
	}

	return (min_x > min_x_this || fabs(min_x - min_x_this) < EPSILON)&&(max_x < max_x_this || fabs(max_x - max_x_this) < EPSILON)&&(min_y > min_y_this || fabs(min_y - min_y_this) < EPSILON)&&(max_y < max_y_this || fabs(max_y - max_y_this) < EPSILON);

}



bool Squadratic::is_equal(const Squadratic* micro, float min_x, float max_x, float min_y, float max_y) const{

	vector<Particle> arr;
	arr.push_back(micro->edge_list[0]->GetInitialParticle());
	arr.push_back(micro->edge_list[0]->GetFinalParticle());
	arr.push_back(micro->edge_list[2]->GetInitialParticle());
	arr.push_back(micro->edge_list[2]->GetFinalParticle());

	float min_x_this = arr[0].X();
	float max_x_this = arr[0].X();
	float min_y_this = arr[0].Y();
	float max_y_this = arr[0].Y();

	for(int i = 1; i<4; i++){
		if(arr[i].X() < min_x_this)
			min_x_this = arr[i].X();
		else if (arr[i].X() > max_x_this)
			max_x_this = arr[i].X();

		if(arr[i].Y() < min_y_this)
			min_y_this = arr[i].Y();
		else if (arr[i].Y() > max_y_this)
			max_y_this = arr[i].Y();
	}

	return (fabs(min_x_this - min_x) < EPSILON)&&(fabs(max_x_this - max_x) < EPSILON)&&(fabs(min_y_this - min_y) < EPSILON)&&(fabs(max_y_this - max_y) < EPSILON);

}




Squadratic& Squadratic::GetChild(float min_x, float max_x, float min_y, float max_y) const{

	


	if(child_1 == NULL && child_2 == NULL && child_3 == NULL && child_4 == NULL)
		throw NotBornChildException();
	else if(is_equal(child_1, min_x, max_x, min_y, max_y))
		return *child_1;
	else if(is_equal(child_2, min_x, max_x, min_y, max_y))
		return *child_2;
	else if(is_equal(child_3, min_x, max_x, min_y, max_y))
		return *child_3;
	else if(is_equal(child_4, min_x, max_x, min_y, max_y))
		return *child_4;
	else{


		if(is_inside(child_1, min_x, max_x, min_y, max_y)){

			return child_1->GetChild(min_x, max_x, min_y, max_y);

		}else if(is_inside(child_2, min_x, max_x, min_y, max_y)){

			return child_2->GetChild(min_x, max_x, min_y, max_y);

		}else if(is_inside(child_3, min_x, max_x, min_y, max_y)){

			return child_3->GetChild(min_x, max_x, min_y, max_y);

		}else if(is_inside(child_4, min_x, max_x, min_y, max_y)){

			return child_4->GetChild(min_x, max_x, min_y, max_y);

		}else{
			throw NotBornChildException();
		}


	}



}
