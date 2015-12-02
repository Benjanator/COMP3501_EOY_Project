#pragma once
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include "GameObject.h"

class ScatterShot: public GameObject
{
public: 
	ScatterShot(Ogre::SceneNode * ,Ogre::Quaternion ,Ogre::Vector3 , bool lr);
	~ScatterShot(void);
	Ogre::SceneNode& getNode();

	void move();

	void particle();
	void update(float _timer);
	void collide();
	void collide(int);

private:

	Ogre::Vector3 left_Direction;
	Ogre::Vector3 right_Direction;
	Ogre::Vector3 down_Direction;


	std::vector <Ogre::Vector3> controlPoints;
	void generateCP(int);
	void splinetraj(float _timer);
	int countdown;
	float accel_Rate; 
	

};

