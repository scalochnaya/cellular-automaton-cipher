#include <iostream>
#include <bitset>
#include <vector>
//#include "windows.h"

#define COUNT 128 //количество клеток в линии

using namespace std;

//вывод новой строчки в консоль
void printWorld(const bitset<COUNT>& world) {
	for (int i = 0; i < COUNT; i++) 
	{
		if (world[i]) 
		{
			cout << (char)254;  // если клетка жива
		}
		else 
		{
			cout << (char)253;  // если клетка мертва
		}
	}
	cout << endl;
}

//переход на новый шаг
void updateAutomaton(bitset<COUNT>& world, const bitset<8>& rules) {
	bitset<COUNT> nextStep;
	int result;
	//получаем значение предыдущей, нашей и следующей клетки и создаем из этого номер правила. Пример:
	//01001 было, берем последний элемент и умножаем на 4, первый умножаем на 2 и второй без изменений
	//получаем 1*4+0*2+1=5. 
	result = (world[COUNT - 1] << 2) | (world[0] << 1) | world[1]; 
	nextStep[0] = rules[result];

	for (int i = 1; i < COUNT - 1; i++) {
		result = (world[i - 1] << 2) | (world[i] << 1) | (world[i + 1]);
		nextStep[i] = rules[result];
	}
	result = (world[COUNT - 2] << 2) | (world[COUNT-1] << 1) | world[0];
	nextStep[COUNT - 1] = rules[result];

	world = nextStep;
}

int main()
{
	bitset<8> rules(40); //правило любое можно задать, 30 110 196
	
	bitset<COUNT> world;
	world[COUNT / 2].flip(); //задаем среднюю клетку живой
	for (int i = 0; i < 200; i++)
	{
		printWorld(world);
		updateAutomaton(world, rules);
		//Sleep(1000);
		//system("cls");
	}

}
