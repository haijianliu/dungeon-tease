
#ifndef Particle_hpp
#define Particle_hpp

class Particle : public Component {
	friend class Emitter;
	
private:
	void update();
	
public:
	float lifeTime = 1;
	float gravity = 0;
	glm::vec3 initScale, initVelocity;
	
	Particle();
	~Particle();
};

#endif /* Particle_hpp */
