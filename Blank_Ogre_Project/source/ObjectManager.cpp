#include "ObjectManager.h"


ObjectManager::ObjectManager(void)
{
}


ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::addObject(GameObject* _obj)
{
	objectList.push_back(_obj);
}

void ObjectManager::updateObjects()
{
	for(vector<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it){
		(*it)->update();
	}
}
