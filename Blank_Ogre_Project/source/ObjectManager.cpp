#include "ObjectManager.h"


ObjectManager::ObjectManager(Ogre::SceneManager* _sm)
{
	scene_manager = _sm;
}


ObjectManager::~ObjectManager(void)
{
	scene_manager = 0;

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

void ObjectManager::removeObject(GameObject* _obj)
{
	GameObject* temp;

	for(unsigned int i = 0; i < objectList.size(); i++){
		if(objectList.at(i) == _obj)
		{
			temp = objectList.at(i);
			objectList.erase(objectList.begin() + i);
			destroyList.push_back(temp);
			break;
		}
	}
}

/*
void ObjectManager::updateObjects()
{
	for(vector<GameObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it){
		(*it)->update();
	}
}*/

void ObjectManager::cleanDestroyedObjects()
{
	while(!destroyList.empty()){
		scene_manager->getRootSceneNode()->removeAndDestroyChild(destroyList.back()->getNode().getName());
		destroyList.pop_back();
	}
}

vector<GameObject*>& ObjectManager::getObjectList()
{
	return objectList;
}

int ObjectManager::getListSize()
{
	return objectList.size();
}
