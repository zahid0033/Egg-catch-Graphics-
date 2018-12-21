#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

using  namespace std;

class Menu
{
public:
char name[20] = "Egg-Basket Game";
char line[20] = "------------------";
char play[6] = "PLAY";
char resume[7] = "RESUME";
char control[9] = "CONTROLS";
char highScore[12] = "HIGH SCORES";
char quit[6] = "QUIT";

public:
    void drawText(const char *text, int length, float x, float y)
    {
        glRasterPos2f(x,y);
        for(int i=0; i<length; i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
        }
    }
    void createMenu(bool condition) {

        glColor3d(1.0,0.0,1.0);
        glScalef(2,2,2);
        drawText(name, 20, -0.5, 0.55);
        drawText(line, 20, -0.57, 0.50);

        if(condition)
        {
            drawText(resume, 7, -0.35,0.35);
        }
        else
        {
            drawText(play, 6, -0.35,0.35);
        }

        drawText(control, 9, -0.35,0.20);
        drawText(highScore, 12, -0.35,0.05);
        drawText(quit, 6, -0.35,-0.10);
    }
};
