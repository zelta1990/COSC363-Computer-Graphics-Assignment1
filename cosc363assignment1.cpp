//  ========================================================================
//  COSC363: Computer Graphics (2018);  University of Canterbury.
//
//  FILE NAME: cosc363assignment1.cpp
//  AUTHOR: XIAOSHI XIE
//  STUDENT ID: 22378644
//  ========================================================================
 
#include <fstream>
#include <cmath> 
#include <GL/freeglut.h>
#include "loadTGA.h"

using namespace std;

//constants
#define SKY_WIDTH 500.0
#define SKY_LENGTH 500.0
#define SKY_HEIGHT 500.0

//--Globals ---------------------------------------------------------------
int cam_hgt = 8; //Camera height
float theta = 15;
float wing_angle= 0, lip_angle=0, ufo_move=0, bullet_drop=0; 
int flag = -1, wing_flag=-1,lip_flag=-1,ufo_flag=-1, hit_flag=1, viewmode=1;
int rand_angle;
int shoot = 0;  //flag for switchin shooting stance
float bullet_dist = 0;  //the distance that bullet travels
float train_dist=0;  //distance the trains travels
float angle=0, fps_angle= 90,ex,ez=70,lx,lz=-1, fps_lx, fps_lz, fps_height=6.5;
float radius=3;
int nvrt;
double radian = 10*3.14/180;
float vx[31]={0,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.0,2.9,2.7,2.5,2.3,2.1,1.9,1.7,1.5,1.3,1.1,0.9,0.7,0.5,0.3,0.1,0};
float vy[31]={5,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,6,6.1,6.2,6.3,6.4,6.5,6.6,6.7,6.8,6.9,7.0,7.1,7.2,7.3,7.4,7.5,7.6,7.7,7.8,7.9,7.95,8}, vz[31]={0};   //Vertex list of revolved surface
float wx[31], wy[31], wz[31];   //Array for storing transformed vertices
float white[4] = {1., 1., 1., 1.}, black[4]={0,0,0,0}, grey[4] = { 0.2, 0.2, 0.2, 1.0 };
float yellow[4]={1,1,0,1},red[4]={1,0,0,1},green[4]={0,1,0,1};
float gx=0,gy=20,gz=-35, spot_dir[3]={0,-5,0};
GLuint textures[12];
GLUquadric *q;


