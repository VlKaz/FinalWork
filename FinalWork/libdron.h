#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>


#define WIDTH 20
#define HEIGHT 20
#define MAX_FRUT_SIZE 20


typedef struct tail_t{
	int x;
	int y;
	} tail_t;
	
typedef struct snake_t{
	int x;
	int y;
	tail_t * tail;
	size_t tsize;
	}snake_t;
	
typedef struct frut{
	int x;
	int y;
	int enable; // флаг еды 0 съели,  1 - нет
}frut;
	
typedef enum {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT,
	} direction;
	
void startMenu(int *sel); // Стартовое меню
struct snake_t Setup(int x, int y, size_t tsize); // Начальная загрузка Дрона
void initFrut(frut frut[], int size); // Рандомная установка Тыкв
void refreshFrut(frut frut[], int size); //Проверка и переустановка тыкв
void printExit(int *levelSnake1, int *levelSnake2); //Финальный результат
void isCrush(snake_t *snake); // Проверка на столкновение с вагонами
void Input(direction *dir); // Ручное управление
void Logic(snake_t *snake,frut frut[], direction dir, int *level); // Общая логика движени дрона + сбор тыкв + подсчет уровней + определения поля сбора
void Drow(snake_t *snake,snake_t *snake2, frut frut[], direction dir, direction dir2, int *levelSnake1,int *levelSnake2); //Отрисовка дронов + поля + собраные тыквы
void generateSnakeDirection(snake_t *snake2, direction *dir2, frut frut[]); // логика ИИ



