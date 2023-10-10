#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include "windows.h"
#include <time.h>
#include <stdlib.h>

#define SIZE 50 //количество клеток в линии
const int COUNT = SIZE * SIZE;

using namespace std;

//вывод новой строчки в консоль
void printWorld(const bitset<COUNT>& world) 
{
	int tmp = 0; //для прохода по всем элементам
	for (int i = 0; i < SIZE; i++)
	{
		tmp = i * SIZE;
		for (int j = 0; j < SIZE; j++)
		{
			if (world[tmp + j])
			{
				cout << (char)254 << " ";
			}
			else
			{
				cout << (char)253 << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

//переход на новый шаг
void updateAutomaton(bitset<COUNT>& world, const bitset<512>& rules) 
{
	bitset<COUNT> nextStep;
	int result;
	//отдельный цикл для первой и последней строчки, тк автомат зациклен
	for (int i = 1; i < SIZE - 1; i++)
	{
		//для первой строчки
		result = (world[COUNT - SIZE + i - 1] << 8) | (world[COUNT - SIZE + i] << 7) | (world[COUNT - SIZE + i + 1] << 6) |
			(world[i - 1] << 5) | (world[i] << 4) | (world[i + 1] << 3) | 
			(world[SIZE + i - 1] << 2) | (world[SIZE + i] << 1) | (world[SIZE + i + 1]);
		nextStep[i] = rules[result];

		//для последней
		result = (world[COUNT - SIZE - SIZE + i - 1] << 8) | (world[COUNT - SIZE - SIZE + i] << 7) | (world[COUNT - SIZE - SIZE + i + 1] << 6) |
			(world[COUNT - SIZE + i - 1] << 5) | (world[COUNT - SIZE + i] << 4) | (world[COUNT - SIZE + i + 1] << 3) |
			(world[i - 1] << 2) | (world[i] << 1) | (world[i + 1]);
		nextStep[COUNT - SIZE + i] = rules[result];
	}
	//обработка основного количества поля без границ
	int tmp;
	for (int i = 1; i < SIZE - 1; i++)
	{
		tmp = i * SIZE;
		for (int j = 1; j < SIZE - 1; j++)
		{
			result = (world[tmp + j - SIZE - 1] << 8) | (world[tmp + j - SIZE] << 7) | (world[tmp + j - SIZE + 1] << 6) |
				(world[tmp + j - 1] << 5) | (world[tmp + j] << 4) | (world[tmp + j + 1] << 3) | 
				(world[tmp + j + SIZE - 1] << 2) | (world[tmp + j + SIZE] << 1) | (world[tmp + j + SIZE + 1]);
			nextStep[tmp + j] = rules[result];
		}
	}

	world = nextStep;
}

int main()
{
	srand(time(NULL));
	
	//не пугаться!!! это всего лишь правило для игры в жизнь)))
	bitset<512> rules(string("00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000100000000000000010000000100010110000000000000000000000000000000010000000000000001000000010001011000000000000000010000000100010110000000010001011100010110011010000000000000000000000000000000000100000000000000010000000100010110000000000000000100000001000101100000000100010111000101100110100000000000000000010000000100010110000000010001011100010110011010000000000100010111000101100110100000010111011111100110100010000000")); //цифра исключительно для респекта
	bitset<COUNT> world;
	world[COUNT / 2].flip(); //задаем среднюю клетку живой
	for (int i = 0; i < COUNT; i++)
	{
		if (rand() % 10 > 5)
			world[i].flip();
	}
	for (int i = 0; i < 200; i++)
	{
		printWorld(world);
		updateAutomaton(world, rules);
		Sleep(100);
		system("cls");
	}

}
