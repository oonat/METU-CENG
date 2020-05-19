#include "CurvyWall.h"


CurvyWall::CurvyWall(float len_param, float rad_param):Wall(len_param){

rad = rad_param;
center = NULL;

}


CurvyWall::CurvyWall(const Particle& start_param, const Particle& end_param, const Particle& center_param):Wall(start_param, end_param){
center = new Particle(center_param);

if(start_point != NULL && center != NULL){

rad = start_point->FindDistance(*center);


// re-calculate length after wall constr.
if(*start_point == *end_point){

length = 2*PI*rad;

}else{

float start_angle = atan2(start_point->Y() - center->Y(), start_point->X() - center->X());
float end_angle = atan2(end_point->Y() - center->Y(), end_point->X() - center->X());
float alpha = end_angle - start_angle;

if (alpha < 0) 
	alpha += 2*PI;

length = alpha*rad;

}


}
}



CurvyWall::CurvyWall(const CurvyWall& rhs):Wall(rhs){

if(rhs.center == NULL){
center = NULL;
}else{
center = new Particle(*rhs.center);
}

rad = rhs.rad;

}



float CurvyWall::GetRadius() const{
return rad;
}



const Particle& CurvyWall::GetCenter() const{
return *center;
}




void CurvyWall::ComputeLength(){


if(start_point != NULL && end_point != NULL){
	
if(*start_point == *end_point){

length = 2*PI*rad;

}else{

float start_angle = atan2(start_point->Y() - center->Y(), start_point->X() - center->X());
float end_angle = atan2(end_point->Y() - center->Y(), end_point->X() - center->X());
float alpha = end_angle - start_angle;

if (alpha < 0) 
	alpha += 2*PI;

length = alpha*rad;

}

}
}



Wall* CurvyWall::Clone() const{
return new CurvyWall(*this);
}



bool CurvyWall::IsContinuousLinear(const Wall& rhs) const{
return false;
}



const Wall& CurvyWall::operator+(const Wall& rhs) const{



if(dynamic_cast<const CurvyWall*>(&rhs) == NULL){
	throw ApplePearException(); 
}else{

	const CurvyWall* casted_rhs = (CurvyWall*)(&rhs);

	if(*center == *casted_rhs->center){
		if(*start_point == *casted_rhs->end_point){
			CurvyWall* new_curvy = new CurvyWall(*casted_rhs->start_point, *end_point, *center);
			return *new_curvy;

        }else if(*end_point == *casted_rhs->start_point){
			CurvyWall* new_curvy = new CurvyWall(*start_point, *casted_rhs->end_point, *center);
			return *new_curvy;
        }else{
		throw ApplePearException(); 
		}



	}else{
		throw ApplePearException(); 
	}
}


}





CurvyWall::~CurvyWall(){

delete center;
	
}

