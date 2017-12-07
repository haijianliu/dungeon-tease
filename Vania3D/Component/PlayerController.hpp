
#ifndef PlayerController_hpp
#define PlayerController_hpp

class PlayerController : public Component {
public:
	GameObject* camera;

	float lastAttack = 0;
	unsigned int animation = 0;

	PlayerController();
	~PlayerController ();

	void update();
};

#endif /* PlayerController_hpp */
