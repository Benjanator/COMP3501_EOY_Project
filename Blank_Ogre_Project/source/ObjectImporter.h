#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <OgreVector3.h>
#include <OgreVector2.h>

#define v_V3_ptr std::vector<Ogre::Vector3>
#define v_V2_ptr std::vector<Ogre::Vector2>

using namespace std;
class ObjectImporter
{
public:	
	struct Face{
		unsigned int vertex[3];
		unsigned int normal[3];
		unsigned int uv[3];
	};

	ObjectImporter(void);
	~ObjectImporter(void);
	bool loadJSONModel(std::string _fName, vector<Face> &_faces, v_V3_ptr &_verts, v_V3_ptr &_norms = v_V3_ptr(), v_V2_ptr &_uvs = v_V2_ptr());
	bool loadModel(std::string _fName, vector<unsigned int> &_faces, v_V3_ptr &_verts, v_V3_ptr &_norms = v_V3_ptr(), v_V2_ptr &_uvs = v_V2_ptr());
	
private:
	void parseToFloat(string, vector<float>&);

};



