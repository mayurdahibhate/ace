// Windows header files

// OpenGL headers
#include <GL/glew.h> // this must be included before gl/GL.h
#include <GL/gl.h>

#include "include/vmath.h"
using namespace vmath;

#include "include/OGL.h"
#include "include/window_manager.h"
#include "include/LoadShaders.h"
// #include "include/printGLinfo.h"

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// link with OpenGL library
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

// global variable declarations
FILE* gpFile = NULL;

GLuint shaderProgramObject = 0;

enum 
{
	AMC_ATTRIBUTE_POSITION,
	AMC_ATTRIBUTE_COLOR
};

GLuint vao_cube = 0;

GLuint vbo_position_cube = 0;
GLuint vbo_color_cube = 0;

GLuint mvpMatrixUniform = 0;

mat4 perspectiveProjectionMatrix;

GLfloat cAngle = 0.0f;

void init(void);
void uninit();

void keyboard(unsigned int);
void draw(void);
void update(void);
void resize(int, int);


// entry point function
int main(int argc, char **argv)
{
	acewmInitializeCallback(init);

	acewmKeyboardCallback(keyboard);
	acewmReshapeCallback(resize);

	acewmDisplayCallback(draw);
	acewmUpdateCallback(update);

	acewmCreateWindow("ACE engine demo!!!", 100, 100, 800, 600);

	acewmEventLoop();

	acewmUninitiiizeCallback(uninit);

	return 0;

}

void keyboard(unsigned int)
{
	
}

void init(void)
{
	// function declarations
	// printGLInfo(gpFile);

	// initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		exit(1);
	}

	// shader program	
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "./shaders/shader.vs" },
        { GL_FRAGMENT_SHADER, "./shaders/shader.fs" },
        { GL_NONE, NULL }
    };

    shaderProgramObject = LoadShaders( shaders );
    glUseProgram( shaderProgramObject );

	// get shader uniform location
	mvpMatrixUniform = glGetUniformLocation(shaderProgramObject, "uMVPMatrix");

	const GLfloat cubePosition[] = {
        // top
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, 
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  

        // bottom
        1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,

        // front
        1.0f, 1.0f, 1.0f,
       -1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        // back
        1.0f, 1.0f, -1.0f,
       -1.0f, 1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        // right
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        // left
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 
		-1.0f, -1.0f, -1.0f, 
		-1.0f, -1.0f, 1.0f
	};

	const GLfloat cubeColor[] = {
		0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
	};

	const GLfloat cubeVertices[] = {
        // top
		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, 0.0f, 
		-1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  
		0.0f, 1.0f, 0.0f,
        
		// bottom
        1.0f, -1.0f, -1.0f,
        1.0f, 0.5f, 0.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, 0.5f, 0.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, 0.5f, 0.0f,

        // front
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,

        // back
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		
		// right
        1.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,

        // left
		-1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
        1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
        1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
        1.0f, 0.0f, 1.0f
	};

	// Vertex Array Object for cube
	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);

	// VBO for position
	glGenBuffers(1, &vbo_position_cube);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_cube);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// VBO for color
	glGenBuffers(1, &vbo_color_cube);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(AMC_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// enabling depth
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// set the clearColor() of window to blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// initialize perspective projection matrix
	perspectiveProjectionMatrix = vmath::mat4::identity();

	// return(0);
}


void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// set perspective projection matrix
	perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);	
}


void draw(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramObject);

	// transformations
	// pyramid
	mat4 modelViewMatrix = vmath::mat4::identity();
	mat4 modelViewProjectionMatrix = vmath::mat4::identity();
	mat4 translationMatrix = vmath::mat4::identity();
		
	mat4 rotationMatrix = vmath::mat4::identity();

	// cube	
	translationMatrix = vmath::translate(0.0f, 0.0f, -6.0f);

	mat4 scaleMatrix = vmath::mat4::identity();
	scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);

	mat4 rotationMatrix1 = vmath::mat4::identity();
	rotationMatrix1 = vmath::rotate(cAngle, 1.0f, 0.0f, 0.0f);

	mat4 rotationMatrix2 = vmath::mat4::identity();
	rotationMatrix2 = vmath::rotate(cAngle, 0.0f, 1.0f, 0.0f);

	mat4 rotationMatrix3 = vmath::mat4::identity();
	rotationMatrix3 = vmath::rotate(cAngle, 0.0f, 0.0f, 1.0f);

	rotationMatrix = rotationMatrix1 * rotationMatrix2 * rotationMatrix3;
	
	modelViewMatrix = translationMatrix * scaleMatrix * rotationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix; // order of multiplication is important

	// push above mvp vertex shader's mvp uniform
	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(vao_cube);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);

	glUseProgram(0);

	acewmSwapBuffers();
}

void update(void)
{
	// code
	cAngle = cAngle - 1.0f;

	if (cAngle <= 0.0f)
	{
		cAngle = cAngle + 360.0f;
	}
}

void uninit(void)
{
	// code
	DeleteShaderProg(shaderProgramObject);

	// cube
	if (vbo_color_cube)
	{
		glDeleteBuffers(1, &vbo_color_cube);
		vbo_color_cube = 0;
	}

	if (vbo_position_cube)
	{
		glDeleteBuffers(1, &vbo_position_cube);
		vbo_position_cube = 0;
	}

	// delete VAO
	if (vao_cube)
	{
		glDeleteVertexArrays(1, &vao_cube);
		vao_cube = 0;
	}
}
