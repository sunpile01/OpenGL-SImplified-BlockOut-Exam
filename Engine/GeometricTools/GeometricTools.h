#ifndef GEOMETRICTOOLS_H
#define GEOMETRICTOOLS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <glm/glm.hpp>
namespace GeometricTools {
	
	//Coordinates for a UnitTriangle
	constexpr std::array<float, 3 * 2> UnitTriangle2D = { -0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f };
	
	//Coordinates for a unitsquare
	constexpr std::array<float, 4 * 2> UnitSquare2D =
	{ 
		 -0.5f, -0.5f,  //0
		 0.5f, -0.5f,   //1
		 0.5f,  0.5f,	//2
		 -0.5f,  0.5f	//3
	};
	
	//Topology for a unitSquare
	constexpr std::array<float, 3 * 2> UnitSquareTopology = { 0, 1, 2, 2, 3, 0 };

	/**
	* @brief Creates the vertexes of the square
	* @return - vector with the vertexes
	*/
	std::vector<float> unitSquare2DTest() {
		std::vector <float> tmp;
		tmp.push_back(-0.5f);
		tmp.push_back(-0.5f);
		tmp.push_back(0.5f);
		tmp.push_back(-0.5f);
		tmp.push_back(0.5f);
		tmp.push_back(0.5f);
		tmp.push_back(-0.5f);
		tmp.push_back(0.5f);
		return tmp;
	}

	/**
	* @brief Generates the correct order of indices for a square
	* @return - vector with the indices
	*/
	std::vector<GLuint> unitSquareTopologyTest() {
		std::vector <GLuint> tmp;
		tmp.push_back(0);
		tmp.push_back(1);
		tmp.push_back(2);
		tmp.push_back(2);
		tmp.push_back(3);
		tmp.push_back(0);
		return tmp;
	}
	
	//Geometry of a 3D unit cube
	constexpr std::array<float, 8 * 3> UnitCube3D = {
	   -0.5f, -0.5f, -0.5f,  //0
	   -0.5f, -0.5f,  0.5f,  //1
		0.5f, -0.5f,  0.5f,  //2
		0.5f, -0.5f, -0.5f, //bottom 4 corners	//3

	   -0.5f,  0.5f, -0.5f,
	   -0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f  //top 4 corners
	};

	//Topology for the unit cube
	constexpr std::array<GLuint, 12 * 3> UnitCubeTopology = {
		0, 1, 2,  0, 2, 3, // bottom
		4, 5, 6,  4, 6, 7, // top

		0, 1, 5,  0, 5, 4, // front
		3, 2, 6,  3, 6, 7, // right

		1, 5, 6,  1, 6, 2, // front        
		0, 4, 7,  0, 7, 3  // back
	};


	constexpr std::array<float, 3 * 24 * 2> UnitCube3D24WNormals = {
	   //Bottom 4 vertexes in counter clockwise order
	  //xpos  ypos   zpos   xnorm   ynorm  znorm
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//0
	   -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  //1			//0
	   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -3.0f / 2.0f,	//2

		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	//3
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,	//4			//1
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -3.0f / 2.0f,	//5

		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	//6
		0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	//7			//2
		0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 3.0f / 2.0f,	//8

	   -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	//9
	   -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	//10		//3 
	   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 3.0f / 2.0f,	//11

	   //Top 4 vertexes in counter clockwise order
	   -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//12
	   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	//13		//4
	   -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -3.0f/2.0f,	//14

		0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	//15  
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	//16		//5
		0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -3.0f / 2.0f,	//17 

		0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	//18
		0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	//19		//6
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 3.0f / 2.0f,	//20

	   -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	//21
	   -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	//22		//7
	   -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 3.0f / 2.0f	//23   
	};

	constexpr std::array<GLuint, 6 * 3 *2> UnitCube3DTopologyTriangles24 = {
		1, 4, 7,     7, 10, 1,		// bottom 
		13, 16, 19,  19, 22, 13,    // top

		0, 3, 15,  15, 12, 0,		// front
		5, 8, 20,  20, 17, 5,		// right

		2, 11, 23,  23, 14, 2,		// left      
		9, 6, 18,  18, 21, 9		// far
	};

	/**
	* @brief Creates the vertices for a grid of given size
	*
	* @param x - Number of rows for the grid
	* @param y - Number of columns for the grid
	* @return indices - address of the array indices is returned
	*/
	template <typename T, typename U>
	std::vector<float> UnitGridGeometry2D(T x, U y) {
		//Always 1 more row and column comapred to number of squares in row and column
		const int size = (x + 1) * (y + 1) * 2;	
		std::vector <float> vertexes;
		vertexes.resize(size);
		int h = 0;
		for (int i = 0; i < x + 1 ; i++) {
			GLfloat xCoordinate = (float)i / (float)x;		//-0.5 to 0.5 with 1/x increments for rows
			for (int j = 0; j < y + 1; j++) {
				GLfloat yCoordinate = (float)j / (float)y;  //Same as above for columns
				
				//Normalizing the coordinates
				vertexes[h++] = xCoordinate - 0.5f; 
				vertexes[h++] = yCoordinate - 0.5f;
			}
		}
		return vertexes;
	}

	/**
	* @brief Creates the vertices for a grid of given size
	*
	* @param x - Number of rows for the grid
	* @param y - Number of columns for the grid
	* @return indices - address of the array indices is returned
	*/
	template <typename T, typename U>
	std::vector <GLuint> UnitGridTopologyTriangles(T X, U Y) {
		std::vector <GLuint> indices;
		//rows * columns, * 3 because 2 triangles per square in the grid	
		indices.resize(X * Y * 3 * 2);
		int count = 0;
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				//first triangle in the current square
				indices[count++] = ((Y + 1) * i) + j;			  //Bottom left vertex
				indices[count++] = (Y + 1) * (i + 1) + j;	      //Top left vertex
				indices[count++] = (Y + 1) * (i + 1) + j + 1;     //Top right vertex
				//second triangle in the current square
				indices[count++] = ((Y + 1) * i) + j;			  //Bottom left vertex
				indices[count++] = ((Y + 1) * i) + j + 1;		  //Bottom right vertex
				indices[count++] = (Y + 1) * (i + 1) + j +1;      //Top right vertex
			}
		}
		return indices;
	}
	
	/**
	* @brief Creates the vertices for a grid of given size with texture coordinates aswell
	*
	* @param x - Number of rows for the grid
	* @param y - Number of columns for the grid
	* @return indices - address of the array indices is returned
	*/
	template <typename T, typename U>
	std::vector<float> UnitGridGeometry2DWTCoords(T x, U y)
	{
		const int size = (x + 1) * (y + 1) * 4;
		std::vector <float> vertexes;
		vertexes.resize(size);
		int h = 0;
		//float zCoordinate = 0.0f;
		for (int i = 0; i < x + 1; i++) {
			GLfloat xCoordinate = (float)i / (float)x;
			for (int j = 0; j < y + 1; j++) {
				GLfloat yCoordinate = (float)j / (float)y;
				//float color = (float)((i + j) % 2);

				//Normalizing the coordinates
				vertexes[h++] = xCoordinate - 0.5f;
				vertexes[h++] = yCoordinate - 0.5f;
				vertexes[h++] = xCoordinate + 0.5f;
				vertexes[h++] = yCoordinate + 0.5f;
			}
		}
		return vertexes;
	}

}
#endif