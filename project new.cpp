#include <iostream>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <GL/glut.h>
#include "Menu.h"
#include "controlMenu.h"
#include "Highscore.h"
#include "GameOverScreen.h"

using namespace std;

Menu menu;
controlMenu controlScreen;
highScoreMenu highScore;
gameOver gameEndScreen;

int windowWidth  = 1024;     // Windowed mode's width
int windowHeight = 576;     // Windowed mode's height
int windowPosX   = 200;      // Windowed mode's top-left corner x
int windowPosY   = 100;

unsigned long int total_points = 0;
bool gCount = false; // writing high score once

bool soundPlayingFlag = false; // to switch from menu sound to background sound
bool gameOverSoundFlag = false;
bool restartFlag = false;
bool fromGameToMenu = false;
bool firstMenuFlag = false;

bool flag1 = false; //for zombie1 leg & hand movement

bool fullScreenMode = false;

bool paused = false; //pausing the game
bool gameMenu = true;
bool gameControlMenu = false;
bool showHighScore = false;
bool gameover = false;

float playerX = 0.0f;
float playerY = -2.15f;

int w,h;
int point=0;
int inc=5;
int life=100;
int healthInc=0;
int r,g,b;
int eggNum=1;
static float posx=0;

void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
		length = strlen(stringToDisplay);

	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}

}
void DisplayHealthBar() {
    char temp[200];
	glColor3f(0 ,0 ,1);
	sprintf(temp,"SCORE = %d",point);
  displayRasterText(-1.6,1,0.4,temp);

  glColor3f(0 ,0 ,1);
	sprintf(temp,"Level = 1");
  displayRasterText(0,1,0.4,temp);

  glColor3f(0 ,0 ,1);
	sprintf(temp,"Health = %d",life);
  displayRasterText(1.2,1,0.4,temp);
}

float getX(int x){
    return (float)x/(1600/2);
}

float getY(int y){
    return (float)y/(800/2);
}
int colorX=3;
void eggColor(int x){
    colorX=x;
   if(x==2)
   {
    r=218;
    g=165;
    b=32;
    inc=10;
    healthInc=0;
   }
   else if(x==1)
   {
    r=0;
    g=0;
    b=0;
    inc=0;
    healthInc=-5;
   }
   else{
    r=255;
    g=255;
    b=255;
    inc=5;
    healthInc=0;
   }
}
int previousPoint=0;
int previousHealth=5;
float _eggmove = 0.0;
float _cloud1 = 0.0;
float _k=0.0;

void myMouse(int b, int s, int x, int y) {      // mouse click callback
	if (s == GLUT_DOWN) {

            if(gameMenu && fullScreenMode == false)
            {
                if(b == GLUT_LEFT_BUTTON && ((x >= 345 && x <= 410) && (y >= 110 && y <= 127))) // start playing 509
                {
                    if(firstMenuFlag)
                    {
                        if(x >= 345 && x <= 410) // Check for resume button
                        {
                            gameMenu = false;
                            fullScreenMode = true;
                            point=previousPoint;
                            life=previousHealth;
                            glutFullScreen(); //start the game in full screen
                            glutPostRedisplay();
                        }
                    }
                    else
                    {
                        if(x >= 345 && x <= 410)
                        {
                            gameMenu = false;
                            fullScreenMode = true;
                            glutFullScreen(); //start the game in full screen
                            glutPostRedisplay();
                        }
                    }
                }
                else if(b == GLUT_LEFT_BUTTON && ((x >= 345 && x <= 480) && (y >= 175 && y <= 195))) //open sub menu
                {
                    gameControlMenu = true;
                    gameMenu = false;
                    glutPostRedisplay();
                }
                else if(b == GLUT_LEFT_BUTTON && ((x >= 345 && x <= 510) && (y >= 245 && y <= 265))) // open sub menu
                {
                    showHighScore = true;
                    gameMenu = false;
                    glutPostRedisplay();
                }
                else if(b == GLUT_LEFT_BUTTON && ((x >= 345 && x <= 410) && (y >= 315 && y <= 335))) // exit
                {
                    exit(0);
                }
            }

            else if(gameControlMenu && fullScreenMode == false)
                {
                    if((x >= 462 && x <= 518) && (y >= 365 && y <= 385))
                    {
                        gameControlMenu = false;
                        gameMenu = true;
                        glutPostRedisplay();
                    }
                }

                else if(showHighScore && fullScreenMode == false)
                {
                    if((x >= 455 && x <= 523) && (y >= 362 && y <= 383))
                    {
                        showHighScore = false;
                        gameMenu = true;
                        glutPostRedisplay();
                    }
                }

            else
            {
                if (b == GLUT_LEFT_BUTTON && paused == false && gameover == false) {


                        glutPostRedisplay();
                    }

            }
	}
}