void loadTextureImage()             //sourced from lab3
{
	glGenTextures(12, textures);
	
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	loadTGA("back.tga");
	printf("loaded");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	loadTGA("bottom.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	loadTGA("front.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	loadTGA("left.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	loadTGA("right.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	loadTGA("up.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	loadTGA("train_side.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	loadTGA("train_top_down.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	loadTGA("train_front_back.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	loadTGA("clock.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	loadTGA("clock_top_down.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_2D, textures[11]);
	loadTGA("floor.tga");
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void normal(float x1, float y1, float z1,            //sourced from lab4
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

void drawSkybox()                      
{
	glColor4d(0.0, 0.0, 0.1, 1);
    glDisable(GL_TEXTURE_2D);
    glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textures[5]);  //skybox top
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f,1.0f);
	glVertex3f(SKY_WIDTH, SKY_HEIGHT-5, -SKY_LENGTH);
	glTexCoord2d(1.0f,0.0f);
	glVertex3f(SKY_WIDTH, SKY_HEIGHT-5, SKY_LENGTH);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(-SKY_WIDTH, SKY_HEIGHT-5, SKY_LENGTH);
	glTexCoord2d(0.0f,1.0f);
	glVertex3f(-SKY_WIDTH, SKY_HEIGHT-5, -SKY_LENGTH);
    glEnd();
	glDisable(GL_TEXTURE_2D);

 	glEnable(GL_TEXTURE_2D);   
	glBindTexture(GL_TEXTURE_2D,textures[2]);  //skybox front
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(SKY_WIDTH, -5, SKY_LENGTH);
	glTexCoord2d(0.0f,1.0f);
	glVertex3f(SKY_WIDTH, SKY_HEIGHT-5, SKY_LENGTH);
	glTexCoord2d(1.0f,1.0f);
	glVertex3f(-SKY_WIDTH, SKY_HEIGHT-5, SKY_LENGTH);
	glTexCoord2d(1.0f,0.0f);
	glVertex3f(-SKY_WIDTH, -5, SKY_LENGTH);
    glEnd(); 
	glDisable(GL_TEXTURE_2D);

 	glEnable(GL_TEXTURE_2D);   	
	glBindTexture(GL_TEXTURE_2D,textures[0]);  //skybox back
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(-SKY_WIDTH, -5, -SKY_LENGTH);
	glTexCoord2d(0.0f,1.0f);
	glVertex3f(-SKY_WIDTH, SKY_HEIGHT-5, -SKY_LENGTH);
	glTexCoord2d(1.0f,1.0f);
	glVertex3f(SKY_WIDTH, SKY_HEIGHT-5, -SKY_LENGTH);
	glTexCoord2d(1.0f,0.0f);
	glVertex3f(SKY_WIDTH, -5, -SKY_LENGTH);
    glEnd(); 
	glDisable(GL_TEXTURE_2D);

 	glEnable(GL_TEXTURE_2D);       
	glBindTexture(GL_TEXTURE_2D,textures[3]);  //skybox left
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(SKY_WIDTH, -5, -SKY_LENGTH);
	glTexCoord2d(0.0f,1.0f);
	glVertex3f(SKY_WIDTH, SKY_HEIGHT-5, -SKY_LENGTH);
	glTexCoord2d(1.0f,1.0f);
	glVertex3f(SKY_WIDTH, SKY_HEIGHT-5, SKY_LENGTH);
	glTexCoord2d(1.0f,0.0f);
	glVertex3f(SKY_WIDTH, -5, SKY_LENGTH);
    glEnd();
	glDisable(GL_TEXTURE_2D); 

 	glEnable(GL_TEXTURE_2D);       
	glBindTexture(GL_TEXTURE_2D,textures[4]);  //skybox right
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(-SKY_WIDTH, -5, SKY_LENGTH);
	glTexCoord2d(0.0f,1.0f);
	glVertex3f(-SKY_WIDTH, SKY_HEIGHT-5, SKY_LENGTH);
	glTexCoord2d(1.0f,1.0f);
	glVertex3f(-SKY_WIDTH, SKY_HEIGHT-5, -SKY_LENGTH);
	glTexCoord2d(1.0f,0.0f);
	glVertex3f(-SKY_WIDTH, -5, -SKY_LENGTH);
    glEnd(); 	
	glDisable(GL_TEXTURE_2D);

 	glEnable(GL_TEXTURE_2D);      
	glBindTexture(GL_TEXTURE_2D,textures[1]);  //skybox bottom
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(-SKY_WIDTH, -5, SKY_LENGTH);
	glTexCoord2d(0.0f,1.0f);
	glVertex3f(-SKY_WIDTH, -5, -SKY_LENGTH);
	glTexCoord2d(1.0f,1.0f);
	glVertex3f(SKY_WIDTH, -5, -SKY_LENGTH);
	glTexCoord2d(1.0f,0.0f);
	glVertex3f(SKY_WIDTH, -5, SKY_LENGTH);
    glEnd(); 
	glDisable(GL_TEXTURE_2D);

}	

void drawCactus()
{
	glPushMatrix();
	glTranslatef(5, 4, 50);
	glScalef(2, 8,2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 4, 50);
	glScalef(1,4,2);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.5, 2.5, 50);
	glScalef(1,1,2);
	glutSolidCube(1);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(6.5, 4.5, 50);
	glScalef(2,1,2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, 6, 50);
	glScalef(1,3,2);
	glutSolidCube(1);
	glPopMatrix();			
	
}

void drawCactusShadow(){
	float shadowMat[16] = {gy,0,0,0, -gx,0,-gz,-1,0,0,gy,0, 0,0,0,gy};
	glDisable(GL_LIGHTING);
	glPushMatrix();          //draw shadow object
	glColor4f(0.2,0.2,0.2,1.0);
	glMultMatrixf(shadowMat);
    drawCactus();
	glPopMatrix();
}
void drawRoad()
{
	glColor4d(0., 0., 0.1, 1);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	glDisable(GL_TEXTURE_2D);
    glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-500, 1, 28);
	glVertex3f(-500, 1, 48);
	glVertex3f(500, 1, 48);
	glVertex3f(500, 1, 28);
	glEnd();
	
    glColor3f(1,1,1);             //white strips
    for(int i = 0; i<60;i+=1){
        glPushMatrix();
        glTranslatef(-400+i*15,1,38);
        glScalef(10, 0.01, 1);
        glutSolidCube(1);
        glPopMatrix();
    }

}

void drawEntrance()         //draw entrance of the station
{
	glColor3f(0., 0., 0.8);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
    glPushMatrix();          //front left
	  glTranslatef(-25,10,28);
	  glScalef(30,20,0.5);
	  glutSolidCube(1);
	glPopMatrix();
	
    glPushMatrix();          //front right
	  glTranslatef(25,10,28);
	  glScalef(30,20,0.5);
	  glutSolidCube(1);
	glPopMatrix();
	
    glPushMatrix();           //back left
	  glTranslatef(-25,10,12);
	  glScalef(30,20,0.5);
	  glutSolidCube(1);
	glPopMatrix();

    glPushMatrix();           //back right
	  glTranslatef(25,10,12);
	  glScalef(30,20,0.5);
	  glutSolidCube(1);
	glPopMatrix();	
	
	glPushMatrix();           //right wall
	  glTranslatef(40,10,20);
	  glScalef(0.5,20,16);
	  glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();          //left wall
	  glTranslatef(-40,10,20);
	  glScalef(0.5,20,16);
	  glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();          //roof
	  glTranslatef(0,22,20);
	  glScalef(80,5,16.5);
	  glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();          // opposite roof
	  glTranslatef(0,20,-35);
	  glScalef(80,1.5,16.5);
	  glutSolidCube(1);
	glPopMatrix();		

    glPushMatrix();           //opposite wall
	  glTranslatef(0,10,-40);
	  glScalef(80,20,0.5);
	  glutSolidCube(1);
	glPopMatrix();	
	
	
	glEnable(GL_TEXTURE_2D);   //tower body back
	glBindTexture(GL_TEXTURE_2D,textures[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-40,24.5,12);
	glTexCoord2f(0,1);glVertex3f(-40,34.5,12);
	glTexCoord2f(1,1);glVertex3f(-24,34.5,12);
	glTexCoord2f(1,0);glVertex3f(-24,24.5,12);
	glEnd();
	glDisable(GL_TEXTURE_2D);
		
	glEnable(GL_TEXTURE_2D);   //tower body front
	glBindTexture(GL_TEXTURE_2D,textures[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);glVertex3f(-40,24.5,28);
	glTexCoord2f(1,1);glVertex3f(-40,34.5,28);
	glTexCoord2f(0,1);glVertex3f(-24,34.5,28);
	glTexCoord2f(0,0);glVertex3f(-24,24.5,28);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);   //tower body left
	glBindTexture(GL_TEXTURE_2D,textures[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-40,24.5,28);
	glTexCoord2f(0,1);glVertex3f(-40,34.5,28);
	glTexCoord2f(1,1);glVertex3f(-40,34.5,12);
	glTexCoord2f(1,0);glVertex3f(-40,24.5,12);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);   //tower body right
	glBindTexture(GL_TEXTURE_2D,textures[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-24,24.5,12);
	glTexCoord2f(0,1);glVertex3f(-24,34.5,12);
	glTexCoord2f(1,1);glVertex3f(-24,34.5,28);
	glTexCoord2f(1,0);glVertex3f(-24,24.5,28);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);   //tower body top
	glBindTexture(GL_TEXTURE_2D,textures[10]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-40,34.5,12);
	glTexCoord2f(0,1);glVertex3f(-40,34.5,28);
	glTexCoord2f(1,1);glVertex3f(-24,34.5,28);
	glTexCoord2f(1,0);glVertex3f(-24,34.5,12);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);   //tower body bottom
	glBindTexture(GL_TEXTURE_2D,textures[10]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-40,24.5,12);
	glTexCoord2f(0,1);glVertex3f(-40,24.5,28);
	glTexCoord2f(1,1);glVertex3f(-24,24.5,28);
	glTexCoord2f(1,0);glVertex3f(-24,24.5,12);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();          //tower roof
	  glColor3f(1, 0, 0);
	  glTranslatef(-32,34.5,20);
	  glRotatef(-90,1,0,0);
	  glScalef(2.2,2.2,2.2);
	  glutSolidCone(5, 5, 20,20);
	glPopMatrix();

    glColor3f(0.9,0.9,0.9);
	glPushMatrix();          //tilt roof
	  glTranslatef(0,24,2);
	  glRotatef(25,1,0,0);
	  glScalef(80,1,22);
	  glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();          //opposite tilt roof
	  glTranslatef(0,25,-20);
	  glRotatef(165,1,0,0);
	  glScalef(80,1,25);
	  glutSolidCube(1);
	glPopMatrix();	

}

void drawRails()
{
	glColor3f(0.55, 0.41, 0.08);
	
	for(int i = 0; i<25;i+=8){
	  glPushMatrix();          
	  glTranslatef(0,-4,-4-i);
	  glScalef(1000,1,1);
	  glutSolidCube(1);
	  glPopMatrix();
    }
    
    for(int j = -500;j< 500; j+=3){
		glPushMatrix();
		glTranslatef(0+j, -4, -8);
		glScalef(1,1,7);
		glutSolidCube(1);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0+j, -4, -24);
		glScalef(1,1,7);
		glutSolidCube(1);
		glPopMatrix();
		
	}
	
}

void drawFloor()
{
	glNormal3f(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	for(int i = -40; i < 40; i++)        //near floor
	{
		for(int j = 27;  j > -1; j--)
		{
            glEnable(GL_TEXTURE_2D);   
	        glBindTexture(GL_TEXTURE_2D,textures[11]);
	        glBegin(GL_QUADS);
			glTexCoord2f(0,0);glVertex3f(i, 1, j);
			glTexCoord2f(0,1);glVertex3f(i, 1, j+1);
            glTexCoord2f(1,1);glVertex3f(i+1, 1, j+1);
			glTexCoord2f(1,0);glVertex3f(i+1, 1, j);
			glEnd();
		    glDisable(GL_TEXTURE_2D);
		}
	}
	glColor3f(0.5, 0.5, 0.5);                   //far floor
	glNormal3f(0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	for(int i = -40; i < 40; i++)
	{
		for(int j = -30;  j > -50; j--)
		{

			glVertex3f(i, 1, j);
			glVertex3f(i, 1, j+1);
			glVertex3f(i+1, 1, j+1);
			glVertex3f(i+1, 1, j);
		}
	}
	glEnd();

}
void drawPlatform()
{
	glColor3f(0.5, 0.5, 0.5); //inside bottom
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	glPushMatrix();          //near wall
	  glTranslatef(0,-1.5,0);
	  glScalef(80,5,0.5);
	  glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();          //far wall
	  glTranslatef(0,-1.8,-30);
	  glScalef(80,5,0.5);
	  glutSolidCube(1);
	glPopMatrix();
		
}

void drawDuckBody()
{
	glMaterialfv(GL_FRONT,GL_SPECULAR,white);
	glPushMatrix();     //head
	glTranslatef(-10, 6, 43);
	glScalef(1,1,1);
	glutSolidSphere(1,20,20);
	glPopMatrix();
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	glPushMatrix(); //neck
	glTranslatef(-10,5,43);
	glScalef(0.9,1,0.9);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //body
	glTranslatef(-11,4,43);
	glScalef(3,1.8,2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //left wing
	glTranslatef(-10.25,4,41.5);
	glRotatef(-wing_angle, 0,1,0);
	glTranslatef(10.25,-4,-41.5);	
	glTranslatef(-11,4,41.5);
	glScalef(1.5,0.6,0.6);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); //right wing
	glTranslatef(-10.25,4,44.5);
	glRotatef(wing_angle, 0,1,0);
	glTranslatef(10.25,-4,-44.5);	
	glTranslatef(-11,4,44.5);
	glScalef(1.5,0.6,0.6);
	glutSolidCube(1);
	glPopMatrix();
}
	
void drawDuckParts(){	
	glPushMatrix(); // left leg
	glTranslatef(-11,2.6,44);
	glScalef(0.5,1.5,0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // right leg
	glTranslatef(-11,2.6,42);
	glScalef(0.5,1.5,0.5);
	glutSolidCube(1);
	glPopMatrix();	
	
	
	glPushMatrix();     //upper lip
	glTranslatef(-9.4,6,43);
	glRotatef(lip_angle,0,0,1);
	glTranslatef(9.4,-6,-43);	
	glTranslatef(-9, 6, 43);
	glScalef(0.4,0.1,0.2);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();     //lower lip
	glTranslatef(-9.4,5.8,43);
	glRotatef(-lip_angle,0,0,1);
	glTranslatef(9.4,-5.8,-43);	
	glTranslatef(-9, 5.8, 43);
	glScalef(0.4,0.1,0.2);
	glutSolidCube(1);
	glPopMatrix();
}

void drawDuckEyes(){
     //left eye
	glPushMatrix();
	glTranslatef(-10,6.2,44);
	glutSolidSphere(0.2,20,20);
	glPopMatrix();
	
	 //right eye
	glPushMatrix();
	glTranslatef(-10,6.2,42);
	glutSolidSphere(0.2,20,20);
	glPopMatrix();	
}

void drawDuck(){
	glColor3f(1,1,0);
	drawDuckBody();
	glColor3f(1,0,0);
	drawDuckParts();
	glColor3f(0,0,0);
	drawDuckEyes();

}
void drawRailBase()
{
	glColor3f(0.5, 0.5, 0.5);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	glNormal3f(0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	for(int i = -500; i < 500; i++)
	{
		for(int j = 0;  j > -35; j--)
		{
			glVertex3f(i, -4, j);
			glVertex3f(i, -4, j+1);
			glVertex3f(i+1, -4, j+1);
			glVertex3f(i+1, -4, j);
		}
	}
	glEnd();

}
void drawGreenTrain(){
	glMaterialfv(GL_FRONT,GL_SPECULAR,white);
	for(int i = 0;i < 8;i+=1){
	    glPushMatrix();             //base
	    glColor3f(0.0,0.5,0.0);
	    glTranslatef(-50+i*15-train_dist, 1.5, -23.5);
	    glScalef(14, 2, 9);
	    glutSolidCube(1);
	    glPopMatrix();
	    
	    glPushMatrix();            //carriage body
	    glColor3f(0,0.8,0);
	    glTranslatef(-56+i*15-train_dist, 6.5, -23.5);
	    glRotatef(90,0,1,0);
		gluCylinder(q, 4,4,12, 20, 20);
		glPopMatrix();
		
		glPushMatrix();          //carriage front
		glColor3f(0,0.8,0);
		glTranslatef(-56+i*15-train_dist,6.5,-23.5);
		glRotatef(90,0,1,0);
		gluDisk(q,0,4,20,20);
		glPopMatrix();

		
		glPushMatrix();            //carriage back
		glColor3f(0,0.8,0);
		glTranslatef(-44+i*15-train_dist,6.5,-23.5);
		glRotatef(90,0,1,0);
		gluDisk(q,0,4,20,20);
		glPopMatrix();
		
			
	}
	
	for(int i = 0;i<7;i+=1){       //connector
	    glPushMatrix();
	    glColor3f(0.0,0.5,0.0);
	    glTranslatef(-43+i*15-train_dist, 6, -23.5);
	    glScalef(6, 4, 5);
	    glutSolidCube(1);
		glPopMatrix();	
	}
	glColor3f(0.0,0.5,0.0);

	glPushMatrix();                // train head
	glTranslatef(-48-train_dist, 11.5, -23.5);
	glScalef(5, 5,5);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-48-train_dist, 14.5, -23.5);
	glScalef(7,1,7);
	glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0,0,0);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	for(int i = 0;i<8;i+=1){             // back-right wheel
	      glPushMatrix();
	      glTranslatef(-55+i*15-train_dist,-1.5,-20.5);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();

                                      //front-right wheel   
	      glPushMatrix();
	      glTranslatef(-45+i*15-train_dist,-1.5,-20.5);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
                                    //front-left wheel   
	      glPushMatrix();
	      glTranslatef(-45+i*15-train_dist,-1.5,-27.5);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
                                   // back-left wheel
	      glPushMatrix();
	      glTranslatef(-55+i*15-train_dist,-1.5,-27.5);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
	   }
	
}

void drawRedTrain(){
	   glColor3f(1,0,0);
	   for(int j = 0;j< 10; j+=1){

		glEnable(GL_TEXTURE_2D);   //carriage right
		glBindTexture(GL_TEXTURE_2D,textures[6]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-57+j*15+train_dist,0.5,-3.5);
		glTexCoord2f(0,1);glVertex3f(-57+j*15+train_dist,7.5,-3.5);
		glTexCoord2f(1,1);glVertex3f(-43+j*15+train_dist,7.5,-3.5);
		glTexCoord2f(1,0);glVertex3f(-43+j*15+train_dist,0.5,-3.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); //carriage_left
		glBindTexture(GL_TEXTURE_2D,textures[6]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-43+j*15+train_dist,0.5,-11.5);
		glTexCoord2f(0,1);glVertex3f(-43+j*15+train_dist,7.5,-11.5);
		glTexCoord2f(1,1);glVertex3f(-57+j*15+train_dist,7.5,-11.5);
		glTexCoord2f(1,0);glVertex3f(-57+j*15+train_dist,0.5,-11.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); //carriage_top
		glBindTexture(GL_TEXTURE_2D,textures[7]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-57+j*15+train_dist,7.5,-3.5);
		glTexCoord2f(0,1);glVertex3f(-57+j*15+train_dist,7.5,-11.5);
		glTexCoord2f(1,1);glVertex3f(-43+j*15+train_dist,7.5,-11.5);
		glTexCoord2f(1,0);glVertex3f(-43+j*15+train_dist,7.5,-3.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); //carriage_bottom
		glBindTexture(GL_TEXTURE_2D,textures[7]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-57+j*15+train_dist,0.5,-3.5);
		glTexCoord2f(0,1);glVertex3f(-57+j*15+train_dist,0.5,-11.5);
		glTexCoord2f(1,1);glVertex3f(-43+j*15+train_dist,0.5,-11.5);
		glTexCoord2f(1,0);glVertex3f(-43+j*15+train_dist,0.5,-3.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); //carriage_front
		glBindTexture(GL_TEXTURE_2D,textures[8]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-43+j*15+train_dist,0.5,-3.5);
		glTexCoord2f(0,1);glVertex3f(-43+j*15+train_dist,7.5,-3.5);
		glTexCoord2f(1,1);glVertex3f(-43+j*15+train_dist,7.5,-11.5);
		glTexCoord2f(1,0);glVertex3f(-43+j*15+train_dist,0.5,-11.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); //carriage_back
		glBindTexture(GL_TEXTURE_2D,textures[8]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-57+j*15+train_dist,0.5,-3.5);
		glTexCoord2f(0,1);glVertex3f(-57+j*15+train_dist,7.5,-3.5);
		glTexCoord2f(1,1);glVertex3f(-57+j*15+train_dist,7.5,-11.5);
		glTexCoord2f(1,0);glVertex3f(-57+j*15+train_dist,0.5,-11.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	   }
	   glColor3f(1,1,0);
	   for(int i = 0;i<9;i+=1){       //connector
		
		glPushMatrix();
		glTranslatef(-43.5+i*15+train_dist,3,-7);
		glRotatef(90,0,1,0);
		gluCylinder(q, 2,2,2, 10, 10);
		glPopMatrix();
	   }
	   glColor3f(0,0,0);
	   glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	   for(int i = 0;i<10;i+=1){             // back-right wheel
	      glPushMatrix();
	      glTranslatef(-55+i*15+train_dist,-1.5,-4);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
	   }
	   for(int i = 0;i<10;i+=1){          //front-right wheel   
	      glPushMatrix();
	      glTranslatef(-46+i*15+train_dist,-1.5,-4);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
	   }
	   for(int i = 0;i<10;i+=1){          //front-left wheel   
	      glPushMatrix();
	      glTranslatef(-55+i*15+train_dist,-1.5,-11);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
	   }
	   for(int i = 0;i<10;i+=1){             // back-left wheel
	      glPushMatrix();
	      glTranslatef(-46+i*15+train_dist,-1.5,-11);
		  gluDisk(q, 1,2, 20, 20); 
		  glPopMatrix();
	   }
	
}


void drawUfo(){             //generated by surface revolution
	glMaterialfv(GL_FRONT,GL_SPECULAR,white);
	glColor3f(1,0,0);
	for (int n=0; n<36; n++){		
	    for (int i = 0; i <=31; i++){
			wx[i] = vx[i]*cos(radian) + vz[i]*sin(radian);
			wy[i] = vy[i];
			wz[i] = -vx[i]*sin(radian) + vz[i]*cos(radian);
		}
		glBegin(GL_QUADS);
		for(int i = 0; i < 30; i++)
		{	
			glNormal3f(vx[i]+ufo_move, vy[i], vz[i]-35);
			glVertex3f(vx[i]+ufo_move, vy[i], vz[i]-35);
			glNormal3f(vx[i+1]+ufo_move, vy[i+1], vz[i+1]-35);
			glVertex3f(vx[i+1]+ufo_move, vy[i+1], vz[i+1]-35);
			glNormal3f(wx[i+1]+ufo_move,wy[i+1],wz[i+1]-35);
			glVertex3f(wx[i+1]+ufo_move,wy[i+1],wz[i+1]-35);
			glNormal3f(wx[i]+ufo_move,wy[i],wz[i]-35);
			glVertex3f(wx[i]+ufo_move,wy[i],wz[i]-35);
		}
		glEnd();
		for(int i= 0; i < 31; i++){
			vx[i] = wx[i];
			vy[i] = wy[i];
			vz[i] = wz[i];
		}
	}
}

void drawDuckShadow(){
	float shadowMat[16] = {gy,0,0,0, -gx,0,-gz,-1,0,0,gy,0, 0,0,0,gy};
	glDisable(GL_LIGHTING);
	glPushMatrix();          //draw shadow object
	glColor4f(0.2,0.2,0.2,1.0);
	glMultMatrixf(shadowMat);
    drawDuckBody();
    drawDuckParts();
    drawDuckEyes();
	glPopMatrix();
	
}

//--Draws a character model constructed using GLUT objects ------------------
void drawManInBlack()
{
	glColor3f(1, 1, 1);		//Head
	glPushMatrix();
	glTranslatef(0, 7.7, 5);
	glScalef(1.2,1.2,1.2);
	glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0, 0, 0);		//sunglasses
	glPushMatrix();
	glTranslatef(0, 7.8, 4.35);
	glScalef(1.2,0.5,0.1);
	glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(1,1,1);   //nose
	glPushMatrix();
	glTranslatef(0,7.7,4.3);
	glScalef(0.1,0.3,0.2);
	glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0,0,0); //hat lower part
	glPushMatrix();
	glTranslatef(0,8.2,5);
	glScalef(1.6,0.1,1.6);
	glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0,0,0); //hat upper part
	glPushMatrix();
	glTranslatef(0,8.4,5);
	glScalef(1.4,0.4,1.4);
	glutSolidCube(1);
	glPopMatrix();
	

	glColor3f(0, 0, 0);			//Torso
	glPushMatrix();
	  glTranslatef(0, 5.6, 5);
	  glScalef(3, 3, 1.4);
	  glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(1, 1, 1);			//suit
	glPushMatrix();
	  glTranslatef(0, 5.5, 4.3);
	  glScalef(1, 3, 0.2);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);			//Right leg
	glPushMatrix();
	  glTranslatef(-0.8, 2.6, 5);
	  glScalef(1, 3, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);			//Left leg
	glPushMatrix();
	  glTranslatef(0.8, 2.6, 5);
	  glScalef(1, 3, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);			//Right arm
	glPushMatrix();
	  glTranslatef(-2, 5, 5);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);			//Left arm
	glPushMatrix();
	  glTranslatef(2, 6.5, 5);
	  glRotatef(theta, 1, 0, 0);
	  glTranslatef(-2, -6.5,-5);
	  glTranslatef(2, 5, 5);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0,0,1);        //gun horizontal
	glPushMatrix();
	glTranslatef(2,6.5,5);
	glRotatef(theta,1,0,0);
	glTranslatef(-2,-6.5,-5);
	glTranslatef(2,3,5);
	glScalef(0.5,0.5,0.8);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0,0,1);        //gun vertical
	glPushMatrix();
	glTranslatef(2,6.5,5);
	glRotatef(theta,1,0,0);
	glTranslatef(-2,-6.5,-5);
	glTranslatef(2,2.2,4.5);
	glScalef(0.5,1.5,0.5);
    glutSolidCube(1);
    glPopMatrix();

}

