#include "ObjectManager.h"


ObjectManager::ObjectManager(void)
{
}


ObjectManager::~ObjectManager(void)
{
	while(!objectList.empty())
	{
		GameObject* temp = objectList.back();
		objectList.pop_back();
		delete temp;
	}
}

void ObjectManager::addObject(GameObject* _obj)
{
	objectList.push_back(_obj);
}

/*
void ObjectManager::updateObjects()
{
	for(vector<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it){
		(*it)->update();
	}
}*/

vector<GameObject*>& ObjectManager::getObjectList()
{
	return objectList;
}

int ObjectManager::getListSize()
{
	return objectList.size();
}
