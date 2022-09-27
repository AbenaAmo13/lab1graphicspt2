
#include "gl\glew.h"

#include "shaders\Shader.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


class Cube
{
private:
	float dim;
	GLuint m_vaoID;		    // vertex array object
	GLuint m_vboID[2];		// two VBOs - used for colours and vertex data
	GLuint ibo;                     //identifier for the triangle indices

	const static int numOfVerts = 8;
	const static int numOfTris = 12;
	const static int numOfValuesPerVertex = 3;
	const static int numOfVertsPerTriangle = 3;
	
	float verts[numOfVerts*3];
	float cols[numOfVerts*3];
	unsigned int tris[numOfTris *3];

	CShader myShader;

	void setDim(float d);
	void constructGeometry();

public:
	Cube();	
	void init(float cubeSideLength);
	void render(glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
};