#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>



class SmallShip: public GameObject
{
public:
	SmallShip(Ogre::SceneNode*);
	~SmallShip(void);

	Ogre::SceneNode& getNode();

	void accelerate(int _abs);
	void fullStop();
	void verticalThrust(int _abs);
	void horizontalThrust(int _abs);

	void pitch(Ogre::Radian);
	void yaw(Ogre::Radian);
	void roll(Ogre::Quaternion);
	void translate(Ogre::Vector3, Ogre::Vector3, Ogre::Vector3);

	void update(float _timer);
	void collide();
	void shoot(	GameObjectFactory* );

	Ogre::Quaternion getOrientation();
	Ogre::Vector3 getPosition();

	


protected:

	void move();

	Ogre::Vector3 direction;
	Ogre::Vector3 up;
	Ogre::Vector3 right;

	//Ogre::Vector3 currentDirection;
	//Ogre::Vector3 currentUp;
	//Ogre::Vector3 currentRight;

	bool indestructable;
	
	float accel_Rate;   // rate of acceleration 
	float roll_Rate;
	float yaw_Rate;
	float pitch_Rate;
	void collide(int);

	Ogre::Vector3 velocity;

private:

	int health;
	bool hasExploded;
	float personalTimer;
};

