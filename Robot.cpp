//Computer Graphics Homework2 - Robot Arm & Bouncing Ball
//============================================================================
// Name        : Robot.cpp //Homework2
// Author      : Miguel Cayetano
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// CIN		   : 303435436
//============================================================================

#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>

#include "robotHeader.h"


/*Shading inside init fnc*/
void myInit(int shadingChoice, int colorChoice)
{
	wristRot = lowerRot;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	if (shadingChoice == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	}
	else if (shadingChoice == 1) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	}

	if (colorChoice == 1) {
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}


	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-3.5*worldWidth / worldHeight, 3.5*worldWidth / worldHeight, -3.5, 3.5, 0.1, 100);
}

void myIdle()
{
	//this function will be invoked when idle

	t += 0.001;
	if (t > 1)
	{
		t = 0.001;
	}

	if (ballRadius<=0) {
		ballRadius += 0.1;
	}
	else if (ballRadius>=0.5) {
		ballRadius += 0;
	}

	if (pressedR) {
		rotation_sun += 0;
		rotation_earth += 0;
		rotation_mars += 0;
		rotation_moon += 0;

		//Camera rotates elltical rotation
		eyex = 30 * cos(2 * PI*tt);
		eyez = 20 * sin(2 * PI*tt);
		tt++;
	}

	else {
		rotation_sun += 0.05;
		rotation_earth += 0.02;
		rotation_mars += 0.01;
		rotation_moon += 0.15;
	}

	glutPostRedisplay();
}

//new seperate function that draw the orbit of the function
void drawOrbit()
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);	//using line loop
	for (float tt = 0; tt <= 1; tt = tt + 0.02)
	{
		//Must be on x/z axis bc 
		glVertex3f((0) + 2 * cos(2 * PI*tt), 0, (0) + 2 * sin(2 * PI*tt));
	}
	glEnd();
}

void drawBall()
{

	glPushMatrix();
		glTranslatef(0,4,0);
		glRotated(rotation_sun, 0, 0, 0);
		glutSolidSphere(ballRadius, 20, 16);	
	glPopMatrix();


}

void drawAxes()
{
	//glColor3f(1,0,0);
	glBegin(GL_LINES);
	//x
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	//y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	//z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);

	glEnd();
}

//draw circle stand
void drawStand()
{
	if (isOn)
	{
		glColor3f(0.0f, 1.0f, 0.0f);   
	}
	else if (isOn == false)
	{
		glColor3f(1.0f, 0.0f, 0.0f);  
	}


	glPushMatrix();
		glTranslated(0,-0.2,0);
		glScalef(1.0, 0.1, 1.0);

		if (isSolid) {
			glutSolidSphere(0.5, 20,16);
		}
		else {
			glutWireSphere(0.5, 20, 16);
		}
		
	glPopMatrix();

}



//Joint that connects to upper arm
void drawShoulderJoint()
{

	glColor3f(0.5f, 0.5f, 0.5f);   

	glPushMatrix();
	glTranslated(0, 0, 0);

	if (isSolid) {
		glutSolidSphere(0.35, 20, 16);
	}
	else {
		glutWireSphere(0.35, 20, 16);
	}
	glPopMatrix();
}

//Actual upper arm thats connected btwn shoulder and upper arm joint
void drawUpperArm()
{
	glColor3f(0.0f, 0.0f, 2.5f);
	//1st part of upper arm
	glPushMatrix();
			
		glTranslated(-0.2, 1, 0.0);
//		glRotated(rotation_angle, tx, 0, 0);
		glTranslated(0.0,0.0,0);
		glScalef(0.1, 1.45, 0.1);
		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
			
	glPopMatrix();

	//2nd part of upper arm	//FIXED
	glPushMatrix();
	glColor3f(0,0,1.5);
		glTranslated(0.2, 1, 0.0);
		glScalef(0.1, 1.45, 0.1);
		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();
}
//**********************************88
//Draws upper arm joint (sphere)
void drawArmJoint()
{
	glColor3f(0.5f, 0.5f, 0.5f);    // sun is orange

	glPushMatrix();
		glTranslated(0, 1.5, 0);
		if (isSolid) {
			glutSolidSphere(0.35, 20, 16);
		}
		else {
			glutWireSphere(0.35, 20, 16);
		}
	glPopMatrix();
}


