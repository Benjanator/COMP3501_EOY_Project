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
	void updateObjects();

	vector<GameObject*> objectList;
};

