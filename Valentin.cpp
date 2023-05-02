#include <iostream>
using namespace std;

class Field
{
private:
	int _size;
	int** _matrix;
public:
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
				default:  // nothing here
					cout << "_";
					break;
				}
				cout << " ";
			}
			cout << "\n";
		}
	}
	int operator()(int x, int y)
	{
		return _matrix[x][y];
	}
	void operator()(int x, int y, int obj)
	{
		_matrix[x][y] = obj;
	}
};

class Game
{
private:
	bool _status;
public:
	Game()
	{
		_status = true;

	}
};

int main()
{
	Field test(10);
	test.printNum();
	test.print();
	test(1, 2, 2);
	test.printNum();
	test.print();
}

