
#ifndef Time_hpp
#define Time_hpp

class Time {
private:
	float lastTime = 0;

	Time();

public:
	float currentTime = 0;
	float deltaTime = 0;

	static Time* getInstance();
	~Time();

	void update();
};

#endif /* Time_hpp */
