
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
PointLight::PointLight() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
PointLight::~PointLight() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void PointLight::start() {
	float lightMax = glm::max(glm::max(this->color.x, this->color.y), this->color.z) * this->intensity;
	this->radius = 8 * glm::sqrt(lightMax / 5);

//	float constant = 1.0;
//	float linear = 0.7;
//	float quadratic = 1.8;
//	this->radius = (-linear + glm::sqrt(linear * linear - 4 * quadratic * (constant - (256.0 / 5.0) * lightMax))) / (2 * quadratic);
}
