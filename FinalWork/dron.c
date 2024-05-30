#include "libdron.h"
int gameOver;


int main(int argc, char **argv)
{
	int sel;
	direction dir = LEFT;
	direction dir2 = LEFT;
	int levelSnake1 = 0;
	int levelSnake2 = 0;
	gameOver = 1;
	snake_t snake = Setup(WIDTH/2,HEIGHT/2,1);
	snake_t snake2 = Setup(WIDTH - 5,HEIGHT/2,1);
	frut frut[MAX_FRUT_SIZE];
	
	initFrut(frut,MAX_FRUT_SIZE);
	
	startMenu(&sel);
	switch(sel)
	{
		case 1:
		while(gameOver)
		{
			Drow(&snake, &snake2, frut, dir, dir2,&levelSnake1,&levelSnake2);
			Input(&dir);
			generateSnakeDirection(&snake2, &dir2, frut);
			Logic(&snake,frut,dir,&levelSnake1);
			Logic(&snake2,frut,dir2,&levelSnake2);
			isCrush(&snake);
			isCrush(&snake2);
			refreshFrut(frut,MAX_FRUT_SIZE);
			snake.tsize > snake2.tsize ? Sleep(1000/snake.tsize):Sleep(1000/snake2.tsize);    //Скорость в отдельную функцию
		}
		break;
		
		case 2:
		while(gameOver)
		{
			Drow(&snake, &snake2, frut, dir, dir2,&levelSnake1,&levelSnake2);
			generateSnakeDirection(&snake2, &dir2, frut);
			generateSnakeDirection(&snake, &dir, frut);
			Logic(&snake,frut,dir,&levelSnake1);
			isCrush(&snake);
			Logic(&snake2,frut,dir2,&levelSnake2);
			isCrush(&snake2);
			snake.tsize > snake2.tsize ? Sleep(1000/snake.tsize):Sleep(1000/snake2.tsize);    //Скорость в отдельную функцию
			refreshFrut(frut,MAX_FRUT_SIZE);
		}
		break;
	}
	system("cls");
	printExit(&levelSnake1, &levelSnake2);
	return 0;
}

