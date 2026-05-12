#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "utils.h"

using namespace std;

int main()
{
	string *menuOptions = new string[2];
	*(menuOptions + 0) = "Bat dau tro choi";
	*(menuOptions + 1) = "Huong dan";

	int menuChoice;
	do
	{
		menuChoice = displayAndSelectMenu(menuOptions, 2);
		if (menuChoice == 1)
		{
			mapsize a = {0, 0};
			string **arr = nullptr;
			Stack history;
			init(history);
			string player1, player2;
			int win1 = 0;
			int win2 = 0;
			enterName("Nhap ten nguoi choi X: ", player1);
			enterName("Nhap ten nguoi choi O: ", player2);
			creatmap("Nguoi choi lua chon kich thuoc ban do:\n", arr, a);
			if (arr != nullptr)
			{
				position lastMove;
				int totalMoves = 0;
				bool isFinished = false;
				bool player1Starts = true;
				string currentPlayer = player1;
				string currentMark = "X";
				while (!isFinished)
				{
					if (UndoOrContinue(arr, history, currentPlayer, player1, player2, totalMoves))
					{
						currentMark = (currentPlayer == player1) ? "X" : "O";
						print(arr, a);
						continue;
					}
					if (makeMove(arr, a, lastMove, currentMark))
					{
						push(history, lastMove);
						print(arr, a);
						totalMoves++;
						if (checkGameOver(arr, a, lastMove, totalMoves))
						{
							isFinished = true;
							if (totalMoves ==
								(a.row - 1) * (a.col - 1))
							{
								cout << "\nTran dau hoa!\n";
							}
							else
							{
								cout << "\nNguoi chien thang la: " << currentPlayer << " [" << currentMark << "]\n";
								if (currentPlayer == player1)
									win1++;
								else
									win2++;
							}
							showScoreBoard(player1, win1, player2, win2);
							if (playAgain())
							{
								resetBoard(arr, a);
								while (!isEmpty(history))
								{
									position temp;
									pop(history, temp);
								}
								totalMoves = 0;
								isFinished = false;
								player1Starts = !player1Starts;
								if (player1Starts)
								{
									currentPlayer = player1;
									currentMark = "X";
								}
								else
								{
									currentPlayer = player2;
									currentMark = "O";
								}
								print(arr, a);
							}
							else
							{
								break;
							}
						}
						else
						{
							switchTurn(currentPlayer, player1, player2);
							currentMark = (currentMark == "X") ? "O" : "X";
						}
					}
				}
				deleteArray(arr, a);
			}
		}
		else if (menuChoice == 2)
		{
			cout << "\n--- HUONG DAN ---\n";
			cout << "Tao thanh 5 nuoc thang hang de chien thang!\n";
			cout << "Hoac tao thanh 3 nuoc thang hang de chien thang trong ban co 3x3 hoac 4x4! \n";
			cout << "Moi van se luan phien thay doi nguoi di truoc\n";
		}
	} while (menuChoice != 0);

	delete[] menuOptions;
	cout << "Chuong trinh ket thuc. Bam ENTER de thoat...";
	cin.ignore();
	return 0;
}