void keyboard(unsigned char key, int x, int y)
{
switch (key) {
case 'd': /* a key rotates at shoulder */
if(posx<1.3){
    posx = (posx + .1);
}

//posx++;
glutPostRedisplay();
break;
case 'a':
    if(posx>-1.3){
       posx = (posx - .1);
    }

//posx--;
glutPostRedisplay();
break;

case 27: // quit
gameover = true;
glutReshapeWindow(windowWidth, windowHeight);
glutPositionWindow(200, 100);   // Position top-left corner (windowPosX, windowPosY)
fullScreenMode = false;
glutPostRedisplay();
break;

case 32: //main menu
            previousPoint=point;
            previousHealth=life;
            life=100;
            gameover = false;
            gameMenu = true;
            glutReshapeWindow(windowWidth, windowHeight);
            glutPositionWindow(200, 100);   // Position top-left corner (windowPosX, windowPosY)
            fullScreenMode = false;
            glutPostRedisplay();

            break;

    case 'r': //restart
            gameover = false;

          //  reset(); //resetting everything

            gameMenu = true;
            life=100;
            point=0;
            gameOverSoundFlag = false;
            glutReshapeWindow(windowWidth, windowHeight);
            glutPositionWindow(200, 100);   // Position top-left corner (windowPosX, windowPosY)
            fullScreenMode = false;
            //reseted

            glutPostRedisplay();

            break;

default:
break;
    }

}


void update(int value) {


	_eggmove += 0.02f;


	if(_eggmove>.4){

            switch(eggNum)
            {
            case 4:
                if(posx<1.4 && posx>1.1){
                    life+=healthInc;
                    point+=inc;
                 //cout<<""<<life<<""<<point<<endl;
                 _eggmove = -.4f;
                  eggColor((double)(rand()%3+1));
                }
                else if(_eggmove>.5)
                {
                if(colorX!=1)
                life-=5;
                _eggmove = -.4f;
                 eggColor((double)(rand()%3+1));
                }
                break;
            case 3:
                if(posx<0.75 && posx>0.45){
                    life+=healthInc;
                    point+=inc;
                 //cout<<""<<life<<""<<point<<endl;
                 _eggmove = -.4f;
                  eggColor((double)(rand()%3+1));
                }
                else if(_eggmove>.5)
                {
                if(colorX!=1)
                life-=5;
                _eggmove = -.4f;
                 eggColor((double)(rand()%3+1));
                }
                break;
            case 2:
                 if(posx<0.15 && posx>-0.25){
                    life+=healthInc;
                    point+=inc;
                 //cout<<""<<life<<" Point="<<point<<endl;
                 _eggmove = -.4f;
                  eggColor((double)(rand()%3+1));
                }
                else if(_eggmove>.5)
                {
                if(colorX!=1)
                life-=5;
                _eggmove = -.4f;
                 eggColor((double)(rand()%3+1));
                }
                break;
            default:
                if(posx<-0.6 && posx>-1){
                    life+=healthInc;
                    point+=inc;
                 //cout<<""<<life<<" Point="<<point<<endl;
                 _eggmove = -.4f;
                  eggColor((double)(rand()%3+1));
                }
                else if(_eggmove>.5)
                {
                if(colorX!=1)
                life-=5;
                _eggmove = -.4f;
                 eggColor((double)(rand()%3+1));
                }
                break;
            }
    if(_eggmove==-0.4f)
    {
       // DisplayHealthBar();
      eggNum=(double)(rand()% 4+1);
    }

	}



    glutPostRedisplay();

    _cloud1 += .0006;
    if(_cloud1-1.0 > 1.0)
    {
        _cloud1 = -1.0;
    }
	glutPostRedisplay(); //Notify GLUT that the display has changed

	glutTimerFunc(25, update, 0); //Notify GLUT to call update again in 25 milliseconds
}

