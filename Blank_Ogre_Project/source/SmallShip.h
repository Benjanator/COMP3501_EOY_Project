#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>

class SmallShip: public GameObject
{
public:
	SmallShip(Ogre::SceneNode*);
	~SmallShip(void);

	void setTeam(int);
	int getTeam();

	Ogre::SceneNode& getNode();

	void accelerate(int _abs);
	void fullStop();
	void verticalThrust(int _abs);
	void horizontalThrust(int _abs);

	void pitch(Ogre::Radian);
	void yaw(Ogre::Radian);
	void roll(Ogre::Quaternion);
	void translate(Ogre::Vector3, Ogre::Vector3, Ogre::Vector3);

	void update(void);

protected:
	void move();


	Ogre::SceneNode* m_pNode;
	Ogre::Vector3 direction;
	Ogre::Vector3 up;
	Ogre::Vector3 right;

	bool indestructable;
	
	float accel_Rate;   // rate of acceleration 
	float roll_Rate;
	float yaw_Rate;
	float pitch_Rate;

	Ogre::Vector3 velocity;

	int team;
};

