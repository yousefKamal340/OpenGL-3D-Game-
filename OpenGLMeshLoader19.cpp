#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <math.h>
#include <random>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <sstream>
#include <conio.h>
#include <iostream>
#include <mmsystem.h>
using namespace std;

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

GLUquadricObj* quadratic = gluNewQuadric();

//Functions
void set1();
void set2();

bool level2;

double r = 1;
int rd = 1;

double rw = 1;
double rl = 1;

bool w = true;
bool rwb = false;
bool rlb = false;

bool s = true;
bool l = true;

double pos = 0;
double red = 0;
double green = 0;
double blue = 0;

int WIDTH = 1280;
int HEIGHT = 720;
float movePlayerX;
float movePlayerY;
float movePlayerZ;
boolean atRight = false;
boolean atCenter = true;
boolean atLeft = false;
float rotAng;
float rotAngPlayer;
bool isInSet1 = true;
bool isInSet2= false;
bool isInSet3 = false;
bool finishedSets = false;
int score = 0;
int coinsCollected = 0;
int numOfLives = 3;

bool gameOver = false;
bool firstperson = false;

float scale = 0.0f;

bool coin1Collided = false;
bool coin2Collided = false;
bool coin3Collided = false;
bool coin4Collided = false;
bool coin5Collided = false;
bool coin6Collided = false;
bool coin7Collided = false;
bool coin8Collided = false;
bool coin9Collided = false;
bool coin10Collided = false;
bool coin11Collided = false;
bool coin12Collided = false;
bool coin13Collided = false;
bool coin14Collided = false;
bool coin15Collided = false;

bool boosterTaken = false;
int boostTime = 10;

bool jetPackTaken = false;
bool lastLevel = false;

int eyeY = 18;
int eyeZ = 35;

float RotAng = 0.0f;

bool stop = false;
bool planeCol = false;
float trans = 0.0f;
float transX = 0.0f;
bool coinCol = false;
bool boostCol = false;
bool boostCol2 = false;
float coinVanish = 0.0;
float boostVanish = 0.0;
float boostVanish2 = 0.0;
float moveXplayer = 0.0;
float moveZplayer = 0.0;
float moveXobstacles = 0.0;
int counter = 0.0;
int lives = 3;
float coinPositionsX[7] = { -25,-85,-135,-185,-205,-225,-265 };
float coinPositionsZ[7] = { -15,-85,-135,-165,-185,-225,-225 };
float planePositionsX[7] = {};
float planePositionsZ[7] = {};
float rotate1 = 0.0f;
int translateCoinOne = 0;

int translateCoinTwo = 0;
int translateCoinThree = 0;
int translateCoinFour = 0;
int translateCoinFive = 0;

float scaleBooster = 0.0;

float moveYplayer = 0.0f;

int translateCoinSix = 0;

int playerScore = 0;
float extraInX = -5;

void frameTwo(void);
void frameThree(void);
void planeCollision(void);
void boosterCollision(void);
void frameBoosters(void);
void GameOver(void);
void GameOverDisplay(void);
void myDisplay(void);

GLuint tex1;
GLuint tex2;
char title[] = "Subway Surfers ESKO's Edition";

float moveXObstacles;
float moveZObstacles;

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(0, 18, 35);
Vector At(0, 10, 10);
Vector Up(0, 1, 0);

int cameraZoom = 0;

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 0.0f, float eyeY = 18.0f, float eyeZ = 35.0f, float centerX = 0.0f, float centerY = 3.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;

Model_3DS model_jake;
Model_3DS model_jetpack;
Model_3DS model_coin;
Model_3DS model_train;
Model_3DS model_score_booster;
Model_3DS model_door;
Model_3DS model_dog;
Model_3DS model_zombie;
Model_3DS model_health;
Model_3DS model_booster;
Model_3DS model_plane;

// Textures
GLTexture tex_ground;
GLTexture tex_jake;


void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================

