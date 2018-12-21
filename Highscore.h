#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <sstream>
using  namespace std;

class highScoreMenu
{
public:
string name = "HIGH SCORES";
string line = "------------------";
string back_to_menu = "BACK";

public:
    void drawText(string text, int length, float x, float y)
    {
        glRasterPos2f(x,y);
        for(int i=0; i<length; i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
        }
    }
    void createHighScoreMenu(int hgh) {

        glColor3d(1.0,0.0,1.0);
        glScalef(2,2,2);
        drawText(name, 11, -0.23, 0.5);
        drawText(line, 20, -0.3, 0.45);

        //reading from text file
        ifstream inFile;
        inFile.open("HighScoreOfGame.txt");

        if(!inFile)
        {
            cout<<"Unable to open the File !!"<<endl;
            exit(1);
        }

        string high, high1, high2, high3;
        short counter = 0;

        while(getline(inFile,high))
        {
            counter++;

            if(counter == 1)
                high1 = high;
            else if(counter == 2)
                high2 = high;
            else if(counter == 3)
                high3 = high;
        }

        short int len1,len2,len3;
         int len4;
        len1 = high1.length();
        len2 = high2.length();
        len3 = high3.length();
        ostringstream str1;
        str1<<hgh;
		string x=str1.str();
		len4=x.length();

        //cout<<high1<<" "<<high2<<" "<<high3<<endl;

        inFile.close();

        drawText("1. ", 4, -0.3, 0.2);
        drawText(x, len4, -0.2, 0.2);



        drawText(back_to_menu, 5, -0.12, -0.2);
    }
};