///egg1

void egg(){
glPushMatrix();
glColor3ub(r,g,b);
glTranslatef(-.7,-_eggmove,0);
//glTranslatef(_k,-_eggmove,0);
glScalef(.6,1,1);
glutSolidSphere(.05,25,25);


glPopMatrix();
}
///egg2
void egg2(){
glPushMatrix();
glColor3ub(r,g,b);
glTranslatef(0,-_eggmove,0);
//glTranslatef(_k,-_eggmove,0);
glScalef(.6,1,1);
glutSolidSphere(.05,25,25);


glPopMatrix();
}
///egg3
void egg3(){
glPushMatrix();
glColor3ub(r,g,b);
glTranslatef(.7,-_eggmove,0);
//glTranslatef(_k,-_eggmove,0);
glScalef(.6,1,1);
glutSolidSphere(.05,25,25);


glPopMatrix();
}
///egg4
void egg4(){
glPushMatrix();
glColor3ub(r,g,b);
glTranslatef(1.4,-_eggmove,0);
//glTranslatef(_k,-_eggmove,0);
glScalef(.6,1,1);
glutSolidSphere(.05,25,25);


glPopMatrix();
}
///basket
void basket(){

glPushMatrix();
//glRotatef(,0,.10,0);
glTranslatef(0,-.6,0);

glTranslatef(posx,0,0);
//tire
glPushMatrix();
glColor3f(0,0,0);
glutSolidSphere(.02,25,25);
glPopMatrix();


glPushMatrix();
glColor3f(1,1,0);
glutSolidTorus(.02,.04,25,25);
glPopMatrix();

//tire2
glPushMatrix();
glColor3f(0,0,0);
glTranslatef(.2,0,0);
glutSolidSphere(.02,25,25);
glPopMatrix();

glPushMatrix();
glColor3f(1,1,0);
glTranslatef(.2,0,0);
glutSolidTorus(.02,.04,25,25);
glPopMatrix();



//upper

glBegin(GL_POLYGON);
glColor3ub(240,200,206);
glVertex3f(-.05,.17,0);
glVertex3f(.25,.17,0);
glVertex3f(.3,.2,0);
glVertex3f(.25,.23,0);
glVertex3f(-.05,.23,0);
glVertex3f(-.1,.2,0);
glEnd();

//lower
glBegin(GL_POLYGON);
glColor3ub(143,64,66);
glVertex3f(-.02,.08,0);
glVertex3f(.22,.08,0);
glVertex3f(.3,.2,0);
glVertex3f(-.1,.2,0);
glEnd();

//trolly

glBegin(GL_POLYGON);
glColor3ub(0,0,0);
glVertex3f(-.1,0,0);
glVertex3f(.3,0,0);
glVertex3f(.3,.1,0);
glVertex3f(-.1,.1,0);
glEnd();

glPopMatrix();

}

