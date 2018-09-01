# include "iGraphics.h"

/*
	function iDraw() is called again and again by the system.
*/
int starter = 1;
int ladderx=550,ladderSpeed = 50; // ladder x things
double ballx[3],bally[3]={1100,1600,2100},ballSpeed = 1,ballMax=-1;
int score=0,t=6000,life=10;
char showScore[1000],showTime[1000],showScore2[1000],LIFE[1000];
int redballx=0,redbally = 900;
int red = 0;
int pauseCounter = 0;

void init(){
	starter = 1;
	ladderx=550,ladderSpeed = 50;
	ballSpeed = 1,ballMax=-1;
	ballx[0] = (200+rand() %900);
	ballx[1] = (200+rand() %900);
	ballx[2] = (200+rand() %900);
	bally[0] = 1100;
	bally[1] = 1600;
	bally[2] = 2100;
	redballx=0,redbally = 900;
	red = 0;
	score=0,t=6000,life=10;
	pauseCounter = 0;
}

void iDraw()
{
	//place your drawing codes here
	iClear();
	iSetColor(29,29,29); // background color black
	iFilledRectangle(0,0,1300, 700);//setting background;
	if(starter==0){
		iSetColor(255,255,255);
		sprintf(showScore2,"%d",score);
		iText(400,600,"YOUR SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400,500,showScore2,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400,200,"CLICK TO PLAY AGAIN");
	}
	else if(starter == 5){
		init();
		starter = 2;
		iResumeTimer(0);
	}
	else if(starter==2){
		iSetColor(135,206,250);
		iFilledRectangle(170,0,1300-340,700);
		iSetColor(255,255,255); // white color for ladder
		iFilledRectangle(ladderx,125,200,30); // the ladder
		iSetColor(255,255,0); // yellow color text
		sprintf(showScore,"SCORE : %d",score);
		sprintf(showTime,"TIME  : %0.2lfs",t/100.0);
		sprintf(LIFE,"LIFE  : %d",life);
		iText(50,650,showScore); // Show score
		iText(50,600,LIFE); // Show score
		iText(1140,650,showTime); // Show gameplayime
		iSetColor(173,255,47); // ball colors
		for(int i=0;i<3;i++)iFilledCircle(ballx[i],bally[i],30); // draw ball
		if(red==1){
			iSetColor(255,0,0);
			iFilledCircle(redballx,redbally,30);
		}
	}
	else if(starter==1){
		iSetColor(255,255,255); //white button color
		iShowBMP(650-236,350-118,"name.bmp");
		iText(580,70,"CLICK TO PLAY");
		iText(100,70,"Avoid red balls");
		iText(900,70,"Collect balls before time");
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//if(starter==0)starter=1;
		if(starter==1)starter=2;
		else if(starter==0)starter=5;
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'a')
	{
		//
	}if(key == 'd')
	{
		//
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_LEFT)
	{
		ladderx-=ladderSpeed;
		if(ladderx<200)ladderx=200;
	}if(key == GLUT_KEY_RIGHT)
	{
		ladderx+=ladderSpeed;
		if(ladderx>1300-400)ladderx=1300-400;
	}
	//place your codes for other keys here
}
void change(){
	if(starter==2){
		if(pauseCounter==0){
			if(red == 0){
				int k = rand()%241 + 1;
				if(k==241)red=1;
				redballx = (200+rand() %900);
			}
			if(red==1){
				redbally-=ballSpeed;
				if(redbally<=-30)redbally=900,red=0;
				if(redbally<=125+60&& redbally-30>=125 && redballx>=ladderx-30 && redballx<=230+ladderx)life=0;
			}
			if(t--<=0||life==0)pauseCounter=1,ladderSpeed=0/*,starter=0*/;
			ballSpeed += 0.01;
			for(int i=0;i<3;i++){
				if(ballMax<bally[i])ballMax=bally[i];
				bally[i]-=ballSpeed;
				if(bally[i]<=125+60&&bally[i]-30>=125&&ballx[i]>=ladderx-30&&ballx[i]<=230+ladderx)bally[i]=ballMax+300,ballx[i]=(200+rand() %900),score++,ladderSpeed+=5;	
				if(bally[i]<=-30)bally[i]=ballMax+300+125+60,ballx[i]=(200+rand() %900),ladderSpeed-=5,life--;
			}
		}
		else pauseCounter++;
		if(pauseCounter==100)starter = 0;
	}
}

int main()
{
	//place your own initialization codes here.
	ballx[0] = (200+rand() %900);
	ballx[1] = (200+rand() %900);
	ballx[2] = (200+rand() %900);
	iSetTimer(1,change); 
	iInitialize(1300, 700, "COLLECTING BALLS");
	return 0;
}
