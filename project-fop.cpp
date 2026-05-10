#include <iostream>
#include <print>
#include <iomanip>
#include <string>
#include <limits>
#include "utils.cpp"

using namespace std;

int main()
{
	mapsize a = {0, 0};
	string **arr = nullptr;
	Stack history;
	init(history);
	creatmap("Người chơi lựa chọn chọn kích thước bản đồ hoặc tự nhập kích thước: \n", arr, a);

	if (arr != nullptr)
	{
		string currentPlayer = "X";
		position lastMove;
		int totalMoves = 0;
		bool isFinished = false;

		while (!isFinished)
		{
			if (handleUndoOrContinue(arr, history, currentPlayer, totalMoves))
			{
				print(arr, a);
				continue; // quay lại vòng lặp
			}

			if (makeMove(arr, a, lastMove, currentPlayer))
			{
				push(history, lastMove); // Lưu lịch sử nước đi

				print(arr, a);
				totalMoves++;

				if (checkGameOver(arr, a, lastMove, totalMoves))
				{
					isFinished = true;
				}
				else
				{
					switchTurn(currentPlayer); // Chức năng 11
				}
			}
		}
		deleteArray(arr, a);
	}
	return 0;
}
