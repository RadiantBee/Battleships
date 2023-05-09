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
	void printHit() // print only hits or misses
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
		int x = 0; 
		int y = 0;
		bool free;

		for (int k = deck; k > 0; k--)
		{
			int temp = 0;
			while (temp < ship)
			{
				system("cls");
				print();


				while (true)
				{
					cout << "Enter size " << deck << " ship x: "; cin >> x;
					cout << "Enter size " << deck << " ship y: "; cin >> y;
					if (deck != 1)
					{
						cout << "Press 0 for horisontal rotation, 1 for vertical rotaion: "; cin >> isRotated;
					}
					if (x > -1 && x < _size && y > -1 && y < _size)
						break;
					else
					{
						cout << "Place isn't free!\n";
					}
				}
				
				if (isRotated) //for one rotation
				{
					do //searching for a free space
					{
						free = 0;
						for (int i = y; i <= y + deck - 1; i++)
						{
							if (i > 9 || _matrix[x][i] != 0)
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
						for (int j = y - 1; j <= y + deck - 1; j++)
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
						for (int i = x; i <= x + deck - 1; i++)
						{
							if (i > 9 || _matrix[i][y] != 0)
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
	void hit(int x, int y)
	{
		if (_matrix[x][y] == 1)
		{
			_matrix[x][y] = 2;
		}
		else
		{
			_matrix[x][y] = 3;
		}
	}
};

class Player
{
private:
	Field _shipField;// field with player ships
	Field _hitField; // field with enemy ships
	int _playerShipsLeft;	
	int _enemyShipsLeft;
	unsigned int _direction; // for AI to remember a direction
	int _x; // for AI to remember x of the last hit
	int _y; // for AI to remember y of the last hit
	int _hits; // for AI to remember hits
	int _firstHitX;
	int _firstHitY;
	bool _directionWasChanged;
public:
	Player(int size)
	{
		_shipField(size);
		_shipField.autoFill();//_shipField.fill(); !!!changed for testing purposes
		_hitField(size);
		_hitField.autoFill();
		_playerShipsLeft = 20;
		_enemyShipsLeft = 20;
		//For algorithm
		_direction = 0;
		_hits = 0;
		_x = 0;
		_y = 0;
		_firstHitX = 0;
		_firstHitY = 0;
		_directionWasChanged = false;
	}
	bool playerShipsLeft()
	{
		return _playerShipsLeft;
	}
	bool enemyShipsLeft()
	{
		return _enemyShipsLeft;
	}
	void playerTurn()
	{
		int x; int y;
		bool repeat = true;
		while (repeat)
		{
			repeat = false;

			system("cls");
			cout << "Your ships: ";
			_shipField.print();
			cout << "Your hits: ";
			_hitField.printHit();

			cout << "Hit x: "; cin >> x;
			cout << "Hit y: "; cin >> y;
			_hitField.hit(x, y);
			if (_hitField(x,y) == 2)
			{
				repeat = true;
				_enemyShipsLeft--;
			}
		}

	}
	void aiTurn(int size)
	{
		_x = rand() % size;
		_y = rand() % size;
		while (true)
		{
			if(!_hits)
			{ 
				if (_shipField(_x, _y) == 2 || _shipField(_x, _y) == 3) // 2 = hit, 3 = miss
				{
					_x = rand() % size;
					_y = rand() % size;
				}
				if (_shipField(_x, _y) != 1) // if miss
				{
					_shipField.hit(_x, _y);
					break;
				}
				if (_shipField(_x, _y) == 1) // if first hit of a ship
				{
					_shipField.hit(_x, _y);
					_firstHitX = _x;
					_firstHitY = _y;
					_hits++;
					_playerShipsLeft--;
				}
			}
			
			if (_hits)
			{
				int tempX, tempY;
				while (_x + _direction - 2 == size || _y + _direction - 1 == size) // if direction lead in a bad spot
				{
					_direction++; // change direction
				}
				// there are 4 directions: ↑ = 0; → = 1; ↓ = 2; ← = 3
				if (_direction > 3)
				{
					_hits = 0;
					_direction = 0;
					continue;
				}

				
				if (_direction % 2)
				{
					tempX = _x + _direction - 2;
					tempY = _y;
				}
				else
				{
					tempX = _x;
					tempY = _y + _direction - 1;
				}
				
				if (_shipField(tempX, tempY) != 1) // if miss
				{
					_shipField.hit(tempX, tempY);
					if (_hits > 2) // if we already know rotation of the ship
					{
						if(!_directionWasChanged)
						{
							if (_direction > 1)
								_direction -= 2;
							else
								_direction += 2;
							_x = _firstHitX;
							_y = _firstHitY;
							_directionWasChanged = true;
						}
						else
						{
							_directionWasChanged = false;
							_hits = 0;
							_direction = 0;
						}
					}
					else
					{
						_direction++;
					}
					break;
				}
				if (_shipField(tempX, tempY) == 1) // if hit a ship
				{
					_shipField.hit(tempX, tempY);
					_x = tempX;
					_y = tempY;
					_hits++;
					_playerShipsLeft--;
					if (_hits == 4)
						_hits = 0;
				}
				
			}
		}
	}
};

class Game
{
private:
	bool _playerWin;
	bool _again;
public:
	Game()
	{
		_playerWin = false;
		_again = true;
	}
	void play(int size = 10)
	{
		srand(time(0));
		while (_again)
		{
			Player player(size);
			while (true)
			{
				player.playerTurn();
				if (!player.enemyShipsLeft())
				{
					_playerWin = true;
					break;
				}
				player.aiTurn(size);
				if (!player.playerShipsLeft())
					break;
			}
			system("cls");
			switch (_playerWin)
			{
			case false:
				cout << "You lost!\n";
				break;
			case true:
				cout << "Congratulations! You won!\n";
				break;
			}
			cout << "Press 0 to end game or 1 to continue:"; cin >> _again;
		}
		
	}

};

int main()
{
	
	Game game;
	game.play();

}

