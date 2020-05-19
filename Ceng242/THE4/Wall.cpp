#include "Wall.h"
#include "CurvyWall.h"

Wall::Wall(float length_param){
length = length_param;
start_point = NULL;
end_point = NULL;
}



Wall::Wall(const Particle& start_param, const Particle& end_param){
start_point = new Particle(start_param);
end_point = new Particle(end_param);

// compute length
if(start_point != NULL && end_point != NULL){
	length = start_point->FindDistance(*end_point);
}

}



Wall::Wall(const Wall& rhs){

if(rhs.start_point == NULL){
start_point = NULL;
}else{
start_point = new Particle(*(rhs.start_point));
}

if(rhs.end_point == NULL){
end_point = NULL;
}else{
end_point = new Particle(*(rhs.end_point));
}


length = rhs.length;
}



const Particle& Wall::GetInitialParticle() const{
return *start_point;
}



const Particle& Wall::GetFinalParticle() const{
return *end_point;
}



float Wall::FindAngleBetween(const Wall& rhs) const{

float this_angle;
float rhs_angle;

if((start_point->Y() - end_point->Y()) == 0){
	this_angle = 0;
}else if((start_point->Y() - end_point->Y()) < 0){
	this_angle = atan2(end_point->Y() - start_point->Y(), end_point->X() - start_point->X());
}else{
	this_angle = atan2(start_point->Y() - end_point->Y(), start_point->X() - end_point->X());
}


if((rhs.start_point->Y() - rhs.end_point->Y()) == 0){
	rhs_angle = 0;
}else if((rhs.start_point->Y() - rhs.end_point->Y()) < 0){
	rhs_angle = atan2(rhs.end_point->Y() - rhs.start_point->Y(), rhs.end_point->X() - rhs.start_point->X());
}else{
	rhs_angle = atan2(rhs.start_point->Y() - rhs.end_point->Y(), rhs.start_point->X() - rhs.end_point->X());
}


return fabs(this_angle - rhs_angle);
}



float Wall::GetLength() const{
return length;
}



void Wall::ComputeLength(){

if(start_point != NULL && end_point != NULL)
	length = start_point->FindDistance(*end_point);

}



Wall* Wall::Clone() const{

return (new Wall(*this));

}



bool Wall::IsContinuousLinear(const Wall& rhs) const{

// if wall is not curvy
if(dynamic_cast<const CurvyWall*>(&rhs) == NULL){
	if(*rhs.start_point == *end_point || *start_point == *rhs.end_point){
		// Epsilon
		if(this->FindAngleBetween(rhs) < EPSILON)
			return true;
		else 
			return false;
	}else{
		return false;
	}
}

return false;

}



const Wall& Wall::operator+(const Wall& rhs) const{


// if wall is not curvy
if(dynamic_cast<const CurvyWall*>(&rhs) == NULL){
	bool is_lin = this->IsContinuousLinear(rhs);

	if(is_lin){
		if(*start_point == *rhs.end_point){
			Wall* new_wall = new Wall(*rhs.start_point, *end_point);
			return *new_wall;
		}else{
			Wall* new_wall = new Wall(*start_point, *rhs.end_point);
			return *new_wall;
		}
	}else{
		throw ApplePearException();
	}
}else{
throw ApplePearException();
}


}





Wall::~Wall(){

delete start_point;
delete end_point;

}

