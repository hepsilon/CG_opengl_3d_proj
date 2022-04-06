#include <windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include <string>
#include <vector>
#include <iostream>

#include "RgbImage.h"
#include "material.h"

#define BLUE     0.0f, 1.0f, 1.0f, 1.0f
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GREY	 0.1, 0.1, 0.2
#define PI		 3.14159
#define MAX_PART 500
GLint		wScreen = 1200, hScreen = 800,flageye=0;
GLuint		texarray[200];
GLuint		mtxtex[19];
GLuint		mtxcntr = 0;
GLuint		framecntr = 0;
GLuint		tex;

RgbImage	img;

GLfloat		xC = 10.0, yC = 10.0, zC = 10.0,ang1=0,ang2=0;
GLfloat		eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ;

GLfloat  visionRad = 20, visionA = 0.5*PI, incVisao = 0.05;
GLfloat  obsP[] = { visionRad*cos(visionA), 4.0, visionRad*sin(visionA) };

GLfloat lightColor[] = { 0.5, 0.5, 0.5 };
GLfloat down[] = { 0,-1,0,1 };

typedef struct {

	bool alive;
	float life;
	float death;
	float xpos;
	float ypos;
	float zpos;
	float vel;
	float gravity;
}part;
part par_sys[MAX_PART];
int velocity = 0;
void initParticles(int i) {
	par_sys[i].alive = true;
	par_sys[i].life = 1.0;
	par_sys[i].death = float(rand() % 100) / 1000.0f + 0.003f;

	par_sys[i].xpos = (float)(rand() %100) - 50;
	par_sys[i].ypos = -10.0;
	par_sys[i].zpos = (float)(rand() % 100) - 50;



	par_sys[i].vel = velocity;
	par_sys[i].gravity = -0.1;//-0.8;

}
void defTextures() {
	glGenTextures(1, &texarray[0]); //brick wall
	glBindTexture(GL_TEXTURE_2D, texarray[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("brick2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());

	glGenTextures(1, &texarray[1]); //marble black
	glBindTexture(GL_TEXTURE_2D, texarray[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("neonb.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());

	glGenTextures(1, &texarray[2]); //marble black
	glBindTexture(GL_TEXTURE_2D, texarray[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("neong.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());
	
	glGenTextures(1, &texarray[3]);
	glBindTexture(GL_TEXTURE_2D, texarray[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("up.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());

	glGenTextures(1, &texarray[4]);
	glBindTexture(GL_TEXTURE_2D, texarray[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("down2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());

	glGenTextures(1, &texarray[5]);
	glBindTexture(GL_TEXTURE_2D, texarray[5]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("front.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());

	glGenTextures(1, &texarray[6]);
	glBindTexture(GL_TEXTURE_2D, texarray[6]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("back.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());


	glGenTextures(1, &texarray[7]);
	glBindTexture(GL_TEXTURE_2D, texarray[7]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("left.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());

	glGenTextures(1, &texarray[8]);
	glBindTexture(GL_TEXTURE_2D, texarray[8]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	img.LoadBmpFile("right.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());
	char const* c;
	for (int i = 0; i < 19; i++) {
		glGenTextures(1, &mtxtex[i]);
		glBindTexture(GL_TEXTURE_2D, mtxtex[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		std::string s = std::to_string(i);
		s = "matrix" + s + ".bmp";
		c = s.c_str();
		img.LoadBmpFile(c);
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			img.GetNumCols(),
			img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
			img.ImageData());
	}
}
void chooseMtrl(int i) {
	GLfloat dAmb[] = { 0.2472,0.1995,0.0745 };
	GLfloat Dif[] = { 0.7516,0.6064,0.2264 };
	GLfloat Spec[] = { 0.6282,0.5558,0.3660 };
	GLfloat Coef = 500;
	if (i == 0) {

		GLfloat dAmb[] = { 0.2472,0.1995,0.0745 };
		GLfloat Dif[] = { 0.7516,0.6064,0.2264 };
		GLfloat Spec[] = { 0.6282,0.5558,0.3660 };
		GLfloat Coef = 500;
	}
	else if (i == 1) {

		GLfloat dAmb[] = { 0.2472,0.1995,0.0745 };
		GLfloat Dif[] = { 0.7516,0.6064,0.2264 };
		GLfloat Spec[] = { 0.6282,0.5558,0.3660 };
		GLfloat Coef = 500;
	}
	else if (i == 2) {

		GLfloat dAmb[] = { 0.2472,0.1995,0.0745 };
		GLfloat Dif[] = { 0.7516,0.6064,0.2264 };
		GLfloat Spec[] = { 0.6282,0.5558,0.3660 };
		GLfloat Coef = 500;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, dAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Spec);
	glMaterialf(GL_FRONT, GL_SHININESS, Coef);
}

void drawRect(float x, float y, float z,int texnum) {

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texarray[texnum]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_QUADS);
	// Top face (y = 1.0f)

	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), (y), -(z));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(x), (y), -(z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(x), (y), (z));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((x), (y), (z));

	// Bottom face (y = -1.0f)   
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), -(y), (z));
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-(x), -(y), (z));
	glTexCoord2f(2.0f, 2.0f); glVertex3f(-(x), -(y), -(z));
	glTexCoord2f(0.0f, 2.0f); glVertex3f((x), -(y), -(z));
	// Front face  (z = 1.0f)   
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), (y), (z));
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-(x), (y), (z));
	glTexCoord2f(2.0f, 2.0f); glVertex3f(-(x), -(y), (z));
	glTexCoord2f(0.0f, 2.0f); glVertex3f((x), -(y), (z));

	// Back face (z = -1.0f)

	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), -(y), -(z));
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-(x), -(y), -(z));
	glTexCoord2f(2.0f, 2.0f); glVertex3f(-(x), (y), -(z));
	glTexCoord2f(0.0f, 2.0f); glVertex3f((x), (y), -(z));

	// Left face (x = -1.0f)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(x), (y), (z));
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-(x), (y), -(z));
	glTexCoord2f(2.0f, 2.0f); glVertex3f(-(x), -(y), -(z));
	glTexCoord2f(0.0f, 2.0f); glVertex3f(-(x), -(y), (z));


	// Right face (x = 1.0f)
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), (y), -(z));
	glTexCoord2f(2.0f, 0.0f); glVertex3f((x), (y), (z));
	glTexCoord2f(2.0f, 2.0f); glVertex3f((x), -(y), (z));
	glTexCoord2f(0.0f, 2.0f); glVertex3f((x), -(y), -(z));
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

}
void drawFace(float x, float y, float z){
	//glColor3f(0.1f, 0.2f, 0.2f);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texarray[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), (y), -(z));
	glTexCoord2f(4.f, 0.0f); glVertex3f((x), (y), (z));
	glTexCoord2f(4.f, 6.f); glVertex3f((x), -(y), (z));
	glTexCoord2f(0.0f, 6.f); glVertex3f((x), -(y), -(z));

	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
}
void drawStairs(int nstairs,float x,float y, float z) {
	float c=y;

	glPushMatrix();
		glTranslatef(-5, -5, 0);
		for (int i = 0; i < nstairs; i++) {
			if (i % 2 != 0) {
				drawRect(x, c, z,1);
				//glColor3f(0.1f, 0.1f, 0.2f);//Dark grey
			}
			else {
				drawRect(x, c, z,2);
				//glColor3f(0, 0, 0);//Black
			}
			glTranslatef(x+0.5, y, 0.0f);
			c += y;
		}
	glPopMatrix();
}
void drawSky() {
	GLfloat x = 200;
	GLfloat y = 200;
	GLfloat z = 200;
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texarray[4]);
	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), (y), -(z));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(x), (y), -(z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(x), (y), (z));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((x), (y), (z));
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	//bot
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texarray[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), -(y), (z));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(x), -(y), (z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(x), -(y), -(z));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((x), -(y), -(z));
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	//front
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mtxtex[mtxcntr]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f); glVertex3f((x), (y), (z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(x), (y), (z));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(x), -(y), (z));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), -(y), (z));
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	//back 
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mtxtex[mtxcntr]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f((x), -(y), -(z));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(x), -(y), -(z));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(x), (y), -(z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((x), (y), -(z));
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	//left
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mtxtex[mtxcntr]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(x), (y), (z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(x), (y), -(z));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(x), -(y), -(z));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(x), -(y), (z));
	glEnd();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	//right
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mtxtex[mtxcntr]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f((x), (y), -(z));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((x), (y), (z));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((x), -(y), (z));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((x), -(y), -(z));
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	framecntr++;
	if (framecntr == 10) {
		framecntr = 0;
		mtxcntr++;
	}
	if (mtxcntr == 19) {
		mtxcntr = 0;
	}

}
void drawScene() {
	
	GLfloat Posicao[] = { 0.0, 0.0, 15.0 ,1. };
	//mudar material escadas para marmore paredes para pedra
	glLightfv(GL_LIGHT0, GL_POSITION, Posicao);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, down);
	GLfloat dAmb[] = {0.2472,0.1995,0.0745 };
	GLfloat Dif[] = {0.7516,0.6064,0.2264 };
	GLfloat Spec[] = {0.6282,0.5558,0.3660 };
	GLfloat Coef = 500;
	//chooseMtrl(1);
	//glPushMatrix();
	//glTranslatef(0, -2.5, -20);
		glMaterialfv(GL_FRONT, GL_AMBIENT, dAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Spec);
		glMaterialf(GL_FRONT, GL_SHININESS, Coef);
		
	//glPopMatrix();
	glPushMatrix();
		drawStairs(10, 0.5, 0.5, 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-30, 0, 0);
		glRotatef(180, 0.f, 1.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,15,15);
		glRotatef(90, -1.f, 0.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-30, 15, -15);
		glRotatef(180, 0.f, 1.f, 0.f);
		glRotatef(90, -1.f, 0.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-15, 30, 15);
		glRotatef(90, 0.f, -1.f, 0.f);
		glRotatef(90, 0.f, 0.f, 1.f);
		drawStairs(10, 0.5, 0.5, 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-15, 30, -15);
		glRotatef(90, 0.f, 1.f, 0.f);
		glRotatef(90, 0.f, 0.f, 1.f);
		drawStairs(10, 0.5, 0.5, 3);
	glPopMatrix();

	/*
		drawStairs(10, 0.5, 0.5, 3);
		
		glTranslatef(-15,0, 0);
		glRotatef(180, 0.f, 1.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
		
		glTranslatef(0, 15, 20);
		glRotatef(90, -1.f, 0.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
		
		glTranslatef(-15, 35, 0);
		glRotatef(180,0.f, 1.f, 0.f);
		glRotatef(180, 0.5f, 0.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
		
		glTranslatef(-5,5, 20);
		glRotatef(90, -1.f, 0.f, 0.f);
		glRotatef(90, 0.f, 1.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);

		glTranslatef(-15, 0, 0);
		glRotatef(180, 0.f, 1.f, 0.f);
		drawStairs(10, 0.5, 0.5, 3);
		
		//glTranslatef(9.5, 4.5, 0);
		*/
	glPushMatrix();
		glTranslatef(5,15, 0);
		drawFace(0, 20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-35.001, 15, 0);
		drawFace(0, 20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-35, 15, 0);
		glRotatef(180, 0.f, 1.f, 1.f);
		drawFace(0, 20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5.001, 15, 0);
		glRotatef(180, 0.f, 1.f, 1.f);
		drawFace(0, 20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-15, -5, 0);
		glRotatef(180, 1.f, 1.f, 0.f);
		drawFace(0, 20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-15, 34.6, 0);
		glRotatef(180, 1.f, 1.f, 0.f);
		glRotatef(90, 1.f, 0.f,0.f);
		drawFace(0, 20, 5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-15., 22.0, 20.1+0.6);
		glRotatef(90, 0.f, 1.f, 0.f);
		drawFace(0, 20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-15., 22.0, -20.1 - 0.6);
		glRotatef(90, 0.f, 1.f, 0.f);
		drawFace(0,20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2.5, 15 - 0.5, 20 + 0.6);
		glRotatef(90, 0.f, 1.f, 0.f);
		glRotatef(90, 1.f, 0.f, 0.f);
		drawFace(0,20, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-27.5, 15 - 0.5, -20 - 0.6);
		glRotatef(90, 0.f, 1.f, 0.f);
		glRotatef(90, 1.f, 0.f, 0.f);
		drawFace(0,20, 5);
	glPopMatrix();

	
}
void drawRain() {
	glPushMatrix();
	float Lt0spec[4] = { 1.0, 1.0, 1.0, 1.0 };
	float Noemit[4] = { 0.0, 0.0, 0.0, 1.0 };
	float x, y, z;
	for (int loop = 0; loop < MAX_PART; loop = loop +1) {
		if (par_sys[loop].alive == true) {
			x = par_sys[loop].xpos;
			y = par_sys[loop].ypos;
			z = par_sys[loop].zpos;

			// Draw particles
			//glColor3f(0.5, 0.1, 0.5);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Lt0spec);
			glBegin(GL_LINES);
			glVertex3f(x, y, z);
			glVertex3f(x, y + 0.5, z);
			glEnd();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
			// Update values
			//Move
			// Adjust slowdown for speed!
			par_sys[loop].ypos -= par_sys[loop].vel;
			par_sys[loop].vel += par_sys[loop].gravity;
			// Decay
			par_sys[loop].life -= par_sys[loop].death;

			if (par_sys[loop].ypos >= 50) {
				par_sys[loop].life = -1.0;
			}
			//Revive
			if (par_sys[loop].life < 0.0) {
				initParticles(loop);
			}
		}
	}
	glPopMatrix();
}


