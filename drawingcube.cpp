//OPENGL 4 EXAMPLE

#include <iostream>
using namespace std;

#include <math.h>     //sin and cos included in this header file.

//--- OpenGL --- The OpenGL Extension Wrangler Library
#include "gl/glew.h"
#include "gl/wglew.h"
#pragma comment(lib, "glew32.lib")
//--------------

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


#include "GL\freeglut.h"

#include "shaders/Shader.h"   // include shader header file, this is not part of OpenGL
//Shader.h has been created using common glsl structure


#include <math.h>     //sin and cos included in this header file.

#include "Cube.h"	//include declaration for your cube class

Cube myCube;	//create a cube object
Cube miniCube1;
Cube miniCube2;
Cube miniCube3;
int screenWidth=480, screenHeight=480;

glm::mat4 ProjectionMatrix;
glm::mat4 ModelViewMatrix;
glm::mat4 ModelViewMatrix2;

float AngleInDegrees = 0.0f;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void init();				//called in winmain when the program starts.
void reshape(int width, int height);

/*************    START OF OPENGL FUNCTIONS   ****************/

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; 
	screenHeight = height;

	glViewport(0,0,width,height);						// set Viewport dimensions

	//Calculate a projection matrix based on perspective viewing for 3d geometry
	//Increasing the first parameter of the ProjectionMatrix variable zooms out from the object. 
	//Once your faraway clipping is more than 45 since your dimension is 5 and you've pushed your perspective back by 40, you should be able to see all of the cube since it won't clip it away. 

	//Your 3rd parameter should be more than the 
	ProjectionMatrix = glm::perspective(glm::radians(40.0f), width / static_cast<float>(height), 0.1f, 60.0f);
}

void display()									
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//This is the general ViewMatrix that ensures that all our objects is behind our camera lense/space. 
	glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -40.0));
	
	//This is our rotation matrix. 
	glm::mat4 ModelMatrix = glm::rotate(glm::mat4(1.0), glm::radians(AngleInDegrees), glm::vec3(0.0, 1.0, 1.0));

	//This is for minicube 1. It is translated to 5,5,5 because the main cube has it's cube side length set to 5 and we want it at the corner. 
    glm::mat4 Cube2ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(5.0, 5.0, 5.0));
	
	//This is for the main cube 
	ModelViewMatrix = ViewMatrix * ModelMatrix;

	//This is for minicube. 
	//ViewMatrix* ModelMatrix*Cube2ModelMatrix --> put it's at the corner and make it rotate about the translated axis. 
	//ViewMatrix* ModelMatrix*Cube2ModelMatrix*ModelMatrix --> by multiplying the modelmatrix at the end, you are making the cube in itself spin. 
	ModelViewMatrix2 = ViewMatrix *ModelMatrix* Cube2ModelMatrix *ModelMatrix ;

	AngleInDegrees += 0.8f;
	if (AngleInDegrees > 360.0)
		AngleInDegrees = 0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	myCube.render(ModelViewMatrix, ProjectionMatrix);	//need to render your cube
	miniCube1.render(ModelViewMatrix2, ProjectionMatrix); //renders the minicube. 

	//To complete do the other mini cubes. 
	glutSwapBuffers();
}

void init()
{

	glClearColor(0.0,0.0,0.0,0.0);	//sets the clear colour
	glClearDepth(1.0);
					
	myCube.init(5.0);	//need to initialise your cube
	miniCube1.init(2.0);
	miniCube2.init(2.0);
	miniCube3.init(2.0);

	
	glEnable(GL_DEPTH_TEST);
	
	//Culling - it stops rendering triangle faces which face away from the camera.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void idle()
{
	glutPostRedisplay();
}

void keyfunction(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		//leaves the main loop and essentially exits the programme.
		glutLeaveMainLoop();
	}
}

/**************** END OPENGL FUNCTIONS *************************/

// FREEGLUT WINDOW SET UP
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Freetype font with 3d geometry");

	glutReshapeFunc(reshape);

	//This initialises glew - it must be called after the window is created.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << " GLEW ERROR" << endl;
	}

	//Check the OpenGL version being used
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
	cout << OpenGLVersion[0] << " " << OpenGLVersion[1] << endl;

	//initialise the objects for rendering
	init();

	//specify which function will be called to refresh the screen.
	glutDisplayFunc(display);

	glutKeyboardFunc(keyfunction);

	glutIdleFunc(idle);

	//starts the main loop. Program loops and calls callback functions as appropriate.
	glutMainLoop();

	return 0;
}