//Draw lower arm that connects between upper arm joint to wrist(another joint)
void drawLowerArm()
{
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();
		glTranslated(0.2, 1.5, 0); //where sphere is
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//maybe switch tx for -tx, for 'down' movement
		glTranslated(0, 0.5, 0);
		glScalef(0.1, 1.0, 0.1);
		glTranslated(0.0, 0.0, 0.0);
		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();	
				

	//2nd part of upper arm	//FIXED
	glPushMatrix(); 	
		glTranslated(-0.2, 1.5, -0.0); //negative, adjust x coordinate
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//Works, this order is needed
		glTranslated(0.0, 0.5, -0.0);			//^^ the 'first' (0,0,0) trans not needed
		glScalef(0.1, 1.0, 0.1);
		glTranslated(0.0, 0.0, 0.0);
		
		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();


}

//*********************************
//Draw wrist joint
void drawWristdJoint()
{
	glColor3f(0.5f, 0.5f, 0.5f);    // sun is orange

	//(FIXED)Wrist, Works, put inside own function, andd add its own translateVariable, wristTX = ++
	glPushMatrix();
	
		glTranslated(-0, 1.5, -0.0); //negative, adjust x coordinate
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//Works, this order is needed
		glTranslated(0.0, 1, -0.0);			//^^ the 'first' (0,0,0) trans not needed
	
		glTranslated(0, 0.1, 0);//(1, needed for wrist rotation)
		glRotatef(wristRot, 1, 0, 0);//(2 needed for wrist rotation)
											
		glTranslated(0.0, 0.0, 0.0);

		if (isSolid) {
			glutSolidSphere(0.35, 20, 16);
		}
		else {
			glutWireSphere(0.35, 20, 16);
		}
	glPopMatrix();
}


//draw hand 
void drawHand() {

	//1st finger bone, always remains straight
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();

		glTranslated(-0.20, 1.5, 0);	
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 1.5, 0);	//Translate to wrist joint location

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.5, 0);	//(3)experimental Translate to wrist joint location


		glScalef(0.1, 0.5, 0.1);
		glTranslated(0.0, 0.0, 0.0);

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();

	//2nd part of 1st finger, this one 'curls', ie rotates
	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();
	
	glTranslated(-0.0, 1.5, 0);
	glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
	glTranslated(0, 0.1, 0);


		glTranslated(-0.20, 1.5, -0.0);	//translate it to same position as 1st bone
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//This rotates along wrist joint
		glTranslated(0.0, 0, -0.0); //translates appropriately. Can be 1.75 or 1.7 

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.7, 0);	//(3)experimental Translate to wrist joint location

		glRotated(finger1_rot, -finger1Translate, 0, 0.0);//Translates around its own x-axis
		glTranslated(0.0, 0.1, -0.0);//Needed as small num so it wont rotate by alot around own axis
		
		glScalef(0.1, 0.25, 0.1);//Scale same as 1st bone
		glTranslated(0.0, 0.0, 0.0);//Not needed since already at origin

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();


	//2nd finger x  = -0.04
	//1st finger bone, always remains straight
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();

		glTranslated(-0.04, 1.5, 0);
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 1.5, 0);	//Translate to wrist joint location

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.5, 0);	//(3)experimental Translate to wrist joint location


		glScalef(0.1, 0.5, 0.1);
		glTranslated(0.0, 0.0, 0.0);

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();

	//2nd part of 2nd finger, this one 'curls', ie rotates
	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();

		glTranslated(-0.0, 1.5, 0);
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 0.1, 0);


		glTranslated(-0.04, 1.5, -0.0);	//translate it to same position as 1st bone
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//This rotates along wrist joint
		glTranslated(0.0, 0, -0.0); //translates appropriately. Can be 1.75 or 1.7 

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.7, 0);	//(3)experimental Translate to wrist joint location

		glRotated(finger1_rot, -finger1Translate, 0, 0.0);//Translates around its own x-axis
		glTranslated(0.0, 0.1, -0.0);//Needed as small num so it wont rotate by alot around own axis

		glScalef(0.1, 0.25, 0.1);//Scale same as 1st bone
		glTranslated(0.0, 0.0, 0.0);//Not needed since already at origin

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();




	//3rd finger x =0.1
	//3rd finger bone, always remains straight
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();

		glTranslated(0.1, 1.5, 0);
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 1.5, 0);	//Translate to wrist joint location

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.5, 0);	//(3)experimental Translate to wrist joint location


		glScalef(0.1, 0.5, 0.1);
		glTranslated(0.0, 0.0, 0.0);

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();

	//2nd part of 3rd finger, this one 'curls', ie rotates
	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();

	glTranslated(-0.0, 1.5, 0);
	glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
	glTranslated(0, 0.0, 0);

		glTranslated(0.1, 1.5, -0.0);	//translate it to same position as 1st bone
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//This rotates along wrist joint
		glTranslated(0.0, 0, -0.0); //translates appropriately. Can be 1.75 or 1.7 

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.7, 0);	//(3)experimental Translate to wrist joint location

		glRotated(finger1_rot, -finger1Translate, 0, 0.0);//Translates around its own x-axis
		glTranslated(0.0, 0.1, -0.0);//Needed as small num so it wont rotate by alot around own axis

		glScalef(0.1, 0.25, 0.1);//Scale same as 1st bone
		glTranslated(0.0, 0.0, 0.0);//Not needed since already at origin

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();




	//4th finger x =0.25
	//4th finger bone, always remains straight
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();
		glTranslated(0.25, 1.5, 0);
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 1.5, 0);	//Translate to wrist joint location

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.5, 0);	//(3)experimental Translate to wrist joint location


		glScalef(0.1, 0.5, 0.1);
		glTranslated(0.0, 0.0, 0.0);

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();

	//2nd part of 4th finger, this one 'curls', ie rotates


	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();

	glTranslated(-0.0, 1.5, 0);
	glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
	glTranslated(0, 0.0, 0);

		glTranslated(0.25, 1.5, -0.0);	//translate it to same position as 1st bone
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//This rotates along wrist joint
		glTranslated(0.0, 0, -0.0); //translates appropriately. Can be 1.75 or 1.7 

		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.7, 0);	//(3)experimental Translate to wrist joint location

		glRotated(finger1_rot, -finger1Translate, 0, 0.0);//Translates around its own x-axis
		glTranslated(0.0, 0.1, -0.0);//Needed as small num so it wont rotate by alot around own axis

		glScalef(0.1, 0.25, 0.1);//Scale same as 1st bone
		glTranslated(0.0, 0.0, 0.0);//Not needed since already at origin

		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();




	//5th finger(thumb)
	//5th finger bone, always remains straight
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();
		glTranslated(0.25, 1.5, -0.12);
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 1.5, 0);	//Translate to wrist joint location
		
		glTranslated(0, -0.5, 0);//(1)experimental WORKS 
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.5, 0);	//(3)experimental Translate to wrist joint location


		glScalef(0.1, 0.5, 0.1);
		glTranslated(0.0, 0.0, 0.0);
		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();


	//2nd part of 5th finger, this one 'curls', ie rotates
	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();

	glTranslated(-0.0, 1.5, 0);
	glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//rotate around wrist joint
	glTranslated(0, 0.0, 0);

		glTranslated(0.25, 1.5, -0.0);	//translate it to same position as 1st bone
		glRotated(lowerRot, -lowerArmTran, 0, 0.0);	//This rotates along wrist joint
		glTranslated(0.0, 0.0, -0.12); //translates appropriately. Can be 1.75 or 1.7 
	
		glTranslated(0, -0.5, 0);//(1)experimental WORKS
		glRotated(wristRot, -wristTrans, 0, 0.0);	//(2) experimentalrotate around wrist joint
		glTranslated(0, 0.7, 0);

		glRotated(finger1_rot, finger1Translate, 0, 0.0);//Translates around its own x-axi
		glTranslated(0.0, 0.1, -0.0);//Needed as small num so it wont rotate by alot around own axis
		glScalef(0.1, 0.25, 0.1);//Scale same as 1st bone
		
		glTranslated(0.0, 0.0, 0.0);//Not needed since already at origin
		if (isSolid) {
			glutSolidCube(1.0);
		}
		else {
			glutWireCube(1.0);
		}
	glPopMatrix();
}





