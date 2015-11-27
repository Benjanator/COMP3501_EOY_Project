#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;
class ObjectManager
{
public:
	ObjectManager(void);
	~ObjectManager(void);

	void addObject(GameObject*);
	//void updateObjects();

	std::vector<GameObject*>& getObjectList();
	int getListSize();

private:
	std::vector<GameObject*> objectList;
};