void drawBullet(){
	glColor3f(1,1,0);        //bullet
	glPushMatrix();
	glTranslatef(2,6.5-bullet_drop,0-bullet_dist);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();	
 
}

void duckTimer(int value)
{
	if(wing_angle==30||wing_angle==0){
		wing_flag=wing_flag*(-1);	
	}
	wing_angle = wing_angle+wing_flag;
	if(lip_angle==30||lip_angle==0){
		lip_flag=lip_flag*(-1);
	}
    lip_angle+=lip_flag*5;
    glutPostRedisplay();
    glutTimerFunc(50, duckTimer, 0);	
}

void ufoTimer(int value)
{
   if(ufo_move == -40 || ufo_move==40){
		ufo_flag = ufo_flag*(-1);
	}
	ufo_move = ufo_move+ufo_flag;
	glutPostRedisplay();
    glutTimerFunc(50, ufoTimer, 0);
}

void trainTimer(int value)
{
	if(train_dist<10){
	   train_dist+=0.2;
    }else{
		train_dist+=0.3;
	}
	glutPostRedisplay();
    glutTimerFunc(50, trainTimer, 0);
}

void manTimer(int value)
{
	float dx = ufo_move-2, dy = 0,dz=-35+bullet_dist, collision_distance;

    if(theta == 90){
		bullet_dist = 0;
		bullet_drop=0;
		shoot = 1;
		hit_flag=1;
		flag=flag*(-1);
        
    }else if(theta==15){
		flag=flag*(-1);
		shoot = 0;
	}
    theta = theta + flag*1.5;
    collision_distance = sqrt(dx*dx+dy*dy+dz*dz);
    if(collision_distance<=4.5&&bullet_dist!=39){	//if bullet hits ufo, flag switches to -1   
    	   hit_flag=-1;
	}
	if(hit_flag==1&&bullet_dist<39){
		glEnable(GL_LIGHT2);
		bullet_drop+=0;
	   bullet_dist+=3;
	}else if(hit_flag==-1){      //if bullet hits ufo bullet stop moving forward then drop
		glDisable(GL_LIGHT2);     //spotlight upon ufo will be turned ooff for seconds
		if(bullet_drop<5){
		  bullet_drop+=1;
	    }
		bullet_dist+=0;
	}else if(bullet_dist==39)     //if bullet hit the far wall, it drops
	{
		if(bullet_drop<5){
		  bullet_drop+=1;
	    }
		bullet_dist+=0;
	}
    glutPostRedisplay();
    glutTimerFunc(50, manTimer, 0);
}


