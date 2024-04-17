#include <stdio.h>
#include <GL/glew.h>

void printGLInfo(FILE *gpFile)
{
	// variable declarations
	GLint numExtensions;
	GLint i;

	// code
	fprintf(gpFile, "OpenGL Vendor 		: %s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer 	: %s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL Version		: %s\n", glGetString(GL_VERSION));
	fprintf(gpFile, "GLSL Version 		: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// listing of supported extensions
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

	fprintf(gpFile, "\nNumber of OpenGL Extensions Supported : %i\n", numExtensions);
	fprintf(gpFile, "=========================================================================.\n");

	for (i = 0; i < numExtensions; i++)
	{
		fprintf(gpFile, "%s\n", glGetStringi(GL_EXTENSIONS, i));
	}

	fprintf(gpFile, "=========================================================================.\n");
}
