#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;
struct vertexData            // stores the data of each vertice used to create object
{
	float x;
	float y;
	float z;
};

struct face                 // Stores the triangle information, vetices index of each triangle
{
	int a;
	int b;
	int c;
};

std::vector<vertexData> vertices;             // Store all the vertices
std::vector<face> triangles;		      // Store all the triangle info
string trim(string str);
void ReadObject();			     // Read the Object file and store data accordingly
double find_Triangles_Area();		     // Find surface area of the object by finding the area of each triangle

int main(int argc, char const *argv[])
{
	double knotSurfaceArea;
	cout<< " vertices vettor size " << vertices.size()<<endl;
	cout<< "triangles vector size" <<triangles.size()<<endl;
	ReadObject();
	cout<< " vertices vettor size " << vertices.size()<<endl;
	cout<< "triangles vector size" <<triangles.size()<<endl;
	cout<<"Program ended correctly and handled empty lines"<<endl;
	knotSurfaceArea = find_Triangles_Area();
	std::cout << "knot surface area is : " << knotSurfaceArea <<std::endl;
	return 0;
}

void ReadObject()
{
	ifstream myfile("knot.obj");
	if (myfile.is_open())
	{
		cout<< "File is open"<<endl;
		vertexData vertex;
		face faceVertices;
		string line = "";
		string first = "";
		string temp = "";
		string x = "";
		string y = "";
		string z = "";

		// Reading file as one line at a time. and then perform nessary string operations to extract data as float or intger.
		while (getline(myfile, line))
		{
			if(line.size()>0) 
			{
				first = line.substr(0, 1);
				temp = line.substr(1);
				if (first == "v")              // check if the string line data is vertex
				{
					temp = trim(temp);
					vertex.x= stof(temp.substr(0, temp.find(" ")));
					temp = temp.substr(temp.find(" ")+1);
					vertex.y= stof(temp.substr(0, temp.find(" ")));
					vertex.z = stof(temp.substr(temp.find(" ")+1));
					vertices.push_back(vertex);
				}
				if (first == "f")             // check if the string line data is trianle info
				{
					temp = trim(temp);
					faceVertices.a = stoi(temp.substr(0, temp.find(" ")));
					temp = temp.substr(temp.find(" ")+1);
					faceVertices.b = stoi(temp.substr(0, temp.find(" ")));
					faceVertices.c = stoi(temp.substr(temp.find(" ")+1));
					triangles.push_back(faceVertices);
				}
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "file did not opened correctly" << std::endl;
	}
}
string trim(string str)
{
	size_t strBegin = str.find_first_not_of(" \t");
	if (strBegin == std::string::npos)
	{
		return "";
	}
	size_t strEnd = str.find_last_not_of(" \t");
	size_t strRange = (strEnd - strBegin) + 1;
	string result = str.substr(strBegin, strRange);
	return result;
}

double find_Triangles_Area()
{
	// Distance Formula is used to find the length of each segment of triangle and area is calculated using Heron's formula
	float ab = 0;
	float ac = 0;
	float bc = 0;
	float ab_x1_x2 = 0;  // define the x1-x2 value for segment ab
	float ab_y1_y2 = 0;  // define the y1-y2 value for segment ab
	float ab_z1_z2 = 0;  // define the z1-z2 value fro segment ab
	float ac_x1_x2 = 0;  // define the x1-x2 value for segment ac
	float ac_y1_y2 = 0;  // define the y1-y2 value for segment ac
	float ac_z1_z2 = 0;  // define the z1-z2 value fro segment ac
	float bc_x1_x2 = 0;  // define the x1-x2 value for segment bc
	float bc_y1_y2 = 0;  // define the y1-y2 value for segment bc
	float bc_z1_z2 = 0;  // define the z1-z2 value fro segment bc

	double area = 0;
	float s = 0;          // s is spherimeter
	for (size_t i = 0; i < triangles.size(); i++)
	{
		ab_x1_x2 = (vertices[(triangles[i].a)-1].x) - (vertices[(triangles[i].b)-1].x);
		ab_y1_y2 = (vertices[(triangles[i].a)-1].y) - (vertices[(triangles[i].b)-1].y);
		ab_z1_z2 = (vertices[(triangles[i].a)-1].z) - (vertices[(triangles[i].b)-1].z);

		ab = sqrt(pow(ab_x1_x2,2) + pow(ab_y1_y2,2) + pow(ab_z1_z2,2));

		ac_x1_x2 = (vertices[(triangles[i].a)-1].x) - (vertices[(triangles[i].c)-1].x);
		ac_y1_y2 = (vertices[(triangles[i].a)-1].y) - (vertices[(triangles[i].c)-1].y);
		ac_z1_z2 = (vertices[(triangles[i].a)-1].z) - (vertices[(triangles[i].c)-1].z);

		ac = sqrt(pow(ac_x1_x2,2) + pow(ac_y1_y2,2) + pow(ac_z1_z2,2));

		bc_x1_x2 = (vertices[(triangles[i].b)-1].x) - (vertices[(triangles[i].c)-1].x);
		bc_y1_y2 = (vertices[(triangles[i].b)-1].y) - (vertices[(triangles[i].c)-1].y);
		bc_z1_z2 = (vertices[(triangles[i].b)-1].z) - (vertices[(triangles[i].c)-1].z);

		bc = sqrt(pow(bc_x1_x2,2) + pow(bc_y1_y2,2) + pow(bc_z1_z2,2));

		s = (ab + ac + bc)/2;
		area = area + sqrt (s*(s-ab)*(s-bc)*(s-ac));
	}
	return area;
}
