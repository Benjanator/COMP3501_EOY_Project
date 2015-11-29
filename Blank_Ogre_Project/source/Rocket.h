#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include "GameObject.h"

class Rocket: public GameObject
{
public:
	Rocket(Ogre::SceneNode*,Ogre::Quaternion, Ogre::Vector3, Ogre::Vector3);
	//Rocket(Ogre::SceneNode* );
	~Rocket(void);
	Ogre::SceneNode& getNode();

	void move();
	void explode();
	void collide();
	void update(float _timer);

private:
	
	int countdown;
	bool hasExploded;
	float accel_Rate; 
	float personalTimer;
	

};
