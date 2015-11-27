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
	void collide();
	void explode();

private:
	
	int countdown;
	float accel_Rate; 
	void update(float _timer);

};
