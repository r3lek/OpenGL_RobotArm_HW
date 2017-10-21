#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>


#include "robotHeader.h"
/*
	

*/

/*Shading inside init fnc*/
void myInit(int shadingChoice, int colorChoice)
{
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

//Joint that connects to upper arm
void drawShoulderJoint()
{
	glColor3f(0.5f, 0.5f, 0.5f);    // sun is orange

	glPushMatrix();
	glTranslated(0, 0, 0);
//	glRotated(rotation_sun, 0, 1, 0);
	glutSolidSphere(0.35, 20, 16);	// locate the sun at the origin
	glPopMatrix();
}

//Actual upper arm thats connected btwn shoulder and upper arm joint
void drawUpperArm()
{

	glColor3f(0.0f, 0.0f, 0.0f);
	//1st part of upper arm
	glPushMatrix();
		glTranslated(-0.2, 1, 0.0);
//		glRotated(rotation_angle, tx, 0, 0);
		glTranslated(0.0,0.0,0);
		glScalef(0.1, 1.45, 0.1);
		//glRotated(rotation_sun, 0, 1, 0);
		glutSolidCube(1.0);	// locate the sun at the origin
	glPopMatrix();

	//2nd part of upper arm	//FIXED
	glPushMatrix();
		glTranslated(0.2, 1, 0.0);
		glScalef(0.1, 1.45, 0.1);
		//glRotated(rotation_sun, 0, 1, 0);
		glutSolidCube(1.0);	// locate the sun at the origin
	glPopMatrix();
}

//Draws upper arm joint (sphere)
void drawArmJoint()
{
	glColor3f(0.5f, 0.5f, 0.5f);    // sun is orange

	glPushMatrix();
		glTranslated(0, 1.5, 0);
		//	glRotated(rotation_sun, 0, 1, 0);
		glutSolidSphere(0.35, 20, 16);	// locate the sun at the origin
	glPopMatrix();
}


//Draw lower arm that connects between upper arm joint to wrist(another joint)
void drawLowerArm()
{
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();
		glTranslated(0.2, 1.5, 0); //where sphere is
		glRotated(rotation_angle, -tx, 0, 0.0);	//maybe switch tx for -tx, for 'down' movement
		glTranslated(0, 0.5, 0);
		glScalef(0.1, 1.0, 0.1);
		glTranslated(0.0, 0.0, 0.0);
		glutSolidCube(1);
	glPopMatrix();	
				

	//2nd part of upper arm	//FIXED
	glPushMatrix(); 	
		glTranslated(-0.2, 1.5, -0.0); //negative, adjust x coordinate
		glRotated(rotation_angle, -tx, 0, 0.0);	//Works, this order is needed
		glTranslated(0.0, 0.5, -0.0);			//^^ the 'first' (0,0,0) trans not needed
		glScalef(0.1, 1.0, 0.1);
		glTranslated(0.0, 0.0, 0.0);
		
		glutSolidCube(1.0);	// locate the sun at the origin
	glPopMatrix();


}

//Draw wrist joint
void drawWristdJoint()
{
	glColor3f(0.5f, 0.5f, 0.5f);    // sun is orange

	//(FIXED)Wrist, Works, put inside own function, andd add its own translateVariable, wristTX = ++
	glPushMatrix();
		glTranslated(-0, 1.5, -0.0); //negative, adjust x coordinate
		glRotated(rotation_angle, -tx, 0, 0.0);	//Works, this order is needed
		glTranslated(0.0, 1, -0.0);			//^^ the 'first' (0,0,0) trans not needed
											//glScalef(0.1, 1.0, 0.1);
		glTranslated(0.0, 0.0, 0.0);

		glutSolidSphere(0.35, 20, 16);	// locate the sun at the origin
	glPopMatrix();
}


//draw hand 
void drawHand() {

	//1st finger bone, always remains straight
	glColor3f(0.1f, 0.1f, 0.1f);  //'bones' are green
	glPushMatrix();
		glTranslated(0.0, 1.5, 0);
		glRotated(rotation_angle, -tx, 0, 0.0);	//rotate around wrist joint
		glTranslated(0, 1.5, 0);	//Translate to wrist joint location
		glScalef(0.1, 0.5, 0.1);
		glTranslated(0.0, 0.0, 0.0);
		glutSolidCube(1);
	glPopMatrix();

	//2nd part of finger, this one 'curls', ie rotates
	glColor3f(1.0f, 0.1f, 0.1f);
	glPushMatrix();
		glTranslated(0.0, 1.5, -0.0);	//translate it to same position as 1st bone
		glRotated(rotation_angle, -tx, 0, 0.0);	//This rotates along wrist joint

		glTranslated(0.0, 1.75, -0.0); //translates appropriately. Can be 1.75 or 1.7 
		glRotated(finger1_rot, -finger1Translate, 0, 0.0);//Translates around its own x-axi
		glTranslated(0.0, 0.1, -0.0);//Needed as small num so it wont rotate by alot around own axis
		glScalef(0.1, 0.25, 0.1);//Scale same as 1st bone
		glTranslated(0.0, 0.0, 0.0);//Not needed since already at origin
		glutSolidCube(1.0);	
	glPopMatrix();








}




void drawSun()
{	// Sun
	glColor3f(1.0f, 0.5f, 0.0f);    // sun is orange	//Wrist, Works, put inside own function, andd add its own translateVariable, wristTX = ++
	glPushMatrix();
		glTranslated(-0, 1.5, -0.0); //negative, adjust x coordinate
		glRotated(rotation_angle, -tx, 0, 0.0);	//Works, this order is needed
		glTranslated(0.0, 1, -0.0);			//^^ the 'first' (0,0,0) trans not needed
												//glScalef(0.1, 1.0, 0.1);
		glTranslated(0.0, 0.0, 0.0);

		glutSolidSphere(0.35, 20, 16);	// locate the sun at the origin
	glPopMatrix();

	glPushMatrix();
		glRotated(rotation_sun, 0, 1, 0);
		glutSolidSphere(0.5, 20, 16);	// locate the sun at the origin
	glPopMatrix();

}


//Attempted extra credit for earth and moon, popping 2x at the end
void drawEarthAndMoon()
{
	// Earth
	glColor3f(0.0f, 1.0f, 0.0f); // earth is green
	glPushMatrix();
	glRotated(rotation_earth, 0, 1, 0);	//added 
	glTranslated(0, 0, 2);
	glutSolidSphere(0.2, 20, 8);
	glColor3f(0, 0, 0);
	//glPopMatrix();	remove for moon

	// Moon
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glRotated(rotation_moon, 0, 1, 0);
	//glTranslated(0, 0, 2);
	//Add something here or remove the one with 2
	glTranslated(0, 0, 0.3);//make it slightly more 'out', so looks like it revolves earth
	glutSolidSphere(0.05, 10, 4);
	glPopMatrix();
	glPopMatrix();
}

void drawMars()
{
	// Mars
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotated(rotation_mars, 0, 1, 0); //added
	glTranslated(0, 0, 3);
	glutSolidSphere(0.15, 20, 8);
	glPopMatrix();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);


	drawAxes();

	glPushMatrix();	//Not needed for now (1)
		glRotatef(rotation_45, 1, 0, 0); //rotate to see if obj in good place (2)
		glRotatef(shoulder_rotation, 0,1,0);
		
		drawShoulderJoint();
		drawUpperArm();

		drawArmJoint();
		
//		glPushMatrix();	//This can rotate around y fine
//			glRotatef(rotation_sun, 0,1, 0);
		drawLowerArm();
//		glPopMatrix();	//Goes together with push matrix to rotate around y (3)

//	glPopMatrix();
		drawWristdJoint();
//		glPopMatrix();	//(3) - Rotates around its own y-axis. Goes together with first oush matrix

		drawHand();
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
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

	case 'r':
		pressedR = !pressedR;
		break;
	case 't':	//Test case for various arm movements
		tx += 1;
		rotation_angle += 0.5;
		break;
	case 'q' :
		rotation_45 += 5;
		break;
	case 'm':
		finger1_rot+=1;
		finger1Translate++;
		break;
	case 'i':
		shoulder_rotation+=5;
		break;



	default:
		break;
	}

	glutPostRedisplay();

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

	glutMainLoop();

	return(0);
}
