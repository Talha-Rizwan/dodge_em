//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions s
#include<ctime>
#include<fstream> //for making the idea of highscores practical
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */


int x ; 		//coordinates of opponent car
int y ;

int c=350,d=770;		//coordinates of players car
 
bool pa=1;		//taking boolian for pause and displaying menu

bool help=0;

int g=210;		//coordinates for third car of level 4
int h=210;

int arr[810][810]={0};	//using array in global for points

int level =1;		
int score =0;		//declaration of level score and lives	
int life=3;


int tscore=0;		//total score of all levels,it will only make an increament when the level is ended

int display_score[10]={200, 180, 170, 160,120, 110, 70, 65,40,20}; //array of high score

int highscore=0;		//this variable will remain zero till high score is not displayed,when key 3 is pressed and game is paused then this variable will become 5 and highscore will be displayed




void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void HIGHSCORE(int user_score){			//function for highscore 
	int high_Scores[10] = { 270, 230, 210, 190,140, 110, 90, 80,55,20}; //scores array
	int tmp;
	//writing in file
	ofstream fout;
	fout.open ("high score.txt"); //the name of file in which we are writing
	if(user_score>high_Scores[9]){
		high_Scores[9]=user_score;//checking the user score if it is greater
	}			   	
	for(int k=0;k<10;k++){
		for(int g=k+1;g<10;g++){
			if(high_Scores[k]<high_Scores[g]){
				tmp=high_Scores[k];		//putting the score at appropriate position in array
				high_Scores[k]=high_Scores[g];
				high_Scores[g]=tmp;
			}
		}
	}
	for (int i = 0; i < 10; i++){
		fout << high_Scores[i] << endl;
	}
	cout<<endl;
	
	fout.close();
	
	//reading file
	string score;
	ifstream fin ("high score.txt"); //file to be read
	if (fin.is_open())
	{
		int k=0;
		while ( getline (fin, score) ) //this loop will run according to number of lines present in file
		{
		 	cout << score << '\n';
		  
		 	// using stoi() function to convert string into Integer
			display_score[k]=stoi(score);	
			k++;
		  
		}
		fin.close();
	}
	
	else 
		cout << "file cannot be accessed"; 
	}

/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	







