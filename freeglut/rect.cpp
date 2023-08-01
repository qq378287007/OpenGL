
#include <iostream>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#include <GL/glut.h>

GLenum doubleBuffer;
GLint thing1, thing2;

static void Args(int argc, char **argv)
{
	doubleBuffer = GL_FALSE;

	for (GLint i = 1; i < argc; i++)
		if (strcmp(argv[i], "-sb") == 0)
			doubleBuffer = GL_FALSE;
		else if (strcmp(argv[i], "-db") == 0)
			doubleBuffer = GL_TRUE;
}

static void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearAccum(0.0, 0.0, 0.0, 0.0);

	thing1 = glGenLists(1);
	glNewList(thing1, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glRectf(-1.0, -1.0, 1.0, 0.0);
	glEndList();

	thing2 = glGenLists(1);
	glNewList(thing2, GL_COMPILE);
	glColor3f(0.0, 1.0, 0.0);
	glRectf(0.0, -1.0, 1.0, 1.0);
	glEndList();
}

static void showGlutInfo()
{
	const GLubyte *name = glGetString(GL_VENDOR);
	const GLubyte *biaoshifu = glGetString(GL_RENDERER);
	const GLubyte *OpenGLVersion = glGetString(GL_VERSION);
	const GLubyte *gluVersion = gluGetString(GLU_VERSION);

	std::cout << "OpenGL实现厂商的名字：" << name << std::endl;
	std::cout << "渲染器标识符：" << biaoshifu << std::endl;
	std::cout << "OpenGL实现的版本号：" << OpenGLVersion << std::endl;
	std::cout << "OGLU工具库版本：" << gluVersion << std::endl;
}

static void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case '2':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}

static void Draw(void)
{
	glPushMatrix();

	glScalef(0.8, 0.8, 1.0);

	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(thing1);
	glAccum(GL_LOAD, 0.5);

	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(thing2);
	glAccum(GL_ACCUM, 0.5);

	glAccum(GL_RETURN, 1.0);

	glPopMatrix();

	if (doubleBuffer)
		glutSwapBuffers();

	else
		glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	Args(argc, argv);

	GLenum type = GLUT_RGB | GLUT_ACCUM;
	type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
	glutInitDisplayMode(type);
	glutInitWindowSize(300, 300);
	glutCreateWindow("Accum Test");

	Init();

	showGlutInfo();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutDisplayFunc(Draw);
	glutMainLoop();

	return 0;
}
