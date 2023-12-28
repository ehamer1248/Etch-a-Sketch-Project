// project.c 
// Manny Hamer
// Fund Comp
// Mini Final Project
// 12/7/2023
// This program replicates the kids toy known as an Etch A Sketch which allows the user to draw on a screen using dials that control the 
// up and down and left and right directions. In this program, the movement of these dials is simulated using the wasd keys, e is used to
// erase the board, and q is used to quit the program. The challenge of drawing on an etch a sketch was something I enhoyed as a child, so 
// I decided to replicate it here


#include <stdio.h>
#include <math.h>

// include new gfx library

#include "gfx2.h"

// define height and width of drawing screen to have a total of 10,800 pixels

#define pixelw 120
#define pixelh 90



// struct for properties of each of the pixels

typedef struct {

  int isFilled;
  int isChanged;
  int h;
  int w;

} Pixel;


// fucntion prototypes

void initBoard(Pixel arr[][pixelh], int ix, int iy);
void drawBoard(Pixel arr[][pixelh]);
int drawUp(Pixel arr[][pixelh], int cx, int cy);
int drawLeft(Pixel arr[][pixelh], int cx, int cy);
int drawRight(Pixel arr[][pixelh], int cx, int cy);
int drawDown(Pixel arr[][pixelh], int cx, int cy);
void drawLeftDial();
double moveLeftDial(double rad, double radchange, int leftRight);
double moveRightDial(double rad, double radchange, int upDown);
void drawRightDial();
void drawOutline();
void erase();
void printName();

int main() {

  // Initialize 2D struct array for the pixels

  Pixel pixArr[pixelw][pixelh];

  // intialize height and width of board, intial drawing positions on the screen, variables to keep track of 
  // the movement of the drawing, and variables for the simulation of the turning of the dials
  
  int width = 800, height = 700, ix = 60, iy = 45, cx = 60, cy = 45;
  double radL = 0, radR = M_PI, radchange = M_PI/35;

  // print controls to the user 

  printf("Welcome to the virtual Etch A Sketch\n\n");
  printf("Controls:\n");
  printf("w: Draw Up\n");
  printf("a: Draw Left\n");
  printf("s: Draw Down\n");
  printf("d: Draw Right\n");
  printf("e: Erase Board\n");
  printf("q: Quit Program\n");


  // open the window

  gfx_open(width, height, "Etch a Sketch");

  // draw the outline of the etch a sketch

  drawOutline();
  drawLeftDial();
  drawRightDial();
  printName();

  // initialize the board and draw the first point in the center

  initBoard(pixArr,ix,iy);
  drawBoard(pixArr);
  
  // intialize char for gfx events

  char c;


  // while loop to run until program is done

  while(1) {

    // gfx wait function equal to c
  
    c = gfx_wait();
    

    // switch statement to control drawing
    switch (c) {

      // case to draw up
    
      case 'w':
        cy = drawUp(pixArr,cx,cy);
        radR = moveRightDial(radR,radchange,0);
        break;

      // case to draw left

      case 'a':
        cx = drawLeft(pixArr,cx,cy);
        radL = moveLeftDial(radL,radchange,1);
        break;

      // case to draw down
    
      case 's':
        cy = drawDown(pixArr,cx,cy);
        radR = moveRightDial(radR,radchange,1);
        break;
      
      // case to draw right
    
      case 'd':
        cx = drawRight(pixArr,cx,cy);
        radL = moveLeftDial(radL,radchange,0);
        break;

      // case to erase
    
      case 'e':
        erase(); // erase board
        initBoard(pixArr,cx,cy); // reinitialize it a current drawing point
        break;

      // case to end program

      case 'q':
        printf("Thank you for drawing!!!");
        return 0;
        break;
    }

    // redraw new point on the board

    drawBoard(pixArr);
    

  }

}

// function to erase board

void erase() 

{

// redraw rectangle on top of board

gfx_color(236,231,230);
gfx_fill_rectangle(100,100,600,450);

}

// function to draw the etch a sketch graphic outline using rgb gradient from
// etch a sketch

void drawOutline()