if(highscore==0){			//will only display highscore if highscore variable is 5
if(help==0){			//will only display help if help==1
if(life>0){			//this condition will make it run till 3 lives
if(level<=4){			//this will allow it to run till 4 levels
if(pa==0){

	


	// Drawing opponent car	
	float width = 10; 
	float height = 7;
	float* color = colors[BLUE_VIOLET]; 
	float radius = 5.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect



//drawing squares at only the places where the value of array is 1
for(int i=0;i<810;i++)
{	for(int j=0;j<810;j++)	
	{
	if(arr[i][j]==1)
	{DrawSquare( i , j ,20,colors[GREEN]);}
	}
}


// displaying string at top for menu
DrawString( 300, 1000, "to pause and show menu press P", colors[MISTY_ROSE]);



//displaying lifes remaining
string l="life remaining = ";
string m=Num2Str(life);
string n=l+m;
DrawString( 50, 900, n, colors[MISTY_ROSE]);



//displaying string for score
string s="level score =";
string t;
t=Num2Str(score);
string u=s+t;
DrawString( 50, 1000, u, colors[MISTY_ROSE]);



//showing level at the top of game
string q="level =";
string r= Num2Str(level);
string v=q+r;
DrawString( 700, 1000, v, colors[MISTY_ROSE]);
	
	
	


	
	//drawing players car
	color = colors[YELLOW]; 
	
	DrawRoundRect(c,d,width,height,color,radius); // bottom left tyre
	DrawRoundRect(c+width*3,d,width,height,color,radius); // bottom right tyre
	DrawRoundRect(c+width*3,d+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(c,d+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(c, d+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(c+width, d+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(c+width*3, d+height*2, width, height, color, radius/2); // body right rect



//removing 1 and placing zero if the car's coordinates are maching with the location of array containing 1
if(arr[c][d]==1 || arr[c-20][d]==1 || arr[c+20][d]==1|| arr[c][d+20]==1 || arr[c][d-20]==1)
{
arr[c][d]=0;		
arr[c-20][d]=0;
arr[c+20][d]=0;
arr[c][d+20]=0;
arr[c][d-20]=0;	
score=score+1;}

if(score==64)
tscore=tscore+100+score;

string o="your total game score =";

string p=Num2Str(tscore);

string w=o+p;

DrawString( 500, 900, w, colors[MISTY_ROSE]);

//staring a new level
if(score==64)
{DrawString( 350, 350, "LEVEL ENDED", colors[MISTY_ROSE]);

level=level+1;
score=0;
for(int i=50;i<=790;i+=90)	
	{	if(i==410)
		continue;	
		for(int j=50;j<=790;j+=90)
		{if(j==410)
		continue;
		
		arr[i][j]=1;				
		}
	}
}



//movement of opponent car
if(x==30 && y<=770 && y>=30)
y=y+5;
if(x<=770 && x>=30 && y==30)
x=x-5;
if(x==770 && y>=30 && y<=770)
y=y-5;
if(y==770 && x>=30 && x<=770)
x=x+5;

if(x==770-90 && y>=30+90 && y<=770-90)
y=y-5;
if(y==770-90 && x>=30+90 && x<=770-90)
x=x+5;
if(x==30+90 && y<=770-90 && y>=30+90)
y=y+5;
if(y==30+90 && x>=30+90 && x<=770-90)
x=x-5;


if(x==770-90-90 && y>=30+90+90 && y<=770-90-90)
y=y-5;
if(y==770-90-90 && x>=30+90+90 && x<=770-90-90)
x=x+5;
if(x==30+90+90 && y<=770-90-90 && y>=30+90+90)
y=y+5;
if(y==30+90+90 && x>=30+90+90 && x<=770-90-90)
x=x-5;



if(x==770-90-90-90 && y>=30+90+90+90 && y<=770-90-90-90)
y=y-5;
if(y==770-90-90-90 && x>=30+90+90+90 && x<=770-90-90-90)
x=x+5;
if(x==30+90+90+90 && y<=770-90-90-90 && y>=30+90+90+90)
y=y+5;
if(y==30+90+90+90 && x>=30+90+90+90 && x<=770-90-90-90)
x=x-5;






//movement of players car
if(c==770 && d>=30 && d<=770)
d=d+5;
if(d==770 && c>=30 && c<=770)
c=c-5;
if(c==30 && d<=770 && d>=30)
d=d-5;
if(d==30 && c>=30 && c<=770)
c=c+5;


if(c==770-90 && d>=30+90 && d<=770-90)
d=d+5;
if(d==770-90 && c>=30+90 && c<=770-90)
c=c-5;
if(c==30+90 && d<=770-90 && d>=30+90)
d=d-5;
if(d==30+90 && c>=30+90 && c<=770-90)
c=c+5;


if(c==770-90-90 && d>=30+90+90 && d<=770-90-90)
d=d+5;
if(d==770-90-90 && c>=30+90+90 && c<=770-90-90)
c=c-5;
if(c==30+90+90 && d<=770-90-90 && d>=30+90+90)
d=d-5;
if(d==30+90+90 && c>=30+90+90 && c<=770-90-90)
c=c+5;



if(c==770-90-90-90 && d>=30+90+90+90 && d<=770-90-90-90)
d=d+5;
if(d==770-90-90-90 && c>=30+90+90+90 && c<=770-90-90-90)
c=c-5;
if(c==30+90+90+90 && d<=770-90-90-90 && d>=30+90+90+90)
d=d-5;
if(d==30+90+90+90 && c>=30+90+90+90 && c<=770-90-90-90)
c=c+5;





//artificial intelligence of opponent car
if(x<455 && x>355 && y<300 && d>y)
{y=y+90;
x=x-100;}	


if(x<455 && x>355 && y>500 && d<y)
{y=y-90;
x=x+100;}


if(x<455 && x>355 && y>=410 && d>y)
{y=y+90;
x=x+100;}


if(x<455 && x>355 && y<=300  && y>30 && d<y)
{y=y-90;
x=x-100;
}


//for level 2 and above 
if(level>1)
{
if(x<300 && y>355 && y<355 && c>x)
{x=x+90;
y=y+100;}

if(x<=300 && y>355 && y<455 && x>30 && c<x)
{x=x-90;
y=y+100;}

if(x>500 && y>355 && y<455 && c<x)
{x=x-90;
y=y-100;}

if(x>=500 && x<770 && y<455 && y>355 && c>x)
{x=x+90;
y=y-100;}
}



//for level three and above increasing speed of opponent car to double
if(level>2)
{
if(x==30 && y<=770 && y>=30)
y=y+5;
if(x<=770 && x>=30 && y==30)
x=x-5;
if(x==770 && y>=30 && y<=770)
y=y-5;
if(y==770 && x>=30 && x<=770)
x=x+5;

if(x==770-90 && y>=30+90 && y<=770-90)
y=y-5;
if(y==770-90 && x>=30+90 && x<=770-90)
x=x+5;
if(x==30+90 && y<=770-90 && y>=30+90)
y=y+5;
if(y==30+90 && x>=30+90 && x<=770-90)
x=x-5;


if(x==770-90-90 && y>=30+90+90 && y<=770-90-90)
y=y-5;
if(y==770-90-90 && x>=30+90+90 && x<=770-90-90)
x=x+5;
if(x==30+90+90 && y<=770-90-90 && y>=30+90+90)
y=y+5;
if(y==30+90+90 && x>=30+90+90 && x<=770-90-90)
x=x-5;



if(x==770-90-90-90 && y>=30+90+90+90 && y<=770-90-90-90)
y=y-5;
if(y==770-90-90-90 && x>=30+90+90+90 && x<=770-90-90-90)
x=x+5;
if(x==30+90+90+90 && y<=770-90-90-90 && y>=30+90+90+90)
y=y+5;
if(y==30+90+90+90 && x>=30+90+90+90 && x<=770-90-90-90)
x=x-5;

}



//for level four
if(level>3)

{//making of third car
	float width = 10; 
	float height = 7;
	float* color = colors[BLUE_VIOLET]; 
	float radius = 5.0;
	DrawRoundRect(g,h,width,height,color,radius); // bottom left tyre
	DrawRoundRect(g+width*3,h,width,height,color,radius); // bottom right tyre
	DrawRoundRect(g+width*3,h+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(g,h+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(g, h+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(g+width, h+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(g+width*3, h+height*2, width, height, color, radius/2); // body right rect

//movement of third car
if(g==30 && h<=770 && h>=30)
h=h+10;
if(g<=770 && g>=30 && h==30)
g=g-10;
if(g==770 && h>=30 && h<=770)
h=h-10;
if(h==770 && g>=30 && g<=770)
g=g+10;

if(g==770-90 && h>=30+90 && h<=770-90)
h=h-10;
if(h==770-90 && g>=30+90 && g<=770-90)
g=g+10;
if(g==30+90 && h<=770-90 && h>=30+90)
h=h+10;
if(h==30+90 && g>=30+90 && g<=770-90)
g=g-10;


if(g==770-90-90 && h>=30+90+90 && h<=770-90-90)
h=h-10;
if(h==770-90-90 && g>=30+90+90 && g<=770-90-90)
g=g+10;
if(g==30+90+90 && h<=770-90-90 && h>=30+90+90)
h=h+10;
if(h==30+90+90 && g>=30+90+90 && g<=770-90-90)
g=g-10;



if(g==770-90-90-90 && h>=30+90+90+90 && h<=770-90-90-90)
h=h-10;
if(h==770-90-90-90 && g>=30+90+90+90 && g<=770-90-90-90)
g=g+10;
if(g==30+90+90+90 && h<=770-90-90-90 && h>=30+90+90+90)
h=h+10;
if(h==30+90+90+90 && g>=30+90+90+90 && g<=770-90-90-90)
g=g-10;

//auto chasing of third car

if(g<455 && g>355 && h<300 && d>h)
{h=h+90;
g=g-100;}	


if(g<455 && g>355 && h>500 && d<h)
{h=h-90;
g=g+100;}


if(g<455 && g>355 && h>=410 && d>h)
{h=h+90;
g=g+100;}


if(g<455 && g>355 && h<=300  && h>30 && d<h)
{h=h-90;
g=g-100;
}

//applying conditions if the player and opponent second car matches location
if((g==c || g==c+5 || g==c-5) && (h==d || h==d-5 || h==d+5))
{c=770;d=30;score=0;
for(int i=50;i<=790;i+=90)	
	{	if(i==410)
		continue;	
		for(int j=50;j<=790;j+=90)
		{if(j==410)
		continue;
		
		arr[i][j]=1;				
		}
	}
life--;}


}


//applying conditions if the player and opponent first car matches location
if((x==c || x==c+5 || x==c-5) && (y==d || y==d-5 || y==d+5))
{c=350;d=770;score=0;
for(int i=0;i>-1;i++)
{x=rand()%740+30;
y=rand()%740+30;

if((x==210 && y==210 ) || (x==120 && y==120)|| (x==590 && y==590 ) || (x==680 && y==680 )  || (x==500 && y==500 ) ) 
break;


}

for(int i=50;i<=790;i+=90)	
	{	if(i==410)
		continue;	
		for(int j=50;j<=790;j+=90)
		{if(j==410)
		continue;
		
		arr[i][j]=1;				
		}
	}
life--;}





	// Drawing Arena
	int gap_turn = 100;
	int sx = 20;
	int sy = 10;
	int swidth = 800/2 - gap_turn/2; // half width
	int sheight = 10;
	float *scolor = colors[BROWN];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+810, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+810, swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down
	
	int a=90; //making arena with same distances between each route
	for(int i=0;i<3;i++)
	{
	DrawRectangle(sx+a, sy+a, swidth-a, sheight, scolor); // bottom left
	DrawRectangle(sx+a + swidth-a + gap_turn, sy+a, swidth-a, sheight, scolor); // bottom right
	DrawRectangle(sx-a+swidth*2+gap_turn, sy+a+sheight, sheight*2, swidth-a, scolor); // right down
	DrawRectangle(sx-a+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth-a, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+810-a, swidth-a, sheight, scolor); // top right
	DrawRectangle(sx+a, sy+810-a, swidth-a, sheight, scolor); // top left
	DrawRectangle(sx+a-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth-a, scolor); // left up
	DrawRectangle(sx+a-sheight*2, sy+a+sheight, sheight*2, swidth-a, scolor); // left down
	a=a+90;}


	//drawing central box of arena	
	DrawLine( 350 , 370 ,  490 , 370 , 10 , colors[MISTY_ROSE] );
	DrawLine( 350 , 370 ,  350 , 470 , 10 , colors[MISTY_ROSE] );
	DrawLine( 490 , 470 ,  350 , 470 , 10 , colors[MISTY_ROSE] );
	DrawLine( 490 , 470 ,  490 , 370 , 10 , colors[MISTY_ROSE] );







}//displaying menu when the game is paused
if(pa==1)
{DrawString( 50, 1000, "                      PAUSED (MAIN MENU) ", colors[MISTY_ROSE]);

DrawString( 50, 850, " 1) press C to continue", colors[MISTY_ROSE]);

DrawString( 50, 700, "2) press R to start a new game", colors[MISTY_ROSE]);

DrawString( 50, 550, "3) press h for help", colors[MISTY_ROSE]);

DrawString( 50, 400, "4) press 3 for high scores", colors[MISTY_ROSE]);

DrawString( 50, 250, "5) press escape to exit", colors[MISTY_ROSE]);

}
}
if(level==5)//if the player wons
{	DrawString( 50, 250, "game ended                       you won!", colors[MISTY_ROSE]);
	DrawString( 50, 800, "press R to restart the game", colors[MISTY_ROSE]);
	pa=1;
}
}

if(life==0)//if all the lives end
{
DrawString( 50, 250, "GAME OVER", colors[MISTY_ROSE]);
DrawString( 50, 100, "YOU LOSE !", colors[MISTY_ROSE]);
DrawString( 50, 800, "press R to restart the game", colors[MISTY_ROSE]);
pa=1;

}
}
if(help==1)//displaying help and instructions for the game when key 'h' is pressed when game is paused 
{DrawString( 50, 1000, "these are some instructions for playing the game :", colors[MISTY_ROSE]);
DrawString( 100, 900, "instructions to move your yellow coloured car", colors[MISTY_ROSE]);
DrawString( 150, 750, "use up arrow key to move up between the gap", colors[MISTY_ROSE]);
DrawString( 150, 650, "use down arrow key to move down between the gap", colors[MISTY_ROSE]);
DrawString( 150, 550, "use right arrow key to move right between the gap", colors[MISTY_ROSE]);
DrawString( 150, 450, "use left arrow key to move left between the gap", colors[MISTY_ROSE]);
DrawString( 100, 300, "the game is divided in four levels", colors[MISTY_ROSE]);
DrawString( 100, 200, "you are awarded three lives and you lose each life during collision", colors[MISTY_ROSE]);
DrawString( 100, 100, "play long and make high scores", colors[MISTY_ROSE]);
DrawString( 600, 70, "GOOD LUCK !", colors[MISTY_ROSE]);
DrawString( 100, 40, "press backspace key to go back to main menu", colors[MISTY_ROSE]);
}
}

if(highscore==5) 				//displaying highscores when game is paused by pressing the key '3'
{DrawString( 200, 700, "HIGHSCORES", colors[MISTY_ROSE]);
DrawString( 100, 100, "press backspace key to go back to main menu", colors[MISTY_ROSE]);
	string s;int axis=600;
		for(int i=0;i<10;i++){
			s=Num2Str(display_score[i]);
			DrawString( 300, axis,s , colors[MISTY_ROSE]);
			axis-=50;
		}
}






	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {	//giving functions to arrow keys for car to change roads
	if (key
			== GLUT_KEY_LEFT && d<455 && d>355 && c!=30 && c!=500 /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		c=c-90;// what to do when left key is pressed...
	
	} else if (key
			== GLUT_KEY_RIGHT && d<455 && d>355 && c!=770 && c!=300/*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	c=c+90;
	} else if (key
			== GLUT_KEY_UP  && c<455 && c>355 && d!=770 && d!=300/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	d=d+90;
	}

	else if (key
			== GLUT_KEY_DOWN && c<455 && c>355 && d!=30 && d!=500/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	d=d-90;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {//giving functions to other keys except arrow keys whose ascii are known
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}


	if(key==32)
	{
	if(c==770 && d>=30 && d<=770)
	d=d+5;
	if(d==770 && c>=30 && c<=770)
	c=c-5;
	if(c==30 && d<=770 && d>=30)
	d=d-5;
	if(d==30 && c>=30 && c<=770)
	c=c+5;


	if(c==770-90 && d>=30+90 && d<=770-90)
	d=d+5;
	if(d==770-90 && c>=30+90 && c<=770-90)
	c=c-5;
	if(c==30+90 && d<=770-90 && d>=30+90)
	d=d-5;
	if(d==30+90 && c>=30+90 && c<=770-90)
	c=c+5;


	if(c==770-90-90 && d>=30+90+90 && d<=770-90-90)
	d=d+5;
	if(d==770-90-90 && c>=30+90+90 && c<=770-90-90)
	c=c-5;
	if(c==30+90+90 && d<=770-90-90 && d>=30+90+90)
	d=d-5;
	if(d==30+90+90 && c>=30+90+90 && c<=770-90-90)
	c=c+5;
	
	
	
	if(c==770-90-90-90 && d>=30+90+90+90 && d<=770-90-90-90)
	d=d+5;
	if(d==770-90-90-90 && c>=30+90+90+90 && c<=770-90-90-90)
	c=c-5;
	if(c==30+90+90+90 && d<=770-90-90-90 && d>=30+90+90+90)
	d=d-5;
	if(d==30+90+90+90 && c>=30+90+90+90 && c<=770-90-90-90)
	c=c+5;
	}
	
	if(key=='3' && pa==1)		// display highscore only when 3 is pressed in the paused menu and highscore variable will be given value 5 
		highscore=5;
	
	if(key=='p' || key=='P') 	
	pa=1;
	if(key=='c' || key=='C')		//condition to continue when game is paused
	pa=0;
	if((key=='r' || key=='R') && pa==1)	//putting conditions to restart the game
	{pa=0;
	c=350;d=770;score=0;level=1;life=3;
	for(int i=0;i>-1;i++)
	{x=rand()%740+30;
	y=rand()%740+30;

	if((x==210 && y==210 ) || (x==120 && y==120)|| (x==590 && y==590 ) || (x==680 && y==680 )  || (x==500 && y==500 ) ) 
	break;


	}


	for(int i=50;i<=790;i+=90)	//making he points again
	{	if(i==410)
		continue;	
		for(int j=50;j<=790;j+=90)
		{if(j==410)
		continue;
		
		arr[i][j]=1;				
		}
	
	}
}
if(pa==1){
if(key=='h' || key=='H')	//for displaying help
{help=1;

}

if(key==8)		//for going back to main menu when displaying help
help=0;


}

if(pa==1)		//for going back to main menu when displaying highscore
{if(key==8)
highscore=0;}






glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1.0, Timer, 0);
	
	
	//calling display function after every 1 milli second
	GameDisplay();


}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...


srand(time(0));		//for initializing the opponent car from random positions
for(int i=0;i>-1;i++)
{x=rand()%740+30;
y=rand()%740+30;

if((x==210 && y==210 ) || (x==120 && y==120)|| (x==590 && y==590 ) || (x==680 && y==680 )  || (x==500 && y==500 ) ) 
{break;
 if(life==0)
pa=1;
}
}

/*if((y<590 && y>410 && y%5==0) || (y>210 && y<300 && y%5==0))
{
if(x==210  || x==300 || x==590 || x==500)                            not working even after many tries
break;
}
if((x<590 && x>410 && x%5==0) || (x>210  && x<300 && x%5==0))
{
if(y==210 || y==300 || y==500 || y==590)
break;
}*/







for(int i=50;i<=790;i+=90)	//initialising the array first time for points
	{	if(i==410)
		continue;	
		for(int j=50;j<=790;j+=90)
		{if(j==410)
		continue;
		
		arr[i][j]=1;				
		}
	}
	int width = 840, height = 1040; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Dodge_em"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
