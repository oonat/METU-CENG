#include "Particle.h"


Particle::Particle(float param_x, float param_y){
x = param_x;
y = param_y;
}


Particle::Particle(const Particle& rhs){
x = rhs.x;
y = rhs.y;
}


float Particle::X() const{
return x;
}


float Particle::Y() const{
return y;
}


float Particle::FindDistance(const Particle& rhs) const{

float horizontal_dist = (x-rhs.x)*(x-rhs.x);
float vertical_dist = (y-rhs.y)*(y-rhs.y);

return sqrt(horizontal_dist+vertical_dist);
}


bool Particle::operator== (const Particle& rhs) const{
return (fabs(x-rhs.x)<EPSILON) && (fabs(y-rhs.y)<EPSILON);
}


ostream& operator<<(ostream& os, const Particle& rhs){
os<<"("<<rhs.x<<","<<rhs.y<<")";

return os;
}