//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()  
{
	float lpos[4] = {0, 30, 45, 1};  //light0's position
	float lpos1[4] = {0, 20, -35, 1};  //light1's position
    float spot_pos[4]= {ufo_move, 15,-35,1};   //spot light's position
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(viewmode==1){                          //default view
	   gluLookAt(ex,cam_hgt, ez, lx, cam_hgt, lz,0,1,0);
    }else{                                              //ufo first person-view
	   gluLookAt(ufo_move, fps_height, -35, fps_lx, fps_height,fps_lz,0,1,0); 
	}
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0,GL_POSITION, lpos);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white); 
	glLightfv(GL_LIGHT1,GL_POSITION, lpos1);
	
	glLightfv(GL_LIGHT2, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white);       
	glLightfv(GL_LIGHT2,GL_POSITION, spot_pos); 
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir);  
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT,0.01);  
    glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis
	glEnable(GL_LIGHTING);	       //Enable lighting when drawing the model
	
	drawSkybox();
	
	drawRoad();
	
	drawUfo();
	
	drawCactusShadow();
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,white);
	glMaterialfv(GL_FRONT,GL_SPECULAR,black);
	glColor3f(0,1,0);
    drawCactus();
    
	drawDuckShadow();
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,white);
	glMaterialfv(GL_FRONT,GL_SPECULAR,white);
	drawDuck();
		
	drawRails();
	
	drawRedTrain();
	
	drawGreenTrain();
	
	drawEntrance();
		
	drawFloor();
		
	drawPlatform();
	
	drawRailBase();
	
	if(shoot==1){     //only when gunman's arm is parallel to the floor will bullet be shot
	   drawBullet();
	}
	
	drawManInBlack();

    glutSwapBuffers();
}


