/*
* Hw1Header.h
*
*  Created on: Aug 15, 2017
*      Author: Miguel Cayetano
*      CIN: 303435436
*/
#pragma once
#ifndef LAB_SOLAR_H
#define LAB_SOLAR_H

#define PI 3.1415

/*
THIS 'animates' ball being created. ex => sun
	glPushMatrix();
	glRotated(rotation_sun, 0, 0, 0);
	glutSolidSphere(0.5, 10, 16);	// locate the sun at the origin
	glPopMatrix();
*/

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0;

float t;
float tt = 0;
bool pressedR = false;
bool isOn = true;
bool isSolid = true;
bool isAxes = true;
GLdouble ballRadius = 0;

//Initial values for shoulder translation/rotation		|| no scaling
GLdouble shoulder_rotation = 0;

GLdouble upperRot = 0;

//Lower arm rotate and translate
GLdouble lowerRot = 0;
GLdouble lowerArmTran = 0;

GLdouble wristRot = 0;
GLdouble wristTrans = 0;
GLdouble finger1_rot = 0;
GLdouble finger1Translate = 0;
GLdouble finger2_rot = 0;
GLdouble finger3_rot = 0;
GLdouble finger4_rot = 0;
GLdouble finger5_rot = 0;

GLdouble xTran = 0;
GLdouble zTran = 0;



// Initial values
GLdouble scale = 1.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble rotation_angle = 0.0;
GLdouble rotation_sun = 0.0;
GLdouble rotation_earth = 0.0;
GLdouble rotation_moon = 0.0;
GLdouble rotation_mars = 0.0;
GLdouble rotation_45 = 0;


// global values for camera
GLdouble eyex = 25.0, eyey = 25.0, eyez = 25.0;
GLdouble lookx = 0.0, looky = 0.0, lookz = 0.0;

int view = 0;

// global values for shading
GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess[] = { 50.0f };

GLfloat position[] = { 2.0f, 6.0f, 3.0f, 0.0f };
GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };



#endif