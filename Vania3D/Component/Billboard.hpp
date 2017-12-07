
#ifndef Billboard_hpp
#define Billboard_hpp

class Billboard : public Component {
private:
	Transform* transform;
	Transform* transformCamera;
	
	void start();
	void update();

public:
	Billboard();
	~Billboard();
};

#endif /* Billboard_hpp */