//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	train_dist=0;
	bullet_dist=0;
	ufo_move=0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour
    q = gluNewQuadric();
    loadTextureImage();
    gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricNormals(q, GLU_SMOOTH);
	gluQuadricTexture (q, GL_TRUE);
	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 	glEnable(GL_COLOR_MATERIAL);
 	glMaterialfv(GL_FRONT, GL_SPECULAR,white);
 	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);   //Camera Frustum
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)            //sourced from lab3 yard.cpp
{
    if(key== GLUT_KEY_F1){
		viewmode=viewmode*(-1);
	}
	if(viewmode==1){
      if(key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
	  else if(key == GLUT_KEY_RIGHT) angle += 0.1;
	  else if(key == GLUT_KEY_DOWN)
	  {  //Move backward
		ex -= 2*sin(angle);
		ez += 2*cos(angle);
	  }
	  else if(key == GLUT_KEY_UP)
	  { //Move forward
		ex += 2*sin(angle);
		ez -= 2*cos(angle);
	  }
	  lx = ex + 100*sin(angle);
	  lz = ez - 100*cos(angle);
    }else{
      if(key == GLUT_KEY_LEFT) fps_angle -= 0.1;  // ufo first-person view 
	  else if(key == GLUT_KEY_RIGHT) fps_angle += 0.1;
	    fps_lx = ufo_move + 100*sin(fps_angle);
	    fps_lz = -32 - 100*cos(fps_angle);		
	  
	  }
	glutPostRedisplay();
}


//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("cosc363assignment1");
   initialize();
   glutTimerFunc(50, trainTimer, 0);
   glutTimerFunc(30, manTimer, 0);
   glutTimerFunc(100, duckTimer, 0);
   glutTimerFunc(40, ufoTimer, 0);
   glutDisplayFunc(display);
   glutSpecialFunc(special); 
   glutMainLoop();
   return 0;
}
