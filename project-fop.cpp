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
			cout <<setw(3)<< arr[i][j];
		}
		cout << endl;
	}
}
void creatmap(string prompt ,string**& arr, mapsize a)
{
	int size = 0;
	int choice = 0;
	cout << prompt << endl;
	do
	{
		cout << "Lựa chọn kích thước bản đồ sẵn có nhập 0, tự nhập kích thước chọn 1, quay lại màn hình chính chọn 2 \n";
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			choice = -1;
			cout << "Lựa chọn của bạn chưa chính xác vui lòng nhập lại lựa chọn của bạn: ";
		}
	} while (choice > 2 || choice < 0);
	if (choice == 0)
	{
		do
		{
			cout << "Kích thước bản đồ tự chọn gồm có 0: 3x3, 1: 5x5, 2: 10x10, 3: 15x15, 4: 20x20 \n";
			cin >> choice;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				choice = -1;
				cout << "Lựa chọn của bạn chưa chính xác vui lòng nhập lại lựa chọn của bạn: \n";
			}
			else if(choice == 0)
			{
				a.col = 4;
				a.row = 4;
			}
			else if(choice == 1)
			{
				a.col = 6;
				a.row = 6;
			}
			else if(choice == 2)
			{
				a.col = 11;
				a.row = 11;
			}
			else if(choice==3)
			{ 
				a.col = 16;
				a.row = 16;
			}
			else
			{
				a.col = 21;
				a.row = 21;
			}
			
		} while (choice < 0 || choice > 4);
		choice = -1;
	}
	else if (choice == 1)
	{
			cout << "Nhập kích thước mà bạn mong muốn \n";
			do
			{
				cout << "Nhập độ dài hàng: ";
				cin >> a.row;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					a.row = -2;
					cout << "Độ dài hàng bạn nhập chưa đúng vui lòng nhập lại: \n";
				}
				a.row++;
			} while (a.row < 0);
			do
			{
				cout << "Nhập độ dài cột: ";
				cin >> a.col;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					a.col = -2;
					cout << "Độ dài cột bạn nhập chưa đúng vui lòng nhập lại : \n";
				}
				a.col++;
			} while (a.col < 0);
	}
	else
	{
		return;
	}
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

//11 Luân phiên lượt chơi
void switchTurn(string& currentPlayer) {
	currentPlayer = (currentPlayer == "X") ? "O" : "X";
}

//9:Nhập nước đi.
bool makeMove(string** arr, mapsize a, position& p, string playerMark) {
	cout << "\nLuot cua [" << playerMark << "]. Nhap Hang va Cot (vi du: 0 0): ";
	if (!(cin >> p.rowp >> p.colp)) {
		cin.clear();
		cin.ignore(1000, '\n');
		return false;
	}

	// Vì hàng 0 và cột 0 là tiêu đề, ta cộng thêm 1 để vào đúng ô trong mảng
	int r = p.rowp + 1;
	int c = p.colp + 1;

	if (r > 0 && r < a.row && c > 0 && c < a.col && arr[r][c] == ".") {
		arr[r][c] = playerMark;
		p.rowp = r; // Cập nhật vị trí thực tế trong mảng để kiểm tra thắng
		p.colp = c;
		return true;
	}
	cout << "Vi tri khong hop le! Vui long chon o khac.\n";
	return false;
}

//10:Kiểm tra thắng thua
bool checkGameOver(string** arr, mapsize a, position p, int moves) {
	string mark = arr[p.rowp][p.colp];
	int dr[] = { 0, 1, 1, 1 }; // Ngang, Dọc, Chéo xuôi, Chéo ngược
	int dc[] = { 1, 0, 1, -1 };

	for (int i = 0; i < 4; i++) {
		int count = 1;
		for (int dir = -1; dir <= 1; dir += 2) {
			int r = p.rowp + dr[i] * dir;
			int c = p.colp + dc[i] * dir;
			while (r > 0 && r < a.row && c > 0 && c < a.col && arr[r][c] == mark) {
				count++;
				r += dr[i] * dir;
				c += dc[i] * dir;
			}
		}
		if (count >= 5) {
			cout << "\nNGUOI CHOI [" << mark << "] CHIEN THANG!\n";
			return true;
		}
	}
	if (moves == (a.row - 1) * (a.col - 1)) {
		cout << "\nKET QUA HOA!\n";
		return true;
	}
	return false;
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
	mapsize a = { 0,0 };
	string** arr=nullptr;
	creatmap("Người chơi lựa chọn chọn kích thước bản đồ hoặc tự nhập kích thước :\n", arr, a);
	if (arr != nullptr) {
		string currentPlayer = "X";
		position lastMove;
		int totalMoves = 0;
		bool isFinished = false;

		while (!isFinished) {
			if (makeMove(arr, a, lastMove, currentPlayer)) {
				print(arr, a);
				totalMoves++;

				if (checkGameOver(arr, a, lastMove, totalMoves)) {
					isFinished = true;
				}
				else {
					switchTurn(currentPlayer); // Chức năng 11
				}
			}
		}
		deleteArray(arr, a);
	}
	return 0;
}


