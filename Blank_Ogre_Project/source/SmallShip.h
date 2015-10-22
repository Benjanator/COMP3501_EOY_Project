#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>

class SmallShip: public GameObject
{
public:
	SmallShip(Ogre::SceneNode*);
	~SmallShip(void);

	void accelerate(int _abs);
	void verticalThrust(int _abs);
	void horizontalThrust(int _abs);

	void pitch(int _abs);
	void yaw(int _abs);
	void roll(int _abs);

	void update(void);

protected:
	void move();


	Ogre::SceneNode* m_pNode;
	Ogre::Vector3 direction;
	Ogre::Vector3 up;

	bool indestructable;
	
	float accel_Rate;   // rate of acceleration 
	float roll_Rate;
	float yaw_Rate;
	float pitch_Rate;

	Ogre::Vector3 velocity;

	int team;
};

