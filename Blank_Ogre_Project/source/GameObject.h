#pragma once
class GameObject
{
public:
	enum objectType{empty = -1,
					smallAlly_fighter = 0, 
					smallEnemy_fighter, 
					smallAlly_bomber = 10, 
					smallEnemy_bomber, 
					largeEnemy_cmd = 20, 
					largeAlly_cmd};

	GameObject(objectType);
	~GameObject(void);
	virtual void update() = 0;

protected:
	objectType type;
};