void bird(){
glPushMatrix();

    glColor3ub(0, 255, 0);
    glScalef(.7,.7,1);
    glTranslatef(0,.35,0);
      //eyeball
 glPushMatrix();
    glColor3ub(0,0,0);
    glTranslatef(.155,.655,0);
    glutSolidSphere(.02,25,25);
    glPopMatrix();
//eye
    glPushMatrix();
    glColor3ub(255,255,255);
    glTranslatef(.15,.65,0);
    glutSolidSphere(.02,25,25);
    glPopMatrix();

//wings
    glBegin(GL_LINES);
    glColor3ub(0,220,0);
    glVertex3f(.22, .56, 0);
    glVertex3f(.3, .5, 0);

    glVertex3f(.3, .5, 0);
    glVertex3f(.4, .56, 0);
    glEnd();
//legs
glBegin(GL_LINE_LOOP);
    glVertex3f(.3,.4,0);
    glVertex3f(.3,.43,0);
    glVertex3f(.2,.43,0);
    glVertex3f(.3,.43,0);


    glEnd();

    //body
    glBegin(GL_POLYGON);
    glColor3ub(0,255,0);
    glVertex3f(.15, .5, 0);
    glVertex3f(.2, .43, 0);
    glVertex3f(.4, .43, 0);
    glVertex3f(.45, .5, 0);
    glVertex3f(.4, .57, 0);
    glVertex3f(.2, .57, 0);
    glEnd();


     //tail
    glBegin(GL_POLYGON);
    glColor3ub(0,255,0);
    glVertex3f(.4, .53, 0);
    glVertex3f(.5, .56, 0);
    glVertex3f(.45, .6, 0);

    glEnd();

    //neck
    glBegin(GL_POLYGON);
    glColor3ub(0, 255, 0);
    glVertex3f(.15, .5, 0);
    glVertex3f(.20, .5, 0);
    glVertex3f(.25, .65, 0);
    glVertex3f(.20, .65, 0);
    glEnd();



    //mouth
    glBegin(GL_POLYGON);
    glColor3ub(0, 255, 0);
    glVertex3f(.25, .65, 0);
    glVertex3f(.15, .60, 0);
    glVertex3f(.08, .65, 0);
    glVertex3f(.17, .70, 0);
    glEnd();


    //throat
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 0);
    glVertex3f(.08, .65, 0);
    glVertex3f(.15, .60, 0);
    glVertex3f(.1, .55, 0);

    glEnd();
 glPopMatrix();

}
void tree()
{
    ///tree
    glPushMatrix();
    glTranslatef(-.1,-0.1,0);
    glBegin(GL_POLYGON);
    glColor3ub(210,180,75);
    glVertex3f(-1.58,0,0);
    glVertex3f(-1.5,0,0);
    glVertex3f(-1.5,0.3,0);
    glVertex3f(-1.58,0.3,0);
    glEnd();
    //left part
     glBegin(GL_POLYGON);
    glColor3ub(210,180,75);
    glVertex3f(-1.58,0.28,0);
    glVertex3f(-1.52,0.28,0);
    glVertex3f(-1.57,0.35,0);
    glVertex3f(-1.63,0.35,0);
    glEnd();
    //right part
    glBegin(GL_POLYGON);
    glColor3ub(215,185,80);
    glVertex3f(-1.56,0.28,0);
    glVertex3f(-1.5,0.28,0);
    glVertex3f(-1.45,0.35,0);
    glVertex3f(-1.51,0.35,0);
    glEnd();

    //leaf
    glColor3ub(58,95, 11);
    glPushMatrix();
	glTranslatef(-1.54,.56, 0.0);
    glScalef(.2,.2,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=.5;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
	glPopMatrix();
	glColor3ub(58,95, 11);
    glPushMatrix();
	glTranslatef(-1.68,.48, 0.0);
    glScalef(.2,.2,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=.5;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
	glPopMatrix();
	glColor3ub(58,95, 11);
    glPushMatrix();
	glTranslatef(-1.4,.48, 0.0);
    glScalef(.2,.2,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=.5;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
	glPopMatrix();


     glColor3ub(58,95, 11);
    glPushMatrix();
	glTranslatef(-1.54,.44, 0.0);
    glScalef(.2,.2,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=.8;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}


void initRendering() {
    glEnable(GL_DEPTH_TEST);
}
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float _angle_2 = 90;
float i = 0.0f;


void levelOne() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
    glTranslatef(0.0, 0.0, -3.0); //Move forward 5 units

    if(gameover)
    {
        firstMenuFlag = false;

        //writing highscore once

        if(gCount == false)
        {
            string value; // to store high score from text file
            unsigned long int v1,v2,v3; // 3 High scores
            short c = 0;

            ifstream inFile;
            inFile.open("Highscore.txt");

            while(getline(inFile,value))
            {
                c++;

                if(c == 1)
                {
                    v1 = atoi(value.c_str());
                }
                else if(c == 2)
                {
                    v2 = atoi(value.c_str());
                }
                else if(c == 3)
                {
                    v3 = atoi(value.c_str());
                }
            }

            inFile.close();//cout<<v1<<" "<<v2<<" "<<v3<<endl;

            if(point > v1)
                v1 = point;
            else if(point > v2)
                v2 = point;
            else if(point > v3)
                v3 = point;

            //cout<<v1<<" "<<v2<<" "<<v3<<endl;

            ofstream outFile;
            outFile.open("Highscore.txt");

            value = "";
            stringstream dd;

            dd << v1;
            value = dd.str();
            value+="\n";
            dd.str("");

            dd << v2;
            value += dd.str();
            value+="\n";
            dd.str("");

            dd << v3;
            value += dd.str(); //cout<<value<<endl;

            outFile << value;


            outFile.close();

            gCount = true;
        }

        //sending score to game-over screen

        stringstream ff;
        ff << point;
        char temp[100];
        sprintf(temp,"%d",point);
        string points =temp ;


        if(gameOverSoundFlag == false)
        {
            //start game over voice
            mciSendString("close GameOverTheme", NULL, 0, NULL); //closing the song file
            mciSendString("open \"game over.mp3\" type mpegvideo alias GameOverTheme", NULL, 0, NULL); //open the mp3 file
            mciSendString("play GameOverTheme", NULL, 0, NULL); //repeat
            gameOverSoundFlag = true;
        }

        //start playing theme song
        mciSendString("open \"theme.mp3\" type mpegvideo alias themeSong", NULL, 0, NULL); //open the mp3 file
        mciSendString("play themeSong repeat", NULL, 0, NULL); //repeat

        gameEndScreen.createGameOverScreen(points, fullScreenMode); // sending score
    }
    else if(gameMenu) //creating menu
    {

        soundPlayingFlag = true;
        gameOverSoundFlag = false;
        menu.createMenu(firstMenuFlag);
    }
    else if(gameControlMenu)
    {
        controlScreen.createControlMenu(); //sub menu
    }
    else if(showHighScore)
    {
        highScore.createHighScoreMenu(); // sub menu
    }
    else //Game started
    {

    DisplayHealthBar();
///-----------------------------------HALF SURFACE--------------------------
/*glPopMatrix();
    glPushMatrix();
    glColor3f(0.212, 0.212, 0.212);
    glTranslatef(0.0,-0.9,0.0);
    glScalef(20.0, 4.0, 1.0);
    glutSolidCube(.30);
    glPopMatrix();*/

///-------------------------END SURFACE------------------------------

///-------------------------------CLOUD------------------------------

 glPushMatrix();
    glScalef(1.5, 1.5, 0.70);
    glTranslatef(_cloud1, -.1, 0);

glColor3ub(255,255,255);

    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.044;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.98f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.95f,y+.8f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.9f,y+.82f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.04;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.94f,y+.74f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.85f,y+.8f );
	}
	glEnd();

glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.043;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.81f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.87f,y+.75f );
	}
	glEnd();

         glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.044;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.42,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.41f,y+.8f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.36f,y+.82f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.04;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.40f,y+.74f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.31f,y+.8f );
	}
	glEnd();

glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.043;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.29f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.33f,y+.75f );
	}
	glEnd();



	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.33f,y+.68f );
	}
	glEnd();

    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.043;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x-.40f,y+.69f );
	}
	glEnd();

//3RD CLOUD


  glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.044;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.10,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.13f,y+.8f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.18f,y+.82f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.04;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.14f,y+.74f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.23f,y+.8f );
	}
	glEnd();

glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.043;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.27f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.21f,y+.75f );
	}
	glEnd();


//4TH CLOUD

  glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.044;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.20,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.23f,y+.8f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.28f,y+.82f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.04;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.24f,y+.74f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.23f,y+.8f );
	}
	glEnd();

glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.043;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.37f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.31f,y+.75f );
	}
	glEnd();
//5TH CLOUD

  glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.044;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.10f+.70f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.13f+.70F,y+.8f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.18f+.7f,y+.82f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.04;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.14f+.7f,y+.74f );
	}
	glEnd();

 glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.035;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.23f+.7f,y+.8f );
	}
	glEnd();

glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.043;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.27f+.7f,y+.74f );
	}
	glEnd();

	glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.05;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x+.21f+.7,y+.75f );
	}
	glEnd();
glPopMatrix();
//----------------------------END CLOUD--------------------------

//-------------------------------SUN BEGIN------------------------------
    glColor3ub(255, 140, 76);
    glPushMatrix();
	glTranslatef(1.7, 0.9, 0.0);
    glScalef(.2,.2,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=.7;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
	glPopMatrix();
//----------------------------------SUN END------------------------

///eggsss
switch(eggNum)
{
case 4:
    egg4();
    break;
case 3:
    egg3();
    break;
case 2:
    egg2();
    break;
default:
    egg();
    break;
}
//egg();
//egg2();
//egg3();
//egg4();
 ///wire
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex3f(-1.85,0.48,0);
    glVertex3f(2,0.55,0);
    glEnd();
///pole_left
    glPushMatrix();


    glColor3ub(220, 200, 200);

    glBegin(GL_POLYGON);
    glVertex3f(-1.9,-.85,0);
    glVertex3f(-1.85,-.85,0);
    glVertex3f(-1.85,0.5,0);
    glVertex3f(-1.9,0.5,0);
    glEnd();

    glColor3ub(202, 141, 66);

    glBegin(GL_POLYGON);
    glVertex3f(-1.95,-.9,0);
    glVertex3f(-1.75,-.9,0);
    glVertex3f(-1.8,-.8,0);
    glVertex3f(-2,-.8,0);
    glEnd();
    glPopMatrix();




///basket
basket();








///pole_Right

     glPushMatrix();
    glColor3ub(220, 200, 200);
    glTranslatef(3.5,.28,0);


    glBegin(GL_POLYGON);
    glVertex3f(-1.5,-.75,0);
    glVertex3f(-1.45,-.75,0);
    glVertex3f(-1.45,0.3,0);
    glVertex3f(-1.5,0.3,0);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3ub(202, 141, 66);
    glVertex3f(-1.55,-.78,0);
    glVertex3f(-1.38,-.78,0);
    glVertex3f(-1.42,-.72,0);
    glVertex3f(-1.58,-.72,0);
    glEnd();
    glPopMatrix();

///ROAD DIVIDER
 glPushMatrix();
    glColor3f(1,1,1);

   glBegin(GL_LINES);
   glVertex3f(-2.5,-.62,0);
   glVertex3f(-2.3,-.62,0);
   glVertex3f(-2.1,-.62,0);
   glVertex3f(-1.9,-.62,0);
   glVertex3f(-1.7,-.62,0);
   glVertex3f(-1.5,-.62,0);
   glVertex3f(-1.3,-.62,0);
   glVertex3f(-1.1,-.62,0);
   glVertex3f(-.9,-.62,0);
   glVertex3f(-.7,-.62,0);
   glVertex3f(-.5,-.62,0);
   glVertex3f(-.3,-.62,0);
   glVertex3f(-.1,-.62,0);
   glVertex3f(.1,-.62,0);
   glVertex3f(.3,-.62,0);
   glVertex3f(.5,-.62,0);
   glVertex3f(.7,-.62,0);
   glVertex3f(.9,-.62,0);
   glVertex3f(1.1,-.62,0);
   glVertex3f(1.3,-.62,0);
   glVertex3f(1.5,-.62,0);
   glVertex3f(1.7,-.62,0);
   glVertex3f(1.9,-.62,0);
   glVertex3f(2.1,-.62,0);
   glVertex3f(2.3,-.62,0);
   glVertex3f(2.5,-.62,0);

   glEnd();
   glPopMatrix();
   ///home road
   glPushMatrix();
   glColor3ub(160,180,70);
   glBegin(GL_POLYGON);
   glVertex3f(-1.05,-.5,0);
   glVertex3f(-.95,-.5,0);
   glVertex3f(-1.25,-.2,0);
   glVertex3f(-1.35,-.2,0);
   glEnd();
   glPopMatrix();

   ///house


    ///////////////////right body window (right)
    glPushMatrix();
    glTranslatef(-1.72,-.1,0);
    glPushMatrix();
    glColor3ub (90, 90, 90);
    glBegin(GL_QUADS);
    glVertex3f(.48, -.04,0);
    glVertex3f(.56, -.04,0);
    glVertex3f(.56, .04,0);
    glVertex3f(.48, .04,0);
    glEnd();
    glPopMatrix();
      //right body window (left)
    glPushMatrix();
    glTranslatef(-0.26,0,0);
    glColor3ub (90, 90, 90);
    glBegin(GL_QUADS);
    glVertex3f(.48, -.04,0);
    glVertex3f(.56, -.04,0);
    glVertex3f(.56, .04,0);
    glVertex3f(.48, .04,0);
    glEnd();
    glPopMatrix();

    //left body window
    glPushMatrix();
    glTranslatef(-0.36,0,0);
    glColor3ub (90, 90, 90);
    glBegin(GL_QUADS);
    glVertex3f(.48, -.04,0);
    glVertex3f(.54, -.04,0);
    glVertex3f(.54, .04,0);
    glVertex3f(.48, .04,0);
    glEnd();
    glPopMatrix();
    //door
    glPushMatrix();
    glTranslatef(-0.14,0,0);
    glColor3ub (90, 90, 90);
    glBegin(GL_QUADS);
    glVertex3f(.48, -.08,0);
    glVertex3f(.56, -.08,0);
    glVertex3f(.56, .08,0);
    glVertex3f(.48, .08,0);
    glEnd();
    glPopMatrix();


   //right  chal
    glColor3ub (159, 93, 10);
    glBegin(GL_QUADS);
    glVertex3f(.2, .1,0);
    glVertex3f(.6, .1,0);
    glVertex3f(.55, .3,0);
    glVertex3f(.15, .3,0);
    glEnd();


//line of chal
    glPushMatrix();
    glColor3ub (150, 140, 70);
    glPointSize(5);
    glBegin(GL_LINES);
    glVertex3f(.1, .1,0);
    glVertex3f(.16, .28,0);
     glEnd();
     glPopMatrix();
//left triangle or chal
    glColor3ub (120, 108, 60);
    glBegin(GL_TRIANGLES);
    glVertex3f(.08, .1,0);
    glVertex3f(.2, .1,0);
    glVertex3f(.15, .3,0);
    glEnd();




    ////////////////// left body
    glColor3ub (140, 140, 140);
    glBegin(GL_QUADS);
    glVertex3f(.1, -.1,0);
    glVertex3f(.2,-.1,0);
    glVertex3f(.2, .1,0);
    glVertex3f(.1, .1,0);
    glEnd();
    ///////////right body
    glColor3ub (180, 180, 180);
    glBegin(GL_QUADS);
    glVertex3f(.2, -.1,0);
    glVertex3f(.58, -.1,0);
    glVertex3f(.58, .1,0);
    glVertex3f(.2, .1,0);
    glEnd();


glPopMatrix();
glPopMatrix();

///tree
glPushMatrix();
tree();
glPopMatrix();
glPushMatrix();
glScalef(.8,.8,0);
glTranslatef(3.9,.1,0);
tree();
glPopMatrix();
glPushMatrix();
glScalef(.2,.2,0);
glTranslatef(9.7,.3,0);
tree();
glPopMatrix();
glPushMatrix();
glScalef(.2,.2,0);
glTranslatef(-3.8,.5,0);
tree();
glPopMatrix();

	///bird
    glPopMatrix();
   glPushMatrix();
	glTranslatef(-.3,-.03,0);
	bird();
   glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1,-.045,0);
	bird();
    glPopMatrix();
    glTranslatef(.4,-.01,0);
	bird();

    glTranslatef(.7,0,0);
	bird();
   glPopMatrix();


    ///grass
