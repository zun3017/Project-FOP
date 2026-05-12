#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "utils.h"

using namespace std;

void print(string **arr, mapsize a)
{
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < a.col; j++)
        {
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }
}

void enterName(string prompt, string &name)
{
    cout << prompt;
    getline(cin, name);
}
void creatmap(string prompt, string **&arr, mapsize &a)
{
    int size = 0;
    int choice = 0;
    cout << prompt << endl;
    do
    {
        cout << "Lua chon kich thuoc ban do san co nhap 0, tu nhap kich thuoc chon 1, quay lai man hinh chinh chon 2 \n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
            cout << "Lua chon cua ban chua chinh xac vui long nhap lai lua chon cua ban: ";
        }
    } while (choice > 2 || choice < 0);
    if (choice == 0)
    {
        do
        {
            cout << "Kich thuoc ban do tu chon gom co 0: 3x3, 1: 5x5, 2: 10x10, 3: 15x15, 4: 20x20 \n";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                choice = -1;
                cout << "Lua chon cua ban chua chinh xac vui long nhap lai lua chon cua ban: \n";
            }
            else if (choice == 0)
            {
                a.col = 4;
                a.row = 4;
            }
            else if (choice == 1)
            {
                a.col = 6;
                a.row = 6;
            }
            else if (choice == 2)
            {
                a.col = 11;
                a.row = 11;
            }
            else if (choice == 3)
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
        cout << "Nhap kich thuoc ma ban mong muon \n";
        do
        {
            cout << "Nhap do dai hang: ";
            cin >> a.row;
            if (cin.fail() || a.row < 3)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                a.row = -2;
                cout << "Do dai hang ban nhap chua dung vui long nhap lai: \n";
            }
            a.row++;
        } while (a.row < 0);
        do
        {
            cout << "Nhap do dai cot: ";
            cin >> a.col;
            if (cin.fail() || a.col < 3)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                a.col = -2;
                cout << "Do dai cot ban nhap chua dung vui long nhap lai : \n";
            }
            a.col++;
        } while (a.col < 0);
    }
    else
    {
        return;
    }
    arr = new string *[a.row];
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
                arr[i][j] = to_string(j - 1);
            }
            else if (j == 0)
            {
                arr[i][j] = to_string(i - 1);
            }
            else
            {
                arr[i][j] = ".";
            }
        }
    }
    print(arr, a);
}

