#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include "GameObject.h"

class Rocket: public GameObject
{
public:
	//Rocket(Ogre::SceneNode*,Ogre::Quaternion, Ogre::Vector3);
	Rocket(Ogre::SceneNode*);
	~Rocket(void);
	Ogre::SceneNode& getNode();

	void fly();
	void collide();
	void explode();

private:
	
	int countdown;

	void update(void);

};