void setupLights() {


	GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat l0Diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l0Ambient[] = { 1.0f, 1.0f, blue, 1.0f };
	GLfloat l0Position[] = { pos, 0.0f, 0.0f, s };
	GLfloat l0Direction[] = { pos, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);

	GLfloat l1Diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l1Ambient[] = { 1.0f, 1.0f, blue, 1.0f };
	GLfloat l1Position[] = { pos, 10.0f, 0.0f, s };
	GLfloat l1Direction[] = { pos, -1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1Ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, l1Position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1Direction);

	GLfloat l2Diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat l2Ambient[] = { 1.0f, 1.0f, blue, 1.0f };
	GLfloat l2Position[] = { pos, 10.0f, 0.0f, s };
	GLfloat l2Direction[] = { pos, 0.0, -1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2Diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2Ambient);
	glLightfv(GL_LIGHT2, GL_POSITION, l2Position);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2Direction);


}

//=============== SCENE 1

void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-10, 0, -5000);
	glTexCoord2f(5, 0);
	glVertex3f(-15, 0, 10);
	glTexCoord2f(5, 5);
	glVertex3f(15, 0, 10);
	glTexCoord2f(0, 5);
	glVertex3f(10, 0,-5000);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void Anim() {
	rotAng += 0.25;

	scale += 0.5;
	if (boosterTaken) {
		rotAngPlayer += 0.5;
	}
	if (rotAngPlayer == 10) {
		rotAngPlayer = 0;
	}
	if (lastLevel) {
		if (blue > 5 ) {
			red = 0;
			green = 0;
			blue = 0;
			pos = 0;
		}
		if (blue < 5) {
			blue += 0.2;
			red += 0.2;
			green += 0,2;
			pos += 0.5;
		}
	}
	glutPostRedisplay();
}