void changEye(int num) {
	float g_RotateX = 0.0f;
	float g_RotationSpeed = 2.f;

	if (num == 0) {
		eyeX = -15.f;
		eyeY = 15.f;
		eyeZ = 0.f;
		centerX = 15 * cos(ang1);
		centerY = 15 * cos(ang2);
		centerZ = 15 * sin(ang1);
		upX = 0.f;
		upY = 1.f;
		upZ = 0.f;

	}
	if (num == 1) { // up
		ang2 += 0.1;
		
	}
	if (num == 2) { // down
		ang2 -= 0.1;
	}
	if (num == 3) { // left
		ang1 -= 0.1;
		
	}
	if (num == 4) { //right
		ang1 += 0.1;
		

	}
	
	centerX = 15 * cos(ang1);
	centerY = 15 * -cos(ang2);
	centerZ = 15 * sin(ang1);
	glutPostRedisplay();
}
void movement(int key,int x,int y) {
	if (key == GLUT_KEY_UP)
		changEye(1);
	if (key == GLUT_KEY_DOWN)
		changEye(2);
	if (key == GLUT_KEY_LEFT)
		changEye(3);
	if (key == GLUT_KEY_RIGHT)
		changEye(4);
	glutPostRedisplay();
}
void usekeys(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'r':
		lightColor[0] = 1;
		lightColor[1] = 0;
		lightColor[2] = 0;
		break;
	case 'g':
		lightColor[0] = 0;
		lightColor[1] = 1;
		lightColor[2] = 0;
		break;
	case 'b':
		lightColor[0] = 0;
		lightColor[1] = 0;
		lightColor[2] = 1;
		break;
	case 'l':
		lightColor[0] = 1;
		lightColor[1] = 1;
		lightColor[2] = 1;
		break;
	case 27:
		exit(0);
	}
}
void idle() {
	glutPostRedisplay();
}

