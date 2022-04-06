
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PINK     1.0, 0.0, 1.0, 0.0
#define BROWN    0.5, 0.35, 0.05, 1.0
#define PI		 3.14159



GLint		wScreen = 1200, hScreen = 800;
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;
float marioX = 0.0f;
float marioY = 0.0f;
GLfloat  rVisao = 20, aVisao = 0.5*PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao*cos(aVisao), 4.0, rVisao*sin(aVisao) };
GLfloat  incZoom = 3;
GLfloat ytam = 2;






void inicializa(void)
{
	glClearColor(BLACK);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

}


void drawRectangle(float x, float y, float z) {

	glBegin(GL_QUADS);
	// Top face (y = 1.0f)

	glVertex3f((x), (y), -(z));
	glVertex3f(-(x), (y), -(z));
	glVertex3f(-(x), (y), (z));
	glVertex3f((x), (y), (z));

	// Bottom face (y = -1.0f)   
	glVertex3f((x), -(y), (z));
	glVertex3f(-(x), -(y), (z));
	glVertex3f(-(x), -(y), -(z));
	glVertex3f((x), -(y), -(z));

	// Front face  (z = 1.0f)   
	glVertex3f((x), (y), (z));
	glVertex3f(-(x), (y), (z));
	glVertex3f(-(x), -(y), (z));
	glVertex3f((x), -(y), (z));

	// Back face (z = -1.0f)

	glVertex3f((x), -(y), -(z));
	glVertex3f(-(x), -(y), -(z));
	glVertex3f(-(x), (y), -(z));
	glVertex3f((x), (y), -(z));

	// Left face (x = -1.0f)
	glVertex3f(-(x), (y), (z));
	glVertex3f(-(x), (y), -(z));
	glVertex3f(-(x), -(y), -(z));
	glVertex3f(-(x), -(y), (z));

	// Right face (x = 1.0f)
	glVertex3f((x), (y), -(z));
	glVertex3f((x), (y), (z));
	glVertex3f((x), -(y), (z));
	glVertex3f((x), -(y), -(z));
	glEnd();

}

void drawStairs(float y) {
	glPushMatrix();
	drawRectangle(0.2f, y, 1.0f);
	glTranslatef(4.0f, 0.0f, 0.0f);
	drawRectangle(0.2f, y, 1.0f);
	glTranslatef(-2.0f, -(y), 0.0f);
	for (int i = 0; i < (y) * 2; i++) {
		glTranslatef(0.0f, 1.0f, 0.0f);
		drawRectangle(2.0f, 0.1f, 1.0f);
	}
	glPopMatrix();
}

void drawLata() {
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 1.0f, 1.0f, 2.0f, 32, 32);
}

void mario(void) {
	glColor4f(BLUE);
	glTranslatef(marioX, marioY, 0);
	drawRectangle(1, 1, 1);
}


void keyboard_s(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': marioX -= 0.25f;
		glutPostRedisplay();
		break;
	case 'd': marioX += 0.25f;
		glutPostRedisplay();
		break;
	case 'w': marioY += 0.25f;
		glutPostRedisplay();
		break;
	case 's': marioY -= 0.25f;
		glutPostRedisplay();
		break;
	}
}
void drawScene() {

	//floor
	glColor4f(RED);
	glPushMatrix();
	drawRectangle(30.0, 2.0, 1.0);
	glTranslatef(0.0f, 8.0f, 0.0f);
	drawRectangle(30.0, 2.0, 1.0);
	glTranslatef(0.0f, 8.0f, 0.0f);
	drawRectangle(30.0, 2.0, 1.0);
	glTranslatef(0.0f, 8.0f, 0.0f);
	drawRectangle(30.0, 2.0, 1.0);
	glTranslatef(0.0f, 8.0f, 0.0f);
	drawRectangle(10.0, 2.0, 1.0);
	glPopMatrix();

	//stairs
	glColor4f(BROWN);
	glPushMatrix();
	glTranslatef(6.0f, 4.0f, 0.0f); // onde queres desenhar as escadas
	drawStairs(2);
	glTranslatef(-20.0f, 8.0f, 0.0f); // onde queres desenhar as escadas
	drawStairs(2);
	glTranslatef(25.0f, 8.0f, 0.0f); // onde queres desenhar as escadas
	drawStairs(2);
	glTranslatef(-5.0f, 8.0f, 0.0f);
	drawStairs(2);
	glPopMatrix();

	//Latas

	glColor4f(YELLOW);
	glPushMatrix();
	glTranslatef(-28.0f, 28.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLata();
	glTranslatef(3.0f, 0.0f, 0.0f);
	drawLata();
	glPopMatrix();

	//Mario

	glColor4f(BLUE);
	glPushMatrix();
	glTranslatef(-20.0f, 3.0f, 0.0f);
	mario();
	glPopMatrix();

	//Princess
	glColor4f(PINK);
	glPushMatrix();
	glTranslatef(0.0f, 36.0f, 0.0f);
	drawRectangle(1.0f, 2.0f, 1.0f);
	glPopMatrix();

	//Kong
	glColor4f(GREEN);
	glPushMatrix();
	glTranslatef(-20.0f, 28.0f, 0.0f);
	drawRectangle(2.0f, 2.0f, 1.0f);
	glPopMatrix();

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110, (float)wScreen / hScreen, 0.5, 5 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], 12 + obsP[1], 12 + obsP[2], 0, 12, 0, 0, 1, 0);

	//??????????????????????????????????????????????????????????Objectos 
	drawScene();

	glutSwapBuffers();
}


void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP)
		obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN)
		obsP[1] = (obsP[1] - 0.1);


	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.05);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.05);

	obsP[0] = rVisao * cos(aVisao);
	obsP[2] = rVisao * sin(aVisao);


	glutPostRedisplay();

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("DonkeyKong ");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutKeyboardFunc(keyboard_s);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}