{

  // background

  gfx_color(223,178,175);
  gfx_fill_rectangle(0,0,800,700);

  // screen rectangle 

  gfx_color(236,231,230);
  gfx_fill_rectangle(100,100,600,450);

  // left side

  gfx_color(223,178,175);
  gfx_fill_rectangle(0,100,6,450);
  gfx_color(237,135,128);
  gfx_fill_rectangle(6,100,6,450);
  gfx_color(241,113,92);
  gfx_fill_rectangle(12,100,6,450);
  gfx_color(234,84,92);
  gfx_fill_rectangle(18,100,6,450);
  gfx_color(250,11,11);
  gfx_fill_rectangle(24,100,70,450);

  gfx_color(234,84,92);
  gfx_fill_rectangle(94,100,3,450);
  gfx_color(241,113,92);
  gfx_fill_rectangle(97,100,3,450);


  // right side 

  gfx_color(223,178,175);
  gfx_fill_rectangle(794,100,6,450);
  gfx_color(237,135,128);
  gfx_fill_rectangle(788,100,6,450);
  gfx_color(241,113,92);
  gfx_fill_rectangle(782,100,6,450);
  gfx_color(234,84,92);
  gfx_fill_rectangle(776,100,6,450);
  gfx_color(250,11,11);
  gfx_fill_rectangle(706,100,70,450);

  gfx_color(234,84,92);
  gfx_fill_rectangle(703,100,3,450);
  gfx_color(241,113,92);
  gfx_fill_rectangle(700,100,3,450);

  // finish outline right around board

  gfx_color(234,84,92);
  gfx_fill_rectangle(94,94,612,3);
  gfx_color(241,113,92);
  gfx_fill_rectangle(94,97,612,3);
  gfx_color(241,113,92);
  gfx_fill_rectangle(94,553,612,3);
  gfx_fill_rectangle(782,100,6,450);
  gfx_color(234,84,92);
  gfx_fill_rectangle(776,100,6,450);
  gfx_color(250,11,11);
  gfx_fill_rectangle(706,100,70,450);

  gfx_color(234,84,92);
  gfx_fill_rectangle(703,100,3,450);
  gfx_color(241,113,92);
  gfx_fill_rectangle(700,100,3,450);

  // finish outline right around board

  gfx_color(234,84,92);
  gfx_fill_rectangle(94,94,612,3);
  gfx_color(241,113,92);
  gfx_fill_rectangle(94,97,612,3);
  gfx_color(241,113,92);
  gfx_fill_rectangle(94,553,612,3);
  gfx_color(234,84,92);
  gfx_fill_rectangle(94,550,612,3);

  // top

    
  gfx_color(223,178,175);
  gfx_fill_rectangle(0,20,6,82);
  gfx_color(237,135,128);
  gfx_fill_rectangle(6,20,6,82);
  gfx_color(241,113,92);
  gfx_fill_rectangle(12,20,6,82);
  gfx_color(234,84,92);
  gfx_fill_rectangle(18,20,6,82);
  gfx_color(250,11,11);
  gfx_fill_rectangle(24,20,70,82);

  gfx_color(223,178,175);
  gfx_fill_rectangle(0,0,6,20);
  gfx_color(237,135,128);
  gfx_fill_rectangle(6,5,6,15);
  gfx_color(241,113,92);
  gfx_fill_rectangle(12,10,6,10);
  gfx_color(234,84,92);
  gfx_fill_rectangle(18,15,6,5);

  gfx_color(250,11,11);
  gfx_fill_rectangle(94,20,612,74);

  gfx_color(223,178,175);
  gfx_fill_rectangle(794,20,6,82);
  gfx_color(237,135,128);
  gfx_fill_rectangle(788,20,6,82);
  gfx_color(241,113,92);
  gfx_fill_rectangle(782,20,6,82);
  gfx_color(234,84,92);
  gfx_fill_rectangle(776,20,6,82);
  gfx_color(250,11,11);
  gfx_fill_rectangle(706,20,70,82);

  gfx_color(223,178,175);
  gfx_fill_rectangle(794,0,6,20);
  gfx_color(237,135,128);
  gfx_fill_rectangle(788,5,6,15);
  gfx_color(241,113,92);
  gfx_fill_rectangle(782,10,6,10);
  gfx_color(234,84,92);
  gfx_fill_rectangle(776,15,6,5);

  gfx_color(223,178,175);
  gfx_fill_rectangle(6,0,794,5);
  gfx_color(237,135,128);
  gfx_fill_rectangle(12,5,782,5);
  gfx_color(241,113,92);
  gfx_fill_rectangle(18,10,770,5);
  gfx_color(234,84,92);
  gfx_fill_rectangle(24,15,758,5);

  // bottom

  gfx_color(223,178,175);
  gfx_fill_rectangle(0,550,6,150);
  gfx_color(237,135,128);
  gfx_fill_rectangle(6,550,6,145);
  gfx_color(241,113,92);
  gfx_fill_rectangle(12,550,6,140);
  gfx_color(234,84,92);
  gfx_fill_rectangle(18,550,6,135);
  gfx_color(250,11,11);
  gfx_fill_rectangle(24,550,70,130);

  gfx_color(223,178,175);
  gfx_fill_rectangle(794,550,6,150);
  gfx_color(237,135,128);
  gfx_fill_rectangle(788,550,6,145);
  gfx_color(241,113,92);
  gfx_fill_rectangle(782,550,6,140);
  gfx_color(234,84,92);
  gfx_fill_rectangle(776,550,6,135);
  gfx_color(250,11,11);
  gfx_fill_rectangle(706,550,70,130);

  gfx_color(250,11,11);
  gfx_fill_rectangle(94,556,612,124);

  gfx_color(223,178,175);
  gfx_fill_rectangle(0,695,794,5);
  gfx_color(237,135,128);
  gfx_fill_rectangle(6,690,782,5);
  gfx_color(241,113,92);
  gfx_fill_rectangle(12,685,770,5);
  gfx_color(234,84,92);
  gfx_fill_rectangle(18,680,758,5);


}


