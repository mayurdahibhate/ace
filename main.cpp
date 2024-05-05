#include "ace_engine.h"

GLuint shaderProgramObject = 0;

enum
{
	AMC_ATTRIBUTE_POSITION,
	AMC_ATTRIBUTE_COLOR
};

Mesh cube;

GLuint vao_cube = 0;

GLuint vbo_position_cube = 0;
GLuint vbo_color_cube = 0;

GLuint mvpMatrixUniform = 0;

mat4 perspectiveProjectionMatrix;

GLfloat angle_cube = 0.0f;

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
			{GL_VERTEX_SHADER, "./shaders/basic.vert"},
			{GL_FRAGMENT_SHADER, "./shaders/basic.frag"},
			{GL_NONE, NULL}};

	shaderProgramObject = LoadShaders(shaders);
	glUseProgram(shaderProgramObject);

	// get shader uniform location
	mvpMatrixUniform = glGetUniformLocation(shaderProgramObject, "uMVPMatrix");



	vector<vec3> cubePositions;

	cubePositions = vector<vec3> {
		{-1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f,-1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f,-1.0f},
		{1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f,-1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f}
	};

	vector<GLuint> indices = {};

	Mesh cube1(cubePositions, indices);
	vao_cube = cube1.prepare();

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
	rotationMatrix1 = vmath::rotate(angle_cube, 1.0f, 0.0f, 0.0f);

	mat4 rotationMatrix2 = vmath::mat4::identity();
	rotationMatrix2 = vmath::rotate(angle_cube, 0.0f, 1.0f, 0.0f);

	mat4 rotationMatrix3 = vmath::mat4::identity();
	rotationMatrix3 = vmath::rotate(angle_cube, 0.0f, 0.0f, 1.0f);

	rotationMatrix = rotationMatrix1 * rotationMatrix2 * rotationMatrix3;

	modelViewMatrix = translationMatrix * scaleMatrix * rotationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix; // order of multiplication is important

	// push above mvp vertex shader's mvp uniform
	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(vao_cube);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	glUseProgram(0);


	acewmSwapBuffers();
}

void update(void)
{
	// code
	angle_cube = angle_cube - 1.0f;

	if (angle_cube <= 0.0f)
	{
		angle_cube = angle_cube + 360.0f;
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