void switchTurn(string &currentPlayer, string player1, string player2)
{
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool makeMove(string **arr, mapsize a, position &p, string playerMark)
{
    cout << "\nLuot cua [" << playerMark << "]. Nhap Hang va Cot (vi du: 0 0): ";
    if (!(cin >> p.rowp >> p.colp))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    int r = p.rowp + 1;
    int c = p.colp + 1;
    if (r > 0 && r < a.row && c > 0 && c < a.col && arr[r][c] == ".")
    {
        arr[r][c] = playerMark;
        p.rowp = r;
        p.colp = c;
        return true;
    }
    cout << "Vi tri khong hop le! Vui long chon o khac.\n";
    return false;
}

bool checkGameOver(string **arr, mapsize a, position p, int moves)
{
    // Lấy ký tự của nước đi vừa thực hiện (X hoặc O)
    string mark = arr[p.rowp][p.colp];

    // Mảng hướng di chuyển: Ngang, Dọc, Chéo xuôi, Chéo ngược
    int dr[] = { 0, 1, 1, 1 };
    int dc[] = { 1, 0, 1, -1 };

    // Tính toán kích thước thực tế của vùng chơi (loại bỏ hàng/cột tiêu đề)
    int actualRow = a.row - 1;
    int actualCol = a.col - 1;

    // Xác định số quân liên tiếp cần thiết để chiến thắng
    int winCondition = 5; // Mặc định cho bàn cờ lớn (5x5 trở lên)

    if (actualRow == 3 && actualCol == 3)
    {
        winCondition = 3; // Bàn cờ 3x3 cần 3 quân
    }
    else if (actualRow == 4 && actualCol == 4)
    {
        winCondition = 4; // Bàn cờ 4x4 cần 4 quân
    }

    // Vòng lặp kiểm tra qua 4 hướng đường thẳng
    for (int i = 0; i < 4; i++)
    {
        int count = 1; // Tính chính quân cờ vừa đánh là 1

        // dir = 1 là tiến về một phía, dir = -1 là lùi về phía đối diện
        for (int dir = -1; dir <= 1; dir += 2)
        {
            int r = p.rowp + dr[i] * dir;
            int c = p.colp + dc[i] * dir;

            // Di chuyển và đếm các quân trùng màu liên tiếp trong phạm vi bàn cờ
            while (r > 0 && r < a.row && c > 0 && c < a.col && arr[r][c] == mark)
            {
                count++;
                r += dr[i] * dir;
                c += dc[i] * dir;
            }
        }

        // Nếu đạt hoặc vượt quá số quân quy định thì kết thúc trận đấu
        if (count >= winCondition)
        {
            cout << "\nNGUOI CHOI [" << mark << "] CHIEN THANG!\n";
            return true;
        }
    }

    // Kiểm tra trạng thái hòa cờ khi đã đánh hết các ô trống trống
    if (moves == actualRow * actualCol)
    {
        cout << "\nKET QUA HOA!\n";
        return true;
    }
    return false; // Trò chơi tiếp tục
}

bool UndoOrContinue(string **arr, Stack &history, string &currentPlayer, string player1, string player2, int &totalMoves)
{
    cout << "\nNhap 'u' de undo hoac ENTER de tiep tuc(enter 2 lan neu truoc do undo): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string choice;
    getline(cin, choice);
    if (choice == "u")
    {
        position prev;
        if (pop(history, prev))
        {
            arr[prev.rowp][prev.colp] = ".";
            totalMoves--;
            switchTurn(currentPlayer, player1, player2);
            cout << "Da hoan tac nuoc di!(enter de tiep tuc)\n";
        }
        else
        {
            cout << "Khong co nuoc de hoan tac!\n";
        }
        return true;
    }
    return false;
}

void deleteArray(string **arr, mapsize a)
{
    for (int i = 0; i < a.row; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

bool playAgain()
{
    char choice;

    cout << "\nBan co muon choi tiep khong? (y/n): ";
    cin >> choice;

    return (choice == 'y' || choice == 'Y');
}

void resetBoard(string **arr, mapsize a)
{
    for (int i = 1; i < a.row; i++)
    {
        for (int j = 1; j < a.col; j++)
        {
            arr[i][j] = ".";
        }
    }
}

void showScoreBoard(string player1, int win1, string player2, int win2)
{
    cout << "\n===== BANG TY SO =====\n";
    cout << player1 << ": " << win1 << " win\n";
    cout << player2 << ": " << win2 << " win\n";
    cout << "======================\n";
}

void init(Stack &s)
{
    s.top = nullptr;
}

bool isEmpty(Stack s)
{
    return s.top == nullptr;
}
void push(Stack &s, position x)
{
    Node *newNode = new Node;
    newNode->data = x;
    newNode->next = s.top;
    s.top = newNode;
}

bool pop(Stack &s, position &x)
{
    if (isEmpty(s))
        return false;

    Node *temp = s.top;
    x = temp->data;
    s.top = temp->next;
    delete temp;
    return true;
}

int displayAndSelectMenu(string *menuOptions, int numOptions)
{
    int choice;
    cout << "\n============= MENU GOMOKU =============\n";
    for (int i = 0; i < numOptions; i++)
    {
        cout << "   " << i + 1 << ". " << *(menuOptions + i) << "\n";
    }
    cout << "   0. Thoat chuong trinh\n";
    cout << "=======================================\n";
    cout << "Nhap lua chon: ";
    while (!(cin >> choice) || choice < 0 || choice > numOptions)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Khong hop le, nhap lai: ";
    }
    cin.ignore(1000, '\n');
    return choice;
}