//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

	if (isAxes) 
	{
		drawAxes();
	}
	else {
		
	}
	
	drawBall();

	glPushMatrix();	//Not needed for now (1)
		glTranslated(xTran,0,zTran);
		glRotatef(rotation_45, 1, 0, 0); //rotate to see if obj in good place (2)
		glRotatef(shoulder_rotation, 0,1,0);

		drawStand();
		drawShoulderJoint();
		drawUpperArm();
		drawArmJoint();
		drawLowerArm();
		drawWristdJoint();
		drawHand();

	glPopMatrix();
	glutSwapBuffers();

}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		//Animate ball

		break;

	case 'c':
		if (pressedR) {
			pressedR = !pressedR;
		}
		isAxes = !isAxes;
		break;

	case 'i':
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn) {
			if (rotation_45 >= 90) {
				rotation_45 += 0;
			}
			else {
				rotation_45 += 2.5;
			}
		}
		else {
			;//do nothing
			break;
		}
		
		break;
	case 'I':
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn)
		{
			if (rotation_45 <= -90) {
				rotation_45 += 0;
			}
			else {
				rotation_45 -= 2.5;
			}
		}
		else {
			;
			break;
		}
		
		break;

	case 'j':	//Test case for various arm movements
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn) 
		{
			if (lowerRot <= -45) {
				lowerRot += 0;
				lowerArmTran += 0;
			}
			else {
				lowerArmTran -= 1;
				lowerRot -= 0.5;
			}
		}
		else {
			;
			break;
		}
		break;
	case 'J':	//Test case for various arm movements
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn)
		{
			if (lowerRot >= 45) {
				lowerRot += 0;
				lowerArmTran += 0;
			}
			else {
				lowerArmTran -= 1;
				lowerRot += 0.5;
			}
		}
		else {
			;
			break;
		}
		break;

	case 'm':
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn)
		{
			if (finger1_rot >= 90) {
				finger1Translate += 0;
			}
			else {
				finger1_rot += 1;
				finger1Translate += 0.25;
			}
		}
		else {
			;
			break;
		}
		break;
	case 'M':
		if (pressedR) {
			pressedR = !pressedR;
		}
		if(isOn)
		{
			if (finger1_rot <= -0) {
				finger1_rot += 0;
			}
			else {
				finger1_rot -= 1;
			}
		}
		else {
			;
			break;
		}

		break;

	case 'n':	//Test case for various arm movements
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn) 
		{
			if (wristRot <= -45) {
				wristRot += 0;
				wristTrans += 0;
			}
			else {
				wristTrans -= 1;
				wristRot -= 0.5;
			}
		}
		else {
			;
			break;
		}

		break;
	case 'N':	//Test case for various arm movements
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn)
		{
			if (wristRot >= 0) {
				wristRot += 0;
				wristTrans += 0;
			}
			else {
				wristTrans -= 1;
				wristRot += 0.5;
			}
		}
		else {
			;
			break;
		}

		break;
	case 'o':
		if (pressedR) {
			pressedR = !pressedR;
		}
		isOn = !isOn;
		break;
	case 'O':
		if (pressedR) {
			pressedR = !pressedR;
		}
		isOn = !isOn;
		break;
	case 'q':
		//exit
		exit(1);
		break;

	case 'r':
		//pressedR = !pressedR; //changes camera view
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn)
		{
			shoulder_rotation -= 5;
		}
		else {
			;
			break;
		}

		break;
	case 'R':
		if (pressedR) {
			pressedR = !pressedR;
		}
		if (isOn)
		{
			shoulder_rotation += 5;
		}
		else {
			;
			break;
		}		
		break;
	case 'u':
		if (pressedR) {
			pressedR = !pressedR;
		}
		isSolid = !isSolid;
		break;

	case 'v':
		//tt = 0;
		view++;
		view %= 3;
		if (view == 0) {
			eyex = 25;
			eyey = 25;
			eyez = 25;
		}
		else if (view == 1) {
			eyex = 25;
			eyey = 0;
			eyez = 0;
		}
		else if (view == 2) {
			eyex = 0;
			eyey = 25;
			eyez = 25;
		}
		break;
	case 's':

		pressedR = !pressedR;//toggle to view from different angles
		break;

	case 27://27 is ascii for escape key