glPushMatrix();
    glColor3ub(90, 168, 64);

   glBegin(GL_POLYGON);
   glVertex3f(-15,-.5,0);
   glVertex3f(15,-.5,0);
   glVertex3f(15,0.1,0);
   glVertex3f(-15,0.1,0);
   glEnd();

    glPopMatrix();
    ///footpath
       glPushMatrix();
    glColor3ub(195,159,10);

   glBegin(GL_POLYGON);
   glVertex3f(-15,-.78,0);
   glVertex3f(15,-.78,0);
   glVertex3f(15,-.77,0);
   glVertex3f(-15,-.77,0);
   glEnd();

    glPopMatrix();
       glPushMatrix();
    glColor3ub(95,59,10);

   glBegin(GL_POLYGON);
   glVertex3f(-15,-.8,0);
   glVertex3f(15,-.8,0);
   glVertex3f(15,-.75,0);
   glVertex3f(-15,-.75,0);
   glEnd();

    glPopMatrix();



///road
    glPushMatrix();
    glColor3f(0.412, 0.412, 0.412);

   glBegin(GL_POLYGON);
   glVertex3f(-15,-.8,0);
   glVertex3f(15,-.8,0);
   glVertex3f(15,-.5,0);
   glVertex3f(-15,-.5,0);
   glEnd();

    glPopMatrix();


    ///ground
    glPushMatrix();
    glColor3ub(90, 168, 64);

    glBegin(GL_POLYGON);
    glVertex3f(-15,-1,0);
    glVertex3f(15,-1,0);
    glVertex3f(15,-.8,0);
    glVertex3f(-15,-.8,0);
    glEnd();
    glPopMatrix();