// function to initilze the board
void initBoard(Pixel arr[][pixelh], int ix, int iy)

{

  // cycle through the 2D struct array to initialze the filled and changed values, and the height and width for each pixel

  for (int i = 0; i < pixelw; i++) {
    for (int j = 0; j < pixelh; j++) {
      arr[i][j].isFilled = 0;
      arr[i][j].isChanged = 0;
      arr[i][j].w = 5;
      arr[i][j].h = 5;
    }
  }

  // intialize the first drawing point

  arr[ix][iy].isFilled = 1;
  arr[ix][iy].isChanged = 1;

}

// function to draw points

void drawBoard(Pixel arr[][pixelh])

{

  // initialize variables for height and width location of new drawn pixel

  int hsp;
  int wsp;

  // loop throught the struct array to find pixel that changed 
  
  for (int i = 0; i < pixelw; i++) {
    for (int j = 0; j < pixelh; j++) {

      // only color in one pixel each time the function is called for 
      // maximum efficiency, this is why isChanged is used.
      // Otherwise when many pixels are colored in it will take to long
      // to draw all of them becasue there are so many and the program
      // would lag

      if (arr[i][j].isFilled == 1 && arr[i][j].isChanged == 1) {

        // calculate height and width base on location of the pixel

        wsp = 100 + (i * 5);
        hsp = 100 + (j * 5);

        // color in pizel at the location
      
        gfx_color(0,0,0);
        gfx_fill_rectangle(wsp,hsp,arr[i][j].w,arr[i][j].h);

        // set is changed vale back to 0 so it will not be colored in again
    
        arr[i][j].isChanged = 0;
      }
    }
  }


}

// function to draw right

int drawRight(Pixel arr[][pixelh], int cx, int cy)

{

  // increment drawing position
  cx++;

  // set x to the max value if it reaches the right edge

  if (cx >= pixelw) cx = pixelw - 1;

  // set it properties so it will be colored in

  arr[cx][cy].isFilled = 1;
  arr[cx][cy].isChanged = 1;
  
  // return new x position

  return cx;


}

// function to draw left

int drawLeft(Pixel arr[][pixelh], int cx, int cy)

