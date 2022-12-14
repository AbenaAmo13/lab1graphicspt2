#include "Cube.h"
#include "shaders\Shader.h"

#include <iostream>

Cube::Cube()
{
	dim = 1.0;
	m_vaoID = 0;
	m_vboID[0] = 0;
	m_vboID[1] = 0;
	ibo = 0;
}

void Cube::render(glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	glUseProgram(myShader.GetProgramObjID());
	glBindVertexArray(m_vaoID);		// select VAO

	//set the uniform for the projectionmatrix
	glUniformMatrix4fv(glGetUniformLocation(myShader.GetProgramObjID(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	//pass the uniform for the ModelView matrix to the shader
	glUniformMatrix4fv(glGetUniformLocation(myShader.GetProgramObjID(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, numOfTris* numOfVertsPerTriangle, GL_UNSIGNED_INT, 0);
			
	glBindVertexArray(0); //unbind the vertex array object

	glUseProgram(0);
	
}

void Cube::init(float cubeSideLength)
{
	setDim(cubeSideLength);

	if (!myShader.CreateShaderProgram("BasicView", "glslfiles/basic.vert", "glslfiles/basic.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	constructGeometry();
}

void Cube::constructGeometry()
{
	// First simple object
	verts[0] = -dim;   verts[ 1] = -dim;  verts[ 2] = -dim;
	verts[3] = -dim;   verts[ 4] =  dim;  verts[ 5] = -dim;
	verts[6] =  dim;   verts[ 7] =  dim;  verts[ 8] = -dim;
	verts[9] =  dim;   verts[10] = -dim;  verts[11] = -dim;

	verts[12] = -dim;   verts[13] = -dim;  verts[14] = dim;
	verts[15] = -dim;   verts[16] =  dim;  verts[17] = dim;
	verts[18] =  dim;   verts[19] =  dim;  verts[20] = dim;
	verts[21] =  dim;   verts[22] = -dim;  verts[23] = dim;

	cols[0] = 0.0;   cols[ 1] = 0.0;  cols[ 2] = 0.0;
	cols[3] = 0.0;   cols[ 4] = 1.0;  cols[ 5] = 0.0;
	cols[6] = 0.0;   cols[ 7] = 0.0;  cols[ 8] = 1.0;
	cols[9] = 1.0;   cols[10] = 1.0;  cols[11] = 1.0;

	cols[12] = 1.0;   cols[13] = 0.0;  cols[14] = 0.0;
	cols[15] = 0.0;   cols[16] = 1.0;  cols[17] = 0.0;
	cols[18] = 0.0;   cols[19] = 0.0;  cols[20] = 1.0;
	cols[21] = 1.0;   cols[22] = 1.0;  cols[23] = 0.0;
	
	tris[0]=0; tris[1]=1; tris[2]=2;
	tris[3]=0; tris[4]=2; tris[5]=3;
	tris[6]=4; tris[7]=6; tris[8]=5;
	tris[9]=4; tris[10]=7; tris[11]=6;
	tris[12]=1; tris[13]=5; tris[14]=6;
	tris[15]=1; tris[16]=6; tris[17]=2;
	tris[18]=0; tris[19]=7; tris[20]=4;
	tris[21]=0; tris[22]=3; tris[23]=7;
	tris[24]=0; tris[25]=5; tris[26]=1;
	tris[27]=0; tris[28]=4; tris[29]=5;
	tris[30]=3; tris[31]=2; tris[32]=7;
	tris[33]=2; tris[34]=6; tris[35]=7;
		
	// VAO allocation
	glGenVertexArrays(1, &m_vaoID);

	// First VAO setup
	glBindVertexArray(m_vaoID);
	
	glGenBuffers(2, m_vboID);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	//initialises data storage of vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, numOfVerts* numOfValuesPerVertex *sizeof(GLfloat), verts, GL_STATIC_DRAW);
	GLint vertexLocation= glGetAttribLocation(myShader.GetProgramObjID(), "in_Position");
	glVertexAttribPointer(vertexLocation, numOfValuesPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexLocation);

	
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, numOfVerts* numOfValuesPerVertex *sizeof(GLfloat), cols, GL_STATIC_DRAW);
	GLint colorLocation= glGetAttribLocation(myShader.GetProgramObjID(), "in_Color");
	glVertexAttribPointer(colorLocation, numOfValuesPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLocation);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfTris * numOfVertsPerTriangle * sizeof(unsigned int), tris, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Cube::setDim(float d)
{
	dim = d;
}