#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

using  namespace std;

class gameOver
{
public:
char name[10] = "GAME OVER";
char score[30] = "YOUR SCORE : ";
char play[30] = "PLAY AGAIN :        PRESS R";

public:
    void drawText(const char *text, int length, float x, float y)
    {
        glRasterPos2f(x,y);
        for(int i=0; i<length; i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
        }
    }
    void createGameOverScreen(string points, bool fullScreenMode) {

        glColor3d(1.0,0.0,1.0);
        glScalef(2,2,2);

        drawText(name, 10, -0.2, 0.30);
        drawText(score, 30, -0.3, 0.05);

        if(fullScreenMode == true)
        {
            glRasterPos2f(0.2,0.05);
        }
        else
        {
            glRasterPos2f(0.2,0.05);
        }

        for(int i=0; i<points.length(); i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)points[i]); // showing score
        }

        drawText(play, 30, -0.3, -0.05);
    }
};
