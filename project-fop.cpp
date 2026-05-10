#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "utils.h"

using namespace std;

int main()
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
	creatmap("Người chơi lựa chọn chọn kích thước bản đồ hoặc tự nhập kích thước: \n", arr, a);
	if (arr != nullptr)
	{
		string currentPlayer = player1;
		string currentMark = "X";
		position lastMove;
		int totalMoves = 0;
		bool isFinished = false;
		while (!isFinished)
		{
			if (handleUndoOrContinue(arr, history, currentPlayer, player1, player2, totalMoves))
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

					cout << "\nNguoi chien thang la: "
						 << currentPlayer << " [" << currentMark << "]\n";

					if ((a.row - 1) * (a.col - 1))
						;

					else if (currentPlayer == player1)
						win1++;
					else
						win2++;
					showScoreBoard(player1, win1, player2, win2);
					if (playAgain())
					{
						resetBoard(arr, a);
						// reset history stack
						while (!isEmpty(history))
						{
							position temp;
							pop(history, temp);
						}
						totalMoves = 0;
						isFinished = false;
						currentPlayer = player1;
						currentMark = "X";
						print(arr, a);
					}
				}
				else
				{
					// đổi lượt
					switchTurn(currentPlayer, player1, player2);
					// đổi X/O
					currentMark = (currentMark == "X") ? "O" : "X";
				}
			}
		}
	}
	return 0;
}