void set1() {

	glPushMatrix();

	// Draw Coin Model

	if (!coin1Collided) {
		glPushMatrix();
		glTranslatef(0, 6, -12 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin2Collided) {
		glPushMatrix();
		glTranslatef(0, 9, -16 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin3Collided) {
		glPushMatrix();
		glTranslatef(0, 12, -20 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin4Collided) {
		glPushMatrix();
		glTranslatef(0, 9, -24 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin5Collided) {
		glPushMatrix();
		glTranslatef(0, 6, -28 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	glPopMatrix();

	//Center Train
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -20 + moveZObstacles);
	glScalef(0.3, 0.2, 0.3);
	model_train.Draw();
	glPopMatrix();

	//Left Train
	glPushMatrix();
	glTranslatef(-8, 0, -20 + moveZObstacles);
	glScalef(0.3, 0.2, 0.3);
	model_train.Draw();
	glPopMatrix();

	//Right Train
	glPushMatrix();
	glTranslatef(8, 0, -20 + moveZObstacles);
	glScalef(0.3, 0.2, 0.3);
	model_train.Draw();
	glPopMatrix();
	glPopMatrix();
}

void set2() {

	if (!coin6Collided) {
		glPushMatrix();
		glTranslatef(8, 1, -48 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin7Collided) {
		glPushMatrix();
		glTranslatef(8, 1, -51 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin8Collided) {
		glPushMatrix();
		glTranslatef(8, 1, -54 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin9Collided) {
		glPushMatrix();
		glTranslatef(8, 1, -57 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin10Collided) {
		glPushMatrix();
		glTranslatef(8, 1, -60 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 0, -50 + moveZObstacles);
	glScalef(0.3, 0.2, 0.3);
	model_train.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 0, -50 + moveZObstacles);
	glRotatef(180.f, 0, 1, 0);
	glScalef(2, 2, 2);
	model_dog.Draw();
	glPopMatrix();
}

void set3() {
	glPushMatrix();

	if (!coin11Collided) {
		glPushMatrix();
		glTranslatef(-8, 1, -68 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin12Collided) {
		glPushMatrix();
		glTranslatef(-8, 1, -71 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin13Collided) {
		glPushMatrix();
		glTranslatef(-8, 1, -74 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin14Collided) {
		glPushMatrix();
		glTranslatef(-8, 1, -77 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	if (!coin15Collided) {
		glPushMatrix();
		glTranslatef(-8, 1, -80 + moveZObstacles);
		glScalef(10, 10, 10);
		glRotatef(rotAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 0, -80 + moveZObstacles);
	glScalef(0.3, 0.2, 0.3);
	model_train.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 0, -80 + moveZObstacles);
	glScalef(0.3, 0.2, 0.3);
	model_train.Draw();
	glPopMatrix();
	glPopMatrix();
}

void level2Door() {
	glPushMatrix();
	if (!lastLevel) {
		glPushMatrix();
		glTranslatef(0, 0, -125 + moveZObstacles);
		glScalef(50, 50, 50);
		model_jetpack.Draw();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 0, -130 + moveZObstacles);
	glScalef(0.35, 0.06, 0.06);
	model_door.Draw();
	glPopMatrix();
	glPopMatrix();
}

void detectObstaclesCollision()
{
	//Set 1
	if (((movePlayerX <= 2 && movePlayerX >= -2 && (-20 + moveZObstacles) >= 0) || 
		(movePlayerX <= -6 && movePlayerX >= -10 && (-20 + moveZObstacles) >= 0) ||
		(movePlayerX <= 10 && movePlayerX >= 6 && (-20 + moveZObstacles) >= 0)) && movePlayerY <= 5.5 && isInSet1) {
		std::cout << " Crashed ";
		moveZObstacles = 39;
		movePlayerY = 0;
		isInSet1 = false;
		isInSet2 = true;
		score -= 800;
	}
	//Set 2
	if (((movePlayerX <= 2 && movePlayerX >= -2 && (-50 + moveZObstacles) >= 0) ||
		(movePlayerX <= -6 && movePlayerX >= -10 && (-50 + moveZObstacles) >= 0)) && movePlayerY <= 5.5 && isInSet2) {
		std::cout << " Crashed ";
		moveZObstacles = 69;
		movePlayerY = 0;
		isInSet2 = false;
		isInSet3 = true;
		score -= 800;
	}
	//Set 3
	if (((movePlayerX <= 2 && movePlayerX >= -2 && (-80 + moveZObstacles) >= 0) ||
		(movePlayerX <= 10 && movePlayerX >= 6 && (-80 + moveZObstacles) >= 0)) && movePlayerY <= 5.5 && isInSet3) {
		std::cout << " Crashed ";
		moveZObstacles = 99;
		movePlayerY = 0;
		isInSet3 = false;
		finishedSets = true;
		score -= 800;
	}
}

void detectCoinCollision()
{
	//Set 1
	for (int i = 0; i < 3; i++) {
		if (((movePlayerX <= 2 && movePlayerX >= -2 && ((-21 - (i * 4)) + moveZObstacles) == 0)) 
			&& (movePlayerY <= (6 + (i * 3)) 
			&& movePlayerY + 4 >= (6 + (i * 3)))
			&& isInSet1) {
			coinsCollected++;
			score += 1000;
			PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
			if (i == 0) {
				coin1Collided = true;
			}
			if (i == 1) {
				coin2Collided = true;
			}
			if (i == 2) {
				coin3Collided = true;
			}
			std::cout << " \n ";
			std::cout << " COINSSS ";
		};
	};
	if (((movePlayerX <= 2 && movePlayerX >= -2 && ((-21 - (3 * 4)) + moveZObstacles) == 0)) 
		&& (movePlayerY <= 9
		&& movePlayerY + 4 >= 9)
		&& isInSet1) {
		coinsCollected++;
		score += 1000;
		PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
		coin4Collided = true;
		std::cout << " \n ";
		std::cout << " COINSSS ";
	};
	if (((movePlayerX <= 2 && movePlayerX >= -2 && ((-21 - (4 * 4)) + moveZObstacles) == 0)) 
		&& (movePlayerY <= 6
		&& movePlayerY + 4 >= 6) 
		&& isInSet1) {
		coinsCollected++;
		score += 1000;
		PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
		coin5Collided = true;
		std::cout << " \n ";
		std::cout << " COINSSS ";
	};
	//Set 2
	for (int i = 0; i < 5; i++) {
		if (((movePlayerX <= 10 && movePlayerX >= 6 && ((-57 - (i * 3)) + moveZObstacles) == 0)) && movePlayerY <= 2 && isInSet2) {
		coinsCollected++;
		score += 1000;
		if (i == 0) {
			coin6Collided = true;
		}
		if (i == 1) {
			coin7Collided = true;
		}
		if (i == 2) {
			coin8Collided = true;
		}
		if (i == 3) {
			coin9Collided = true;
		}
		if (i == 4) {
			coin10Collided = true;
		}
		PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
		std::cout << " \n ";
		std::cout << " COINSSS ";
		};
	};
	//Set 3
	for (int i = 0; i < 5; i++) {
		if (((movePlayerX <= -6 && movePlayerX >= -10 && ((-77 - (i * 3)) + moveZObstacles) == 0)) && movePlayerY <= 2 && isInSet3) {
			coinsCollected++;
			score += 1000;
			PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
			if (i == 0) {
				coin11Collided = true;
			}
			if (i == 1) {
				coin12Collided = true;
			}
			if (i == 2) {
				coin13Collided = true;
			}
			if (i == 3) {
				coin14Collided = true;
			}
			if (i == 4) {
				coin15Collided = true;
			}
			std::cout << " \n ";
			std::cout << " COINSSS ";
		};
	};
}

void detectBoosterCollision() {
	if ((movePlayerX <= 8 && movePlayerX >= 4) && (-51 + moveZObstacles) == 0 && movePlayerY <= 2) {
		score = score + 3000;
		boosterTaken = true;
	}
}

void detectJetPackCollision() {
	if (lastLevel) {
		if ((movePlayerX <= 2 && movePlayerX >= -2) && (-135 + moveZObstacles) == 0 && movePlayerY <= 2) {
			gameOver = true;
		}
	}
	else {
		if ((movePlayerX <= 2 && movePlayerX >= -2) && (-135 + moveZObstacles) == 0 && movePlayerY <= 2) {
			level2 = true;
			jetPackTaken = true;
		}
	}
}

//================

//================ SCENE 2

void planeCollision(void) {
	if (!stop) {
		if (moveXplayer >= (4.9 + 0) && moveXplayer <= (5.1 + 0) && moveXobstacles >= (7.2 + 0) && moveXobstacles <= (13.4 + 0)) {
			score -= 100;
			trans = 3;
			transX = 5.0f;
			planeCol = true;
			return;
		}
		if (moveXplayer >= (-0.2 + 0) && moveXplayer <= (0.2 + 0) && moveXobstacles >= (17.2 + 0) && moveXobstacles <= (23.4 + 0)) {
			score -= 100;
			trans = 3;
			transX = 5.0f;
			planeCol = true;
			return;
		}
		if (moveXplayer >= (-5 + 0) && moveXplayer <= (-4.8 + 0) && moveXobstacles >= (47.2 + 0) && moveXobstacles <= (53.2 + 0)) {
			score -= 100;
			trans = 3;
			transX = 5.0f;
			planeCol = true;
			return;
		}
		if (moveXplayer >= (-0.1 + 0) && moveXplayer <= (0.1 + 0) && moveXobstacles >= (73.6 + 0) && moveXobstacles <= (79.6 + 0)) {
			score -= 100;
			trans = 3;
			transX = 5.0f;
			planeCol = true;
			return;
		}

		if (moveXplayer >= (-0.2 + 0) && moveXplayer <= (0.2 + 0) && moveXobstacles >= (57.2 + 0) && moveXobstacles <= (64.8 + 0)) {
			score -= 100;
			trans = 3;
			transX = 5.0f;
			planeCol = true;
			return;
		}
	}
	if (moveXobstacles >= 43) {
		stop = false;
	}
	glutPostRedisplay();
}

void frameTwo(void) {

	glPushMatrix();
	glTranslatef(0, 0, -40);
	glPushMatrix();
	glTranslatef(-10, 0, -10);
	// coin1 
	glPushMatrix();
	glTranslatef(5, translateCoinTwo, -5 + moveXobstacles);
	glScalef(10, 10, 10);
	//glRotatef(180.f + RotAng, 0, 1, 0);
	//glScalef(10,10,10);
	model_coin.Draw();
	glPopMatrix();
	glPopMatrix();

	boosterCollision();

	if (!boosterTaken) {
		glPushMatrix();
		glTranslatef(0, boostVanish2, 0);
		glPushMatrix();
		glTranslatef(7, 0, 0 + moveXobstacles);
		glScalef(5 + scaleBooster, 5 + scaleBooster, 5 + scaleBooster);
		model_score_booster.Draw();
		glPopMatrix();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(-5, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -10 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();
	glPopMatrix();

	glutPostRedisplay();
}

void frameThree(void) {


	glPushMatrix();
	glTranslatef(0, 0, -70);
	glPushMatrix();
	glTranslatef(-10, 0, -70 + moveXobstacles);
	glPushMatrix();
	glTranslatef(-10, 0, -10);
	// coin1 
	glPushMatrix();
	glTranslatef(5, 0, -5 + moveXobstacles);
	glScalef(10, 10, 10);
	glRotatef(220.f, 0, 1, 0);
	//model_coin.Draw();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glutPostRedisplay();
}

void frameBoosters(void) {

	glPushMatrix();

	glTranslatef(0, 0, -120);

	glPushMatrix();
	glTranslatef(0, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0 + extraInX, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0 + extraInX, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPopMatrix();

}

void GameOverDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);


	glPushMatrix();

	glPushMatrix();
	glTranslated(0.0, 1.3, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 60, 100, 100);
	gluDeleteQuadric(qobj);

	glPopMatrix();

	if (score > 0) {
		glPushMatrix();
		glTranslatef(moveXplayer, 0, -moveZplayer);
		glRotatef(rotate1, 0, 1, 0);
		glPushMatrix();
		//glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0, 4, 10);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5, 0.5, 0.5);
		model_jake.Draw();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-8, 7, 0);
		glColor3f(1.0f, 1.0f, 1.0f);
		char* playerS[20];
		sprintf((char*)playerS, "Congrats, You Won");
		print(0, 0, (char*)playerS);
		glPopMatrix();
	}
	if (score <= 0) {
		glPushMatrix();
		glTranslatef(moveXplayer, 0, -moveZplayer);
		glRotatef(rotate1, 0, 1, 0);
		glPushMatrix();
		//glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0, 4, 10);
		glRotatef(180, 0, 1, 0);
		glScalef(10, 10, 10);
		model_zombie.Draw();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-8, 5, 0);
		glColor3f(1.0f, 1.0f, 1.0f);
		char* playerS[20];
		sprintf((char*)playerS, "Game Over, You Are Dead");
		print(0, 0, (char*)playerS);
		glPopMatrix();
	}


	glPopMatrix();

	glutSwapBuffers();

	glutPostRedisplay();
}

void GameOver(void)
{
	glutPostRedisplay();
}

void boosterCollision(void) {
	if (moveXplayer >= -6.2 && moveXplayer <= -4.3 && moveXobstacles >= 10.39 && moveXobstacles <= 10.62) {
		boostVanish += 1000.0f;
		score = score + 3000;
		boosterTaken = true;
		loadBMP(&tex2, "Textures/blu-sky-3.bmp", true);
		stop = true;
	}
	if (moveXplayer >= 6.2 && moveXplayer <= 7 && moveXobstacles >= 49.3 && moveXobstacles <= 50.6) {
		boostVanish2 = 1000.0f;
		boosterTaken = true;
		score = score + 3000;
		stop = true;
	}
	if (moveXplayer >= -5.1 && moveXplayer <= -4.9 && moveXobstacles >= 25.4 && moveXobstacles <= 26.44) {
		rotate1 = 90;
		score += 1000;
		translateCoinOne += 1000;
		PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
	}
	if (moveXplayer >= -5.1 && moveXplayer <= -4.9 && moveXobstacles >= 65.0 && moveXobstacles <= 66.0) {
		rotate1 = 90;
		score += 1000;
		translateCoinTwo += 1000;
		PlaySound(TEXT("coineffect.wav"), NULL, SND_ASYNC);
	}
	glutPostRedisplay();
}

//=================

//=======================================================================
// Keyboard Function
//=======================================================================

void myKeyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 'z':
		camera.eye.x = 0;
		camera.eye.y = 18;
		camera.eye.z = 38;
		camera.center.x = 0;
		camera.center.y = 0;
		camera.center.z = 0;
		firstperson = false;
		glutPostRedisplay();
		break;
	case 'x':
		camera.eye.x = 0.0f;
		camera.eye.y = 10.0f;
		camera.eye.z = 4.0f;
		camera.center.x = 0.0f;
		camera.center.y = 3.0f;
		camera.center.z = -25.0f;
		firstperson = true;
		glutPostRedisplay();
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}	

	glutPostRedisplay();
}

void TimerX(int value) {
	scale += 0.2;
	glutTimerFunc(500, TimerX, 0);
	glutPostRedisplay();
}

void Special(int key, int x, int y) {

	if (!level2) {
		switch (key) {
		case GLUT_KEY_UP:
			if (movePlayerY <= 12) {
				movePlayerY += 0.2;
				if (firstperson) {
					camera.center.y = movePlayerY;
				}
			}
			break;
		case GLUT_KEY_DOWN:
			if (movePlayerY >= 0) {
				movePlayerY -= 0.2;
				if (firstperson) {
					camera.center.y = movePlayerY;
				}
			}
			break;
		case GLUT_KEY_LEFT:
			if (movePlayerX >= -8) {
				movePlayerX += -0.2;
				if (firstperson){
					camera.eye.x = movePlayerX;
				}
			}
			break;
		case GLUT_KEY_RIGHT:
			if (movePlayerX <= 8) {
				movePlayerX += 0.2;
				if (firstperson) {
					camera.eye.x = movePlayerX;
				}
			}
			break;
		}
	}
	if (level2) {
		float r = 0.1;
		float x = 1.0;

		switch (key) {
		case GLUT_KEY_UP:
			if (moveYplayer <= 12) {
				moveYplayer += 0.2;
				if (firstperson)
				camera.eye.y = moveYplayer;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (moveXplayer <= 6.9) {
				moveXplayer += r;
				if (firstperson)
				camera.eye.x = moveXplayer;
			}
				
			break;
		case GLUT_KEY_LEFT:
			if (moveXplayer >= -6.9) {
				if (firstperson)
				camera.eye.x = moveXplayer;
				moveXplayer -= r;
			}
				
			break;
		case GLUT_KEY_DOWN:
			moveYplayer -= 3.0f;
			break;
		}
	}
	glutPostRedisplay();
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

//=======================================================================
// Motion Function
//=======================================================================

void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================

void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================

void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================

void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");

	model_jake.Load("Models/jake/Jake.3ds");
	model_train.Load("Models/Subway/Subway.3ds");
	model_jetpack.Load("Models/Jetpack/Jetpack.3ds");
	model_coin.Load("Models/Coin/Coin.3ds");
	model_score_booster.Load("Models/ScoreBooster/ScoreBooster.3ds");
	model_door.Load("Models/door/door.3ds");
	model_dog.Load("Models/dog/Dog.3ds");
	model_plane.Load("Models/Plane/airplane.3ds");
	model_zombie.Load("Models/ZombieJake/ZombieJake.3ds");

	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");

	loadBMP(&tex1, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex2, "Textures/mars.bmp", true);
}

void Time(int value) {
	if (!level2) {
		moveZObstacles += 0.5;
	}
	if (level2) {
		moveZObstacles += 0.5;
		if (scaleBooster <= 5.0) {
			scaleBooster += 0.5;
		}
		else {
			scaleBooster -= 0.5;
		}
		moveXobstacles += 0.2;
		playerScore += 200;
		counter += 1;
		RotAng += 10;
		/*std::cout << counter;
		std::cout << "\n";
		std::cout << "\n";
		std::cout << moveXplayer;
		std::cout << "\n";
		std::cout << "\n";*/
	}
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	glutTimerFunc(100, Time, 0);
}

void scoreTimer(int value) {
	score += 200;

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	glutTimerFunc(1000, scoreTimer, 0);
}

void boostTimer(int value) {
	if(boosterTaken)
		boostTime -= 1;
	if (boosterTaken && boostTime == 0) {
		boostTime = 10;
		boosterTaken = false;
	}

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	glutTimerFunc(1000, boostTimer, 0);
}

void isInSet(int value) {
	if (!level2) {
		//Set1
		if (moveZObstacles >= 39) {
			isInSet1 = false;
			isInSet2 = true;
		}
		//Set2
		if (moveZObstacles >= 69) {
			isInSet2 = false;
			isInSet3 = true;
		}
		//Set3
		if (moveZObstacles >= 99) {
			isInSet3 = false;
			finishedSets = true;
		}

		if (isInSet1) {
			std::cout << " \n ";
			std::cout << " Set1 ";
		}
		if (isInSet2) {
			std::cout << " \n ";
			std::cout << " Set2 ";
		}
		if (isInSet3) {
			std::cout << " \n ";
			std::cout << " Set3 ";
		}
	}
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	glutTimerFunc(0, isInSet, 0);
}

//=======================================================================
// Display Function
//=======================================================================

void Space(void)
{
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::cout << "\n";
	std::cout << "Obs ";
	std::cout << moveXobstacles;
	std::cout << "\n";
	std::cout << "PLa ";
	std::cout << moveXplayer;

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glScalef(10, 10, 10);
	//glRotatef(270.f, 0, 1, 0);
	//model_health.Draw();
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -10);
	// coin1 
	glPushMatrix();
	glTranslatef(5, translateCoinOne, -5 + moveXobstacles);
	glRotatef(RotAng, 0, 1, 0);
	glScalef(10, 10 , 10);
	model_coin.Draw();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if (planeCol) {
		glTranslatef(0, trans, 0);
		planeCol = false;
	}
	glPushMatrix();
	glTranslatef(moveXplayer, moveYplayer, -moveZplayer);
	glPushMatrix();
	glTranslatef(0, 0, 10);
	glScalef(0.3, 0.3, 0.3);
	model_jake.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 1.5, 10.5);
	glScalef(10, 10, 10);
	glRotatef(180.f, 0, 1, 0);
	model_jetpack.Draw();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	if (score > 0 && moveZObstacles >= 337) {
		moveXObstacles = 0;
		moveZObstacles = 0;
		movePlayerY = 0;
		coin1Collided = false;
		coin2Collided = false;
		coin3Collided = false;
		coin4Collided = false;
		coin5Collided = false;
		coin6Collided = false;
		coin7Collided = false;
		coin8Collided = false;
		coin9Collided = false;
		coin10Collided = false;
		coin11Collided = false;
		coin12Collided = false;
		coin13Collided = false;
		coin14Collided = false;
		coin15Collided = false;
		isInSet1 = true;
		isInSet2 = false;
		isInSet3 = false;
		finishedSets = false;
		level2 = false;
		lastLevel = true;
		glutDisplayFunc(myDisplay);
		glutPostRedisplay();
	}

	if (score < 0 && moveZObstacles >= 337) {
		glutDisplayFunc(GameOverDisplay);
		glutPostRedisplay();
	}

	if (!boosterTaken) {
		glPushMatrix();
		glTranslatef(-5, boostVanish, 0 + moveXobstacles);
		glRotatef(scale, 0, 1, 0);
		glScalef(5 + scaleBooster, 5 + scaleBooster, 5 + scaleBooster);
		model_score_booster.Draw();
		glPopMatrix();
	}

	if (boosterTaken) {
		glPushMatrix();
		glTranslated(0.0, 12, -3);
		glColor3f(1.0f, 1.0f, 1.0f);
		char* boost[20];
		sprintf((char*)boost, "Time Left For Booster: %d", boostTime);
		print(0, 0, (char*)boost);
		glPopMatrix();
	}
	

	glPushMatrix();
	glTranslatef(5, 0, 0 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -10 + moveXobstacles);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180.f, 0, 1, 0);
	model_plane.Draw();
	glPopMatrix();

	frameTwo();
	glPushMatrix();
	glTranslatef(20, 0, 0);
	frameThree();
	glPopMatrix();

	planeCollision();
	if (!boosterTaken) {
		boosterCollision();
	}
	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 60, 100, 100);
	gluDeleteQuadric(qobj);

	glPopMatrix();

	glPushMatrix();
	glTranslated(5.0, 5, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	char* playerS[20];
	sprintf((char*)playerS, "Player Score: %d", score);
	print(0, 0, (char*)playerS);
	glPopMatrix();

	glutSwapBuffers();

	glutPostRedisplay();
}

void myDisplay(void)
{
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	glPushMatrix();
	glTranslated(0, 0, 0 + moveZObstacles);
	RenderGround();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movePlayerX, movePlayerY, 0);
	glRotatef(rotAngPlayer, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	model_jake.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -10);
	set1();
	set2();
	set3();
	level2Door();
	glPopMatrix();

	if (!boosterTaken) {
		detectObstaclesCollision();

		glPushMatrix();
		glTranslatef(6, 0, -51 + moveZObstacles);
		glScalef(10, 10, 10);
		model_score_booster.Draw();
		glPopMatrix();
	}
	detectCoinCollision();
	detectBoosterCollision();
	detectJetPackCollision();

	if (boosterTaken) {
		glPushMatrix();
		glTranslated(0.0, 12, -3);
		glColor3f(1.0f, 1.0f, 1.0f);
		char* boost[20];
		sprintf((char*)boost, "Time Left For Booster: %d", boostTime);
		print(0, 0, (char*)boost);
		glPopMatrix();
	}


	if (level2) {
		movePlayerY += 0.25;
	}

	if (lastLevel) {
		if (blue > 5) {
			red = 0;
			green = 0;
			blue = 0;
			pos = 0;
		}
		if (blue < 5) {
			blue += 0.2;
			//red += 0.2;
			//green += 0, 2;
			pos += 0.5;
		}
	}

	if (movePlayerY >= 50 && jetPackTaken) {
		glutDisplayFunc(Space);
		glutPostRedisplay();
	}

	if (lastLevel && gameOver) {
		glutDisplayFunc(GameOverDisplay);
		glutPostRedisplay();
	}

	//sky box
	glPushMatrix();
	if (lastLevel) {
		if (rlb)
		glRotated(rl, 1, 1, 1);
		setupLights();
	}
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 60, 100, 100);
	gluDeleteQuadric(qobj);

	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 10, -3);
	glColor3f(1.0f, 1.0f, 1.0f);
	char* scores[20];
	sprintf((char*)scores, "Score: %d", score);
	print(0, 0, (char*)scores);
	glPopMatrix();

	glutSwapBuffers();
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutSpecialFunc(Special);

	glutIdleFunc(Anim);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	glutTimerFunc(0, Time, 0);

	glutTimerFunc(0, isInSet, 0);

	glutTimerFunc(0, scoreTimer, 0);


	glutTimerFunc(500, TimerX, 0);

	glutTimerFunc(0, boostTimer, 0);

	PlaySound(TEXT("themesong.wav"), NULL, SND_ASYNC);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}