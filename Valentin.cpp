#include <iostream>
using namespace std;

class Field
{
private:
	int _size;
	int** _matrix;
public:
	Field()
	{
		_size = 0;
		_matrix = nullptr;
	}
	Field(int size)
	{
		_size = size;
		_matrix = new int*[size];
		for (int i = 0; i < _size; i++)
			_matrix[i] = new int[size];
		for (int y = 0; y < _size; y++)
			for (int x = 0; x < _size; x++)
				_matrix[x][y] = 0;
	}
	~Field()
	{
		for (int i = 0; i < _size; i++)
			delete[]_matrix[i];
		delete[]_matrix;
	}
	void printNum()
	{
		cout << "\n  ";
		for (int x = 0; x < _size; x++)
			cout << x << " ";
		cout << "\n";
		for (int y = 0; y < _size; y++)
		{
			cout << y << " ";
			for (int x = 0; x < _size; x++)
				cout << _matrix[x][y] << " ";
			cout << "\n";
		}	
	}		
	void print()
	{
		cout << "\n  ";
		for (int x = 0; x < _size; x++)
			cout << x << " ";
		cout << "\n";
		for (int y = 0; y < _size; y++)
		{
			cout << y << " ";
			for (int x = 0; x < _size; x++)
			{
				switch (_matrix[x][y])
				{
				case 1: // ship
					cout << "#";
					break;
				case 2: // hit
					cout << "x";
					break;
				case 3: // miss
					cout << "o";
					break;
				default:  // nothing here (-1 - aroud a ship)
					cout << "_";
					break;
				}
				cout << " ";
			}
			cout << "\n";
		}
	}
	void operator()(int size) //!only for initialisation in default constructor of other classes
	{
		_size = size;
		_matrix = new int* [size];
		for (int i = 0; i < _size; i++)
			_matrix[i] = new int[size];
		for (int y = 0; y < _size; y++)
			for (int x = 0; x < _size; x++)
				_matrix[x][y] = 0;
	}
	int operator()(int x, int y)
	{
		return _matrix[x][y];
	}
	void operator()(int x, int y, int obj)
	{
		_matrix[x][y] = obj;
	}
	void autoFill()
	{
		int deck = 4; //size of ship that will be placed		4->1
		int ship = 1; //amount of the ships that will be placed 1->4
		bool isRotated; 
		int x, y; //coordinates of the begonning of the ship
		bool free;

		for (int k = deck; k > 0; k--)
		{
			int temp = 0; // how many ships was already placed
			while (temp < ship)
			{
				isRotated = rand() % 2;
				if (isRotated) //for one rotation
				{
					do //searching for a free space
					{
						free = 0;
						x = rand() % _size;
						y = rand() % (_size - (deck + 1));
						for (int i = y; i <= y + deck; i++)
						{
							if (_matrix[x][i] != 0)
							{
								free = 1;
								break;
							}
						}
					} while (free);

					// -1 (where other ships cannot go)
					for (int i = x - 1; i <= x + 1; i++)
					{
						for (int j = y - 1; j <= y + deck; j++)
						{
							if (i >= 0 && i < _size && j >= 0 && j < _size)
								_matrix[i][j] = -1;
						}
					}
					// 1 (ship)
					for (int i = y; i < y + deck; i++)
						_matrix[x][i] = 1;
				}
				else //for another rotation
				{
					do //searching for a free space
					{
						free = 0;
						x = rand() % (_size - (deck + 1));
						y = rand() % _size;
						for (int i = x; i <= x + deck; i++)
						{
							if (_matrix[i][y] != 0)
							{
								free = 1;
								break;
							}
						}
					} while (free);

					// -1 (where other ships ship cannot go)
					for (int i = x - 1; i <= x + deck; i++)
					{
						for (int j = y - 1; j <= y + 1; j++)
						{
							if (i >= 0 && i < _size && j >= 0 && j < _size)
								_matrix[i][j] = -1;
						}
					}
					// 1 (ship)
					for (int i = x; i < x + deck; i++)
						_matrix[i][y] = 1;
				}
				temp++;
			}
			deck--;
			ship++;
		}
	}
	void fill()
	{
		int deck = 4;
		int ship = 1;
		bool isRotated;
		int x, y;
		bool free;

		for (int k = deck; k > 0; k--)
		{
			int temp = 0;
			while (temp < ship)
			{
				system("cls");
				print();

				cout << "Enter size " << deck << " ship x: "; cin >> x;
				cout << "Enter size " << deck << " ship y: "; cin >> y;
				if (deck != 1)
				{
					cout << "Press 0 for horisontal rotation, 1 for vertical rotaion: "; cin >> isRotated;
				}
				
				if (isRotated) //for one rotation
				{
					do //searching for a free space
					{
						free = 0;
						for (int i = y; i <= y + deck; i++)
						{
							if (_matrix[x][i] != 0)
							{
								free = 1;
								cout << "Place isn't free!\n";
								cout << "Enter size " << deck << " ship x: "; cin >> x;
								cout << "Enter size " << deck << " ship y: "; cin >> y;
								break;
							}
						}
					} while (free);

					// -1 (where other ships cannot go)
					for (int i = x - 1; i <= x + 1; i++)
					{
						for (int j = y - 1; j <= y + deck; j++)
						{
							if (i >= 0 && i < _size && j >= 0 && j < _size)
								_matrix[i][j] = -1;
						}
					}
					// 1 (ship)
					for (int i = y; i < y + deck; i++)
						_matrix[x][i] = 1;
				}
				else //for another rotation
				{
					do //searching for a free space
					{
						free = 0;
						for (int i = x; i <= x + deck; i++)
						{
							if (_matrix[i][y] != 0)
							{
								free = 1;
								cout << "Place isn't free!\n";
								cout << "Enter size " << deck << " ship x: "; cin >> x;
								cout << "Enter size " << deck << " ship y: "; cin >> y;
								break;
							}
						}
					} while (free);

					// -1 (where other ships ship cannot go)
					for (int i = x - 1; i <= x + deck; i++)
					{
						for (int j = y - 1; j <= y + 1; j++)
						{
							if (i >= 0 && i < _size && j >= 0 && j < _size)
								_matrix[i][j] = -1;
						}
					}
					// 1 (ship)
					for (int i = x; i < x + deck; i++)
						_matrix[i][y] = 1;
				}
				temp++;
			}
			deck--;
			ship++;
		}
		system("cls");
		
	}
};

class Player
{
private:
	Field shipField;
	Field hitField;
public:
	Player(int size)
	{
		shipField(size);
		hitField(size);
	}

};

class Game
{
private:
	bool _status;
	bool _playerWin;
	Field _aiShips;
public:
	Game()
	{
		_status = true;
		_playerWin = false;

	}
	bool isGoing()
	{
		return _status;
	}
};

int main()
{
	/*
	//Before start
	int sizeOfFields = 10;
	Game game;
	Player player(sizeOfFields);
	//Game started
	while (game.isGoing())
	{

	}
	*/
	srand(time(0));
	Field test(10);
	test.fill();
}