{

  // increment x position

  cx--;

  // if it reaches the left edge, set it to the minium value

  if (cx < 0) cx = 0;

  // set properties so it will be colored in

  arr[cx][cy].isFilled = 1;
  arr[cx][cy].isChanged = 1;
  
  // return new x position

  return cx;


}

// funtion to draw down

int drawDown(Pixel arr[][pixelh], int cx, int cy)

{

  // increment y position

  cy++;

  // if it reaches the bottom set y to max value

  if (cy >= pixelh) cy = pixelh - 1;

  // set properties to be colored in

  arr[cx][cy].isFilled = 1;
  arr[cx][cy].isChanged = 1;
  
  // return new y position

  return cy;

}

// function to draw up
int drawUp(Pixel arr[][pixelh], int cx, int cy)

{

  // increment y position

  cy--;

  // if it reaches the top set to minimum value

  if (cy < 0) cy = 0;

  // set properties to be colored in

  arr[cx][cy].isFilled = 1;
  arr[cx][cy].isChanged = 1;
  
  // return new y value

  return cy;

}

// function to draw the left dial

void drawLeftDial()

{
  
  // draw to circles to create depth 

  gfx_color(223,178,175);
  gfx_fill_circle(100,616,50);
  gfx_color(236,231,230);
  gfx_fill_circle(94,620.5,50);

  // initialize x and y

  double x,y;

  // calculate intial position for turn tracking circle

  x = 94 + (33 * cos(0));
  y = 620.5 + (33 * sin(0));

  // draw circle that will track motion at this position

  gfx_color(180,178,175);
  gfx_fill_circle(x,y,10);

}

// function to draw right dial

void drawRightDial()

{
  
  // draw two circles for depth

  gfx_color(223,178,175);
  gfx_fill_circle(706,616,50);
  gfx_color(236,231,230);
  gfx_fill_circle(700,620.5,50);

  // intialize x and y

  double x,y;

  // calculate initial position

  x = 700 + (33 * cos(M_PI));
  y = 620.5 + (33 * sin(M_PI));

  // draw circle that will track motion at this location

  gfx_color(180,178,175);
  gfx_fill_circle(x,y,10);



}

// function to rotate the left dial

double moveLeftDial(double rad, double radchange, int leftRight) 
{

  // print first circle to aat as a clear

  gfx_color(236,231,230);
  gfx_fill_circle(94,620.5,50); 

  // intialize  x and y

  double x,y;

  // caluclate position base on rad

  x = 94 + (33 * cos(rad));
  y = 620.5 + (33 * sin(rad));

  // subtract or add rad depending on if the drawing is going left or right

  if (leftRight == 1)
    rad -= radchange;
  else
    rad += radchange;

  // draw motion tracking circle

  gfx_color(180,178,175);
  gfx_fill_circle(x,y,10);

  // return new rad so the position will change when the function is called again
  return rad;


}

// function to move right dial

double moveRightDial(double rad, double radchange, int upDown) 
{

  // print first circle to act as a clear

  gfx_color(236,231,230);
  gfx_fill_circle(700,620.5,50);

  // intialize x and y

  double x,y;

  // calculate x and y psotion based on rad

  x = 700 + (33 * cos(rad));
  y = 620.5 + (33 * sin(rad));

  // add or subtract radchange based on if the motion is down or up

  if (upDown == 1)
    rad -= radchange;
  else
    rad += radchange;

  // print motion tracking circle at this postion 

  gfx_color(180,178,175);
  gfx_fill_circle(x,y,10);
 
  // return new rad to it will continue to move when the function is called again
  return rad;


}

// function to print etch a sketch name

void printName()

{

  // char pointer for font

  char *myfont = "-sony-fixed-medium-r-normal--24-170-100-100-c-120-jisx0201.1976-0";

  // char pointer for text

  char *name = "Etch A Sketch";

  // change font

  gfx_changefont(myfont);

  // draw with two different colors and add more to create the illusion of depth

  gfx_color(255,255,255);

  gfx_text(336,64,name);
  gfx_text(337,63,name);
  gfx_text(338,62,name);

  gfx_color(224,174,96);
  
  gfx_text(335,65,name);
  gfx_text(336,65,name);
  gfx_text(337,65,name);



}