///sky
glPushMatrix();
glColor3ub (120, 219, 237);
   // glPointSize(5.0);
    glBegin(GL_POLYGON);
    glVertex2f(getX(2500),getY( 800));
    glVertex2f(getX(-2700),getY( 800));
    glVertex2f(getX(-2700),getY( 30));
    glVertex2f(getX(2500),getY( 30));
glEnd();
glPopMatrix();



//----------------------END ROAD------------------
    }
    glutSwapBuffers();
}

void drawScene() {
   if(life>0)
   {
       levelOne();
   }
   else if(life<=0)
   {
       gameMenu = false;
       gameover = true;
       levelOne();
       glutReshapeWindow(windowWidth, windowHeight);
       glutPositionWindow(200, 100);   // Position top-left corner (windowPosX, windowPosY)
       fullScreenMode = false;
       glutPostRedisplay();
   }

}


int main(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);

    glutCreateWindow("View");
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(20, update, 0);
    //glutFullScreen();
    glutMouseFunc(myMouse);

	srand(time(NULL));
	//PlaySound("theme.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

	if(gameMenu)
    {
        mciSendString("open \"theme.mp3\" type mpegvideo alias themeSong", NULL, 0, NULL); //open the mp3 file
        mciSendString("play themeSong repeat", NULL, 0, NULL); //repeat
    }

    glutMainLoop();
    return 0;
}
