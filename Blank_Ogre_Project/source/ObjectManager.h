#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;
class ObjectManager
{
public:
	ObjectManager(Ogre::SceneManager*);
	~ObjectManager(void);

	void addObject(GameObject*);
	void removeObject(GameObject*);
	void cleanDestroyedObjects();
	//void updateObjects();

	std::vector<GameObject*>& getObjectList();
	int getListSize();

private:
	Ogre::SceneManager* scene_manager;

	std::vector<GameObject*> objectList;
	std::vector<GameObject*> destroyList;
};

