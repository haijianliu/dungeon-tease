
#ifndef Emitter_hpp
#define Emitter_hpp

class Emitter : public Component {
private:
	float lastSpawnTime = 0;
	std::vector<Particle*> particles;

	void update();
	void activeParticle();

public:
	Material* material;
	bool animation = false; // when set to true, use uv animation support vertex shader
	float divideX = 1, divideY = 1, sampleTime = 1; // default setting with no divide

	// default values
	unsigned int maxParticles = 40;
	float spawnTime = 0.01;
	float minLifeTime = 1, maxLifeTime = 2;
	float initScale = 10 * GLOBAL_SCALE;
	float velocityHorizonalRange = 0.1, velocityVerticalRange = 0.1;
	float gravity = -0.1;

	Emitter();
	~Emitter();

	void createParticles(const char* name, Scene* scene); // must create
};

#endif /* Emitter_hpp */
