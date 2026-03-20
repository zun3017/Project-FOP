#include<iostream>
#include<print>
#include<iomanip>
#include<string>
using namespace std;
struct mapsize
{
	int row;
	int col;
};
struct position
{
	int rowp;
	int colp;
};
void print(string** arr, mapsize a)
{
	for (int i = 0; i < a.row; i++)
	{
		for (int j = 0; j < a.col; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
void creatmap(string**& arr, mapsize a)
{
	arr = new string * [a.row];
	for (int i = 0; i < a.row; i++)
	{
		arr[i] = new string[a.col];
	}
	for (int i = 0; i < a.row; i++)
	{
		for (int j = 0; j < a.col; j++)
		{
			if (i == 0 && j == 0)
			{
				arr[i][j] = " ";
			}
			else if (i == 0)
			{
				arr[i][j] = to_string(j-1);

			}
			else if (j == 0)
			{
				arr[i][j] = to_string(i-1);
			}
			else
			{
				arr[i][j] = ".";
			}
		}
	}
	print(arr, a);
}
bool checkraw(string** arr, mapsize a, position b)
{
	int count = 0;
	string check = arr[b.rowp][b.colp];
	for (int i = b.colp; i < a.col; i++)
	{
		if (arr[b.rowp][i] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	for (int i = b.colp - 1; i > 0; i--)
	{
		if (arr[b.rowp][i] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	return count >= 5;
}
bool checkcol(string** arr, mapsize a, position b)
{
	int count = 0;
	string check = arr[b.rowp][b.colp];
	for (int i = b.rowp; i < a.row; i++)
	{
		if (arr[i][b.colp] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	for (int i = b.rowp - 1; i > 0; i--)
	{
		if (arr[i][b.colp] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	return count >= 5;
}
bool checkdiagonal(string** arr, mapsize a, position b)
{
	string check = arr[b.rowp][b.colp];
	int count = 0;
	for (int i = b.rowp, j = b.colp; i < a.row && j < a.col; i++, j++)
	{
		if (arr[i][j] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	for (int i = b.rowp - 1, j = b.colp - 1; i > 0 && j > 0; i--, j--)
	{
		if (arr[i][j] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	if (count >= 5)return true;
	count = 0;
	for (int i = b.rowp, j = b.colp; i > 0 && j < a.col; i--, j++)
	{
		if (arr[i][j] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	for (int i = b.rowp + 1, j = b.colp - 1; i < a.row && j > 0; i++, j--)
	{
		if (arr[i][j] == check)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	return count >= 5;
}



































void deleteArray(string** arr,mapsize a)
{
	for (int i = 0; i < a.row; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

int main()
{
	mapsize a;
	a.col = 6;
	a.row = 6;
	string** arr=nullptr;
	creatmap(arr, a);





	deleteArray(arr, a);
	return 0;
}


