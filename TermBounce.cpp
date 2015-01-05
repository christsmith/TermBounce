// Author: Christopher Smith
// 17 Nov 2012

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;
//CHANGE THESE NUMBERS ------------------------------
const int width = 80;//width of the grid
const int hight = 50;//hight of the grid
const char EMPTY = ' ';//dont change this one actually (unless you really want to)
const int BALL_NUM = 10;//number of objects boucing
//------------------------------------------------  

struct Bouncer{
	char lable;
	int hAdd;
	int wAdd;
	int h;
	int w;
};

void fill(char b[hight][width]);
void drawBoard(char b[hight][width]);
Bouncer renderNextPlace(Bouncer b);
void addToBoard(const Bouncer &b, char (&board)[hight][width]);
void fillBouncer(Bouncer &b,char lable);
int randomInt(int nLow, int nHigh);
void setBouncer(Bouncer &b, char label, int h, int hAdd, int w, int wAdd);


int main(){

	char board[hight][width];
	Bouncer balls[BALL_NUM];
	srand ( time(NULL) );
	for(int i = 0; i < BALL_NUM; i++)
	{
		fillBouncer(balls[i], i+49);
	}
	
	for(int i = 0; i < 1000000; i++){
		fill(board);
		for(int j = 0; j < BALL_NUM; j++)
		{
			balls[j] = renderNextPlace(balls[j]);
			addToBoard(balls[j], board);
		}
		drawBoard(board);
		usleep(100000);
	}
	
	return 0;
}




void drawBoard(char b[hight][width]){
	for(int i = 0; i < hight; i++)
	{
		for(int j = 0; j < width; j++)
		{
			cout << b[i][j];
		}
		cout << endl;
	}
	
	
	cout << endl;
}

void fill(char b[hight][width]) 
{
	for(int i = 0; i < hight; i++)
	{
		for(int j = 0; j < width; j++)
		{
			b[i][j] = EMPTY;
			
		}
	}

}


Bouncer renderNextPlace(Bouncer b)
{
		if (b.h + b.hAdd > hight-1 || b.h + b.hAdd < 0)
		{
			b.hAdd*= -1;
		}
		if (b.w + b.wAdd > width-1 || b.w + b.wAdd < 0)
		{
			b.wAdd*= -1;
		}
		
		b.h+=b.hAdd;
		b.w+=b.wAdd;
		return b;
		
}

void addToBoard(const Bouncer &b, char (&board)[hight][width])
{
	board[b.h][b.w] = b.lable;
}


void fillBouncer(Bouncer &b, char lable)
{
	b.lable = lable;
	if (randomInt(0,1)){
		b.hAdd = 1;	
	} else {
		b.hAdd = -1;
	}
	if (randomInt(0,1)){
		b.wAdd = 1;	
	} else {
		b.wAdd = -1;
	}
	b.h = randomInt(0,hight);
	b.w = randomInt(0,width);
}

void setBouncer(Bouncer &b, char lable, int h, int hAdd, int w, int wAdd)
{
	b.lable = lable;
	b.h = h;
	b.hAdd = hAdd;
	b.w = w;
	b.wAdd = w;
}

int randomInt(int nLow, int nHigh)
{
	return rand() % (nHigh - nLow + 1) + nLow;
}
