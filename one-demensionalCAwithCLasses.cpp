#include <iostream>
#include <bitset>

#define COUNT 200 //количество клеток в линии

using namespace std;


class MyWorld
{
private:
	bitset<COUNT> world;
	bitset<8> rule;
public:
	MyWorld(int Rule = 196)
	{
		rule = Rule;
		cout << "\nMyWorld constructor with rule " << rule.to_ulong() << "\n";
	}
	~MyWorld()
	{
		cout << "\nMyWorld destructor\n";
	}
	
	friend ostream& operator<<(ostream& s, const MyWorld& W)
	{
		for (int i = 0; i < COUNT; i++)
		{
			if (W.world[i])
			{
				cout << (char)254;  // если клетка жива
			}
			else
			{
				cout << (char)253;  // если клетка мертва
			}
		}
		cout << endl;
		return s;
	}

	//переход на новый шаг
	void updateAutomaton() 
	{
		bitset<COUNT> nextStep;
		int result;
		//получаем значение предыдущей, нашей и следующей клетки и создаем из этого номер правила. Пример:
		//01001 было, берем последний элемент и умножаем на 4, первый умножаем на 2 и второй без изменений
		//получаем 1*4+0*2+1=5. 
		result = (world[COUNT - 1] << 2) | (world[0] << 1) | world[1];
		nextStep[0] = rule[result];

		for (int i = 1; i < COUNT - 1; i++) {
			result = (world[i - 1] << 2) | (world[i] << 1) | (world[i + 1]);
			nextStep[i] = rule[result];
		}
		result = (world[COUNT - 2] << 2) | (world[COUNT - 1] << 1) | world[0];
		nextStep[COUNT - 1] = rule[result];

		world = nextStep;
	}
	void fillWithRand()
	{
		for (int i = 0; i < COUNT; i++)
		{
			if (rand() % 100 > 50)
				world[i].flip();
		}
	}
	void flip(int i)
	{
		world[i].flip();
	}
};

int main()
{
	srand(time(NULL));
	MyWorld world(184);
	world.fillWithRand();
	world.flip(COUNT / 2);
	for (int i = 0; i < 200; i++)
	{
		cout << world;
		world.updateAutomaton();
	}

}

