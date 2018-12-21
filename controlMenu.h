#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

using  namespace std;

class controlMenu
{
public:
char name[15] = "USER MOVEMENT";
char line[20] = "------------------";
char keyboard[9] = "KEYBOARD";
char line1[20] = "--------------";
char inst[12] = "INSTRUCTION";
char line2[20] = "-----------------";
char ins1[13] = "MOVE LEFT";
char ins2[14] = "MOVE RIGHT";
char ins3[10] = "GOLD EGG";
char ins4[15] = "WHITE EGG";
char ins5[10] = "BLACK EGG";
char ins6[10] = "MISS EGG";
char ins7[10] = "PAUSE";
char ins8[10] = "RESTART";
char ins9[10] = "QUIT";
char back_to_menu[5] = "BACK";

public:
    void drawText(const char *text, int length, float x, float y)
    {
        glRasterPos2f(x,y);
        for(int i=0; i<length; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
        }
    }
    void createControlMenu() {

        glColor3d(1.0,0.0,1.0);
        glScalef(2,2,2);
        drawText(name, 15, -0.25, 0.5);
        drawText(line, 20, -0.29, 0.45);

        drawText(keyboard, 9, -0.65, 0.3);
        drawText(line1, 20, -0.70, 0.25);

        drawText(ins1, 13, -0.80, 0.15);
        drawText(" -  a", 5, -0.40, 0.15);

        drawText(ins2, 14, -0.80, 0.10);
        drawText(" -  d", 6, -0.40, 0.10);

        drawText(ins5, 10, 0.15, 0.05);
        drawText(" -  (-5) HEALTH", 16, 0.45, 0.05);

        drawText(ins6, 10, 0.15, 0.00);
        drawText(" -  (-5) HEALTH", 16, 0.45, 0.00);

        drawText(inst, 12, 0.30, 0.3);
        drawText(line2, 20, 0.25, 0.25);

        drawText(ins3, 10, 0.15, 0.15);
        drawText(" -  10 POINTS", 14, 0.45, 0.15);

        drawText(ins4, 15, 0.15, 0.10);
        drawText(" -    5 POINTS", 15, 0.45, 0.10);

        drawText(ins7, 10, -0.80, 0.05);
        drawText(" -  spacebar", 13, -0.40, 0.05);

        drawText(ins8, 10, -0.80, 0.00);
        drawText(" -  r", 7, -0.40, 0.00);

        drawText(ins9, 10, -0.80, -0.05);
        drawText(" -  esc", 8, -0.40, -0.05);

        drawText(back_to_menu, 5, -0.10, -0.20);
    }
};
