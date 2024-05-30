#include "libdron.h"
extern int gameOver;

struct snake_t Setup(int x, int y, size_t tsize)
{
	snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for(int i =0; i < snake.tsize; i++)
	{
		snake.tail[i].x = x;
		snake.tail[i].y = y + i + 1;
	}
	return snake;
}

void initFrut(frut frut[], int size)
{
	for (int i = 0;i<size;i++)
	{
		frut[i].x = rand() % (WIDTH-1);
		frut[i].y = rand() % (HEIGHT-1);
		frut[i].enable = 1;
	}
}

void refreshFrut(frut frut[], int size)
{
	int count = 0;
	for(int i = 0; i < size; i++)
	{
		if(frut[i].enable == 0) count++;
	}
	if (count == size) initFrut(frut,size);
	else return;
}

void printExit(int *levelSnake1, int *levelSnake2)
{
	if(*levelSnake1 == *levelSnake2) printf("\t\t ---Game draw---\n");
	else if (*levelSnake1 > *levelSnake2) printf("\t\t ---The GREEN drone won with the result: %d---\n",*levelSnake1);
	else printf("\t\t ---The BLUE drone won with the result: %d---\n",*levelSnake2);
	
	printf("\t\t\t\t GAME OVER!");
}

void isCrush(snake_t *snake)
{
	for(int i = 1; i < snake->tsize; i++)
	{
		if(snake->tail[i].x == snake->x && snake->tail[i].y == snake->y)
		gameOver = 0;
	}
}
// 

void startMenu(int *sel)
{
	int menu = 1;
	while (menu)
	{
		printf(" ######                                 #     #      #####  \n");
		printf(" #     # #####   ####  #    #           #     #     #     # \n");
		printf(" #     # #    # #    # #   ##           #     #           # \n");
		printf(" #     # #####  #    # #  # #  #####    #     #      #####  \n");
		printf(" #     # #  #   #    # # #  #  #####     #   #  ###       # \n");
		printf(" #     # #   #  #    # ##   #             # #   ### #     # \n");
		printf(" ######  #    #  ####  #    #              #    ###  #####  \n");
		printf("************************************************************\n");
		printf("*			Select menu:			   *\n");
		printf("*			1.Player game.			   *\n");
		printf("*			2.Auto game.			   *\n");
		printf("************************************************************\n");
		switch(getch())
		{
			case '1':
			menu = 0;
			*sel = 1;
			break;
			case '2':
			menu = 0;
			*sel = 2;
			break;
			default:
			system("cls");
			break;
		}
		
	}
}

void Input(direction *dir) 
{
	if(kbhit()) {
		switch(getch()) {
			case 'w':
			case 'W':
				*dir = UP;
				break;
			case 's':
			case 'S':
				*dir = DOWN;
				break;
			case 'a':
			case 'A':
				*dir = LEFT;
				break;
			case 'd':
			case 'D':
				*dir = RIGHT;
				break;
		}
	}
}


void Logic(snake_t *snake,frut frut[], direction dir, int *level) {
		int prevX = snake->tail[0].x;
		int prevY = snake->tail[0].y;
		int prev2X, prev2Y;
		snake->tail[0].x = snake->x;
		snake->tail[0].y = snake->y;
		
		
		for (int i = 1; i < snake->tsize; i++) {
			
			prev2X = snake->tail[i].x;
			prev2Y = snake->tail[i].y;
			snake->tail[i].x = prevX;
			snake->tail[i].y = prevY;
			prevX = prev2X;
			prevY = prev2Y;
			
		}
		
		switch(dir)
		{
			case LEFT:
				snake->y--;
				break;
			case RIGHT:
				snake->y++;
				break;
			case UP:
				snake->x--;
				break;
			case DOWN:
				snake->x++;
				break;
		}
		if (snake->x >= WIDTH)
			snake->x = 0;
		else if (snake->x < 0)
			snake->x = WIDTH - 1;
		
		if (snake->y >= HEIGHT)
			snake->y = 0;
		else if (snake->y < 0)
			snake->y = HEIGHT - 1;
			
		for(int i =0;i<MAX_FRUT_SIZE;i++)
		{
			if (snake->x == frut[i].x && snake->y == frut[i].y && frut[i].enable == 1) 
			{
			snake->tsize++;
			frut[i].enable = 0;
			*level+=1;
			
			}
		}
}

void Drow(snake_t *snake,snake_t *snake2, frut frut[], direction dir, direction dir2, int *levelSnake1,int *levelSnake2)
{
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	for(int i = 0;i < WIDTH + 1;i++)    // Верхняя граница
	{
		SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
		printf("#");
	}
	printf("\n");
	
	for(int i = 0;i < WIDTH; i++)
	{
		for(int j = 0;j < HEIGHT; j++)
		{
			if(j == 0) printf("|");    //Левая граница
			size_t flag_f = 0;
			for(int k = 0; k < MAX_FRUT_SIZE; k++)
			{
				if (i == frut[k].x && j == frut[k].y && frut[k].enable == 1)
				{
					SetConsoleTextAttribute(hwnd, FOREGROUND_RED);
					printf("O");  // фрукт
					flag_f = 1;
				}
			}
			if (snake->x == i && snake->y == j)
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN);
				 printf("@");  // Башка1
			}
			else if (snake2->x == i && snake2->y == j) 
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
				printf("#");  // Башка2
			}
			else
			{
				size_t flag_t = 0;
				for (int k = 0; k < snake->tsize-1; k++)
				{
					if (snake->tail[k].x == i && snake->tail[k].y == j)
					{
						SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN);
						printf("*");
						flag_t = 1;
					}
				}
				for (int k = 0; k < snake2->tsize-1; k++)
				{
					if (snake2->tail[k].x == i && snake2->tail[k].y == j)
					{
						SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
						printf("-");
						flag_t = 1;
					}
				}
				
			if(!flag_t && !flag_f) printf(" ");          //Все не занятое поле
			} 
			
			if(j == WIDTH-1) 
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
				printf("|");
			}
		}
		printf("\n");
	}
	
	for(int i = 0;i < WIDTH + 1;i++)    // Нижняя граница
		printf("#");
	printf("\n");
	SetConsoleTextAttribute(hwnd, FOREGROUND_RED);
	printf("Eat fruit GREEN snake:%d",*levelSnake1);
	printf("\n");
	printf("Eat fruit BLUE  snake:%d",*levelSnake2);
	printf("\n");
}


	void generateSnakeDirection(snake_t *snake2, direction *dir2, frut frut[])
	{
	for (int i = 0;i < MAX_FRUT_SIZE;i++)
	{
	if ((*dir2 == LEFT || *dir2 == RIGHT) && snake2->x == frut[i].x && frut[i].enable == 1)
	{
	return;
	}
	if ((*dir2 == LEFT || *dir2 == RIGHT) && snake2->x != frut[i].x && frut[i].enable == 1)
		{
			if (frut[i].y == snake2->y && frut[i].enable == 1)
			{
				if (abs(frut[i].x - snake2->x) < WIDTH) *dir2 = UP;
				else *dir2 = DOWN;
			return;
			}
		}
	if ((*dir2 == UP || *dir2 == DOWN) && snake2->y == frut[i].y && frut[i].enable == 1)
	{
	return;
	}
		if ((*dir2 == UP || *dir2 == DOWN)&& snake2->y != frut[i].y && frut[i].enable == 1)
		{
			if (frut[i].x == snake2->x && frut[i].enable == 1)
			{
				if (abs(frut[i].y - snake2->y) < HEIGHT) *dir2 = LEFT;
				else *dir2 = RIGHT;
			return;
			}
		}
	}
}