void initLight() {
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	GLfloat Posicao[] = { 0.0, 0.0, 0.0 ,1.};
	GLfloat CorAmbiente[] = {0.5,0.0,0.0};
	GLfloat CorDifusa[] = { 0.3, 0.5, 0.3, 0.5 };
	GLfloat Corspec[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat atLinear = 0.05;
	GLfloat atConst= 0.06;
	GLfloat atQuadr = 0.05;
	GLfloat atSpecul = 0.05;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, CorDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Corspec);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atConst);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, atLinear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, atQuadr);

}
void init(void) {

	//glClearColor(BLACK);
	glClearColor(0.2, 0.2, 0.4, 1);
	glShadeModel(GL_SMOOTH);
	initLight();
	defTextures();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//glShadeModel(GL_SMOOTH);
	for (int loop = 0; loop < MAX_PART; loop++) {
		initParticles(loop);
	}
	PlaySound("Inner Animal.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_CULL_FACE);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)wScreen / hScreen, 0.5, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	changEye(flageye);
	flageye = 5;
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	//gluLookAt(obsP[0]-20, obsP[1]+8, obsP[2]-20, 0,0 , 0, 0, 1, 0);
	drawSky();
	drawRain();
	drawScene();

	glutSwapBuffers();
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Stairs ");

	//initLight();
	init();
	glutSpecialFunc(movement);
	glutKeyboardFunc(usekeys);
	glutDisplayFunc(display);

	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}