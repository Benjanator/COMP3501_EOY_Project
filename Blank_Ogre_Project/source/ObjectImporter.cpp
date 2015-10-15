#include "ObjectImporter.h"
#include "../bin/path_config.h"


ObjectImporter::ObjectImporter(void)
{
}


ObjectImporter::~ObjectImporter(void)
{
}

bool ObjectImporter::loadJSONModel(string _fName, vector<Face> &_faces, v_V3_ptr &_verts, v_V3_ptr &_norms, v_V2_ptr &_uvs)
{
	//check file availability
	string filePath = MATERIAL_DIRECTORY + std::string("/media/mesh/") + _fName;

	ifstream file (filePath);
	if(!file.is_open()){
		cout << "404 :: File Not Found...\n";
		return false;
	}
	
	//clean return vectors
	if(_verts.size() > 0) _verts.clear();
	if(_norms.size() > 0) _norms.clear();
	if(_uvs.size() > 0) _uvs.clear();

	string line;
	
	string sVert = "vertices";
	string sUV = "uvs";
	string sNorm = "normals";
	string sFace = "faces";

	while(getline(file, line)){
		string::size_type start = line.find_first_not_of(" \"");

		if(line.compare(start, sVert.size(), sVert) == 0){
			string::size_type first = line.find("[");
			string::size_type last = line.find("]");

			if(first > line.size() || first + 1 == last) continue;

			string temp = line.substr(first+1, last - first - 1);

			vector<float> fl;
			parseToFloat(temp, fl);

			for(int i = 0; i < (int)fl.size(); i+=3){
				Ogre::Vector3 vert;

				vert.x = fl[i];
				vert.y = fl[i+1];
				vert.z = fl[i+2];

				_verts.push_back(vert);
			}
			cout << " verts: " << _verts.size() << endl;
		}
		else if(line.compare(start, sUV.size(), sUV) == 0){
			string::size_type first = line.find_first_of("[");
			string::size_type last = line.find_last_of("]");

			if(first > line.size() || first + 1 == last) continue;

			string temp = line.substr(first+2, last - first - 3);

			vector<float> fl;
			parseToFloat(temp, fl);

			for(int i = 0; i < (int)fl.size(); i+=2){
				Ogre::Vector2 uv;

				uv.x = fl[i];
				uv.y = fl[i+1];

				_uvs.push_back(uv);
			}
			cout << " uvs: " << _uvs.size() << endl;
		}
		else if(line.compare(start, sNorm.size(), sNorm) == 0){
			string::size_type first = line.find("[");
			string::size_type last = line.find("]");

			if(first > line.size() || first + 1 == last) continue;

			string temp = line.substr(first+1, last - first - 1);

			vector<float> fl;
			parseToFloat(temp, fl);

			for(int i = 0; i < (int)fl.size(); i+=3){
				Ogre::Vector3 norm;

				norm.x = fl[i];
				norm.y = fl[i+1];
				norm.z = fl[i+2];

				_norms.push_back(norm);
			}
			cout << " norm: " << _norms.size() << endl;
		}
		else if(line.compare(start, sFace.size(), sFace) == 0){ //MASSIVE NOTE***** face is indexed as [vert, vert, vert, norm, norm, norm, uv, uv, uv]
			string::size_type first = line.find("[");
			string::size_type last = line.find("]");

			if(first > line.size() || first + 1 == last) continue;

			string temp = line.substr(first+1, last - first - 1);

			vector<float> fl;
			parseToFloat(temp, fl);

			int step = 1;
			int varNum = 1;

			if(fl.size() >= 10){
				if(fl[0] == fl[10]){
					step = 10;
					varNum = 3;
				}
			}
			if(fl.size() >= 7){
				if(fl[0] == fl[7]){
					step = 7;
					varNum = 2;
				}
			}
			if(fl.size() >= 4){
				if(fl[0] == fl[4]){
					step = 3;
					varNum = 1;
				}
			}

			for(int i = 0; i < (int)fl.size(); i+=step){
				Face fc;
				for(int j = 0; j < 3; j++){					
					fc.vertex[j] = (varNum > 0)? (int)fl[i + (0*3) + (j+1)] : 0;
					//cout << fc.vertex[j] << ":";
					//fc.normal[j] = (varNum > 1)? (int)fl[i + (1*3) + (j+1)] : 0;
					//fc.uv[j] = (varNum > 2)? (int)fl[i + (2*3) + (j+1)] : 0;
				}

				//cout <<endl;
				_faces.push_back(fc);
			}
			cout << " face: " << _faces.size() << endl;
		}
		else{}
	}
}

/*INCOMPLETE - DO NOT USE*/
bool ObjectImporter::loadModel(string _fName, vector<unsigned int> &_faces, v_V3_ptr &_verts, v_V3_ptr &_norms, v_V2_ptr &_uvs)
{
	//check file availability
	string filePath = MATERIAL_DIRECTORY + std::string("/media/mesh/") + _fName;

	ifstream file (filePath);
	if(!file.is_open()){
		cout << "404 :: File Not Found...\n";
		return false;
	}
	
	//clean return vectors
	if(_verts.size() > 0) _verts.clear();
	if(_norms.size() > 0) _norms.clear();
	if(_uvs.size() > 0) _uvs.clear();

	string line;

	while(getline(file, line)){
		//cout << line[0] << " || " << line[1] << endl;

		if(line[0] == *"v" && (line[1] != *"n" && line[1] != *"t")){
			Ogre::Vector3 vert;
			
			vector<float> fl;
			parseToFloat(line, fl);

			vert.x = fl[0];
			vert.y = fl[1];
			vert.z = fl[2];

			_verts.push_back(vert);

			cout << "v " << vert << endl;
		}
		else if(line[0] == *"v" && line[1] == *"t"){
		 Ogre::Vector2 uv;

		 vector<float> fl;
		 parseToFloat(line, fl);

		 uv.x = fl[0];
		 uv.y = fl[1];

		 _uvs.push_back(uv);

		 cout <<"vt " << uv << endl;
		 }
		 else if(line[0] == *"v" && line[1] == *"n"){
		 Ogre::Vector3 norm;

		 vector<float> fl;
		 parseToFloat(line, fl);

		 norm.x = fl[0];
		 norm.y = fl[1];
		 norm.z = fl[2];

		 _norms.push_back(norm);

		 cout << "vn " << norm << endl;
		 }/*
		 else if(strcmp(lineHeader, "f") == 0){
		 unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
		 int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", vertexIndex[0], uvIndex[0], normalIndex[0], vertexIndex[1], uvIndex[1], normalIndex[1], vertexIndex[2], uvIndex[2], normalIndex[2]);
		 if(matches != 9){
		 cout << "Improper Format\n";
		 }
		 _faces.push_back(vertexIndex[0]);
		 _faces.push_back(vertexIndex[1]);
		 _faces.push_back(vertexIndex[2]);
		 }*/

	}

	file.close();
	return true;
}

void ObjectImporter::parseToFloat(string line, vector<float> &fl)
{
	vector<string> possible;

	string::size_type curr = 0;
	string::size_type found = 0;

	string::size_type max_size = line.size();

	do{
		found = line.find(",", curr);
		max_size = (found > line.size()) ? line.size() : found - curr;
		possible.push_back(line.substr(curr, max_size));
		curr = found+1;

	}while(found != string::npos);

	for(int i = 0; i < (int)possible.size(); i++){
		try{
			fl.push_back(stof(possible[i]));
		}
		catch(const invalid_argument&){};
	}
}