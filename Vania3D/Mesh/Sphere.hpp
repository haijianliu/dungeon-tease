
#ifndef Sphere_hpp
#define Sphere_hpp

class Sphere : public Model {
private:
	unsigned int vao, count;

public:
	Sphere();
	~Sphere();

	void draw();
};

#endif /* Sphere_hpp */