//		exit(1);
		pressedR = false;
		isOn = true;
		isSolid = true;
		isAxes = true;
		
		shoulder_rotation = 0;
		rotation_45 = 0;
		upperRot = 0;

		eyex = 25.0, eyey = 25.0, eyez = 25.0;
		lookx = 0.0, looky = 0.0, lookz = 0.0;

		//Lower arm rotate and translate
		lowerRot = 0;
		lowerArmTran = 0;

		wristRot = 0;
		wristTrans = 0;
		finger1_rot = 0;
		finger1Translate = 0;
		finger2_rot = 0;
		finger3_rot = 0;
		finger4_rot = 0;
		finger5_rot = 0;

		xTran = 0;
		zTran = 0;
		tx = 0.0, ty = 0.0, tz = 0.0;
		break;

	default:
		break;
	}

	glutPostRedisplay();

}

//special keyboard

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch (theKey) {




	case GLUT_KEY_UP:
		// translate by a small ammount forward
		/*NOTE:  translates along LEFT (DARK BLUE) shoulder. So goes forward depennding on shoulder */
		if (isOn) 
		{
			xTran += 0.35 * cos(shoulder_rotation*PI / 180);
			zTran -= 0.35 * sin(shoulder_rotation*PI / 180);
		}
		else {
			;
			break;
		}

		break;
	case GLUT_KEY_DOWN:
		// translate by a small ammount backward
		/*NOTE:  translates along RIGHT(LIGHT BLUE) shoulder. So goes forward depennding on shoulder */
		if (isOn) 
		{
			xTran -= 0.35 * cos(shoulder_rotation*PI / 180);
			zTran += 0.35 * sin(shoulder_rotation*PI / 180);
		}
		else {
			;
			break;
		}

		break;

	default:
		break;		      // do nothing
	}
	glutPostRedisplay(); // implicitly call myDisplay
}







//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Inner Solar System"); // open the screen window


	int shadingChoice = 0;
	int colorChoice = 0;
	std::cout << "Enter Shading Choice (0 for Diffuse, 1 for Specular):\n";
	std::cin >> shadingChoice;

	std::cout << "Enter Color Option (0 for No Color, 1 for Color):\n";
	std::cin >> colorChoice;

	glutIdleFunc(myIdle);
	myInit(shadingChoice, colorChoice);

	glutDisplayFunc(displaySolarSystem);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);

	glutMainLoop();

	return(0);
}
