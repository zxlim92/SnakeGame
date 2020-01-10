#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;
char user[0];
bool gameOver;
const int width = 20;
const int height = 20;
int bodyX[100], bodyY[100];
int x, y, XcorFruit, YcorFruit, point;
int body;
int difficulty;
int bestScore;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup(){
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	XcorFruit = rand() % width; // modular arithmic can only be between 0-(width-1)
	YcorFruit = rand() % height;
	point = 0;
}
void Draw(){
	system("cls"); //clear terminal
	cout << "HIGHSCORE: " << bestScore << endl;
	for (int i = 0; i < width+2; i++){
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (j == 0){
				cout << "|";
			}
			if (i == y && j == x){
				cout << char(toupper(user[0]));
			}else if (i == YcorFruit && j == XcorFruit){
				cout << "F";
			}else{
				bool print = 0;
				for (int k = 0; k < body; k++){
					if (bodyX[k] == j && bodyY[k] == i){ //extend body after eating fruit
						cout << user[0];
						print = 1;
					}
				}
				if (print == 0){
					cout << " ";
				}
			}
				

			if (j == width - 1){
				cout << "|";
			}
		}
		
		cout << endl;
		
	}

	for (int i = 0; i < width+2; i++){
		cout << "-";
	}
	cout << endl;
	cout << "Score: " << point << endl;
}
void Input()
{
	if (_kbhit()==1){ // check if keyboard key is pressed
		switch (_getch()){ //reads input
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
		}
	}
}
void Logic()
{
	int placeHolderX = bodyX[0];
	int placeHolderY = bodyY[0];
	int secondHolderX, secondHolderY;
	bodyX[0] = x;
	bodyY[0] = y;
	for (int i = 1; i < body; i++){ //for loop to account for body moving
		secondHolderX = bodyX[i];
		secondHolderY = bodyY[i];
		bodyX[i] = placeHolderX;
		bodyY[i] = placeHolderY;
		placeHolderX = secondHolderX;
		placeHolderY = secondHolderY;
	}
	switch (dir){ //coordinate system (0,0) top left. going down is +y and right is +x
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	
	default:
		break;
	}
	if(difficulty ==2){
		if (x > width || x < 0 || y > height || y < 0) //cannot exit map
		gameOver = true;
	}else{
		if (x >= width){ //when reach boundary appear from other side
			x = 0;
			} else if (x < 0){
				 x = width - 1;
			}
		if (y >= height){
			 y = 0; 
		}else if (y < 0){
			y = height - 1;
		}
	}
	for (int i = 0; i < body; i++) //hit own body it dies
		if (bodyX[i] == x && bodyY[i] == y)
			gameOver = true;

	if (x == XcorFruit && y == YcorFruit){
		point += 1;
		body++;
		XcorFruit = rand() % width;
		YcorFruit = rand() % height;
	}

}
int main(){
	Setup();
	int holder;
	int playAgain =1;
	int answer;
	int speed;
	char pace[0];
	ifstream input("bestScore.txt");
	input >> bestScore;
	cout<<"-----------------------"<<endl;
	cout<<"----------SNAKES-------"<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"Current high score:  " << bestScore<<endl;
	gameOver = 0;
	point= 0;
	cout<<endl;
	cout<<"Please TURN OFF ur capslock as this program will not work"<<endl;
	cout<<endl;	
	cout<<"what diffuclty? Easy(1) or Hard(2)"<<endl;
	cout<<"Easy = able to go through walls, Hard = gameover when touch a wall"<<endl;
	cin>>difficulty;
	cout<<"Chose a character (press a single key on ur keyboard)";
	cin>>user[0];
	cout<<"How fast would u like that game? Slow(1) Medium(2) Fast(3)"<<endl;
	cin >> pace[0];
	
	
	
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		switch(pace[0]){
			case '1':
				Sleep(100);
			case '2':
				Sleep(50);
			case '3':
				Sleep(10);
	}
	}
	cout<<point<<endl;
	ofstream output("bestScore.txt");
	if (point > bestScore){
		cout<<"NEW HIGHSCORE !!!WELL DONE"<<endl;
		cout<<"highscore updated"<<endl;
		output<<point;
	}else{
		output<<bestScore;
	}
	cout<<"Press a key and enter to quit"<<endl;
	cin>>holder;
}