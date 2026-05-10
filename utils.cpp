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
            cout << "Lua chon cua ban chua chinh xac vui long nhap lai lua chon cua ban:";
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
            if (cin.fail())
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
            if (cin.fail())
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

bool checkrow(string **arr, mapsize a, position b)
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

bool checkcol(string **arr, mapsize a, position b)
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

bool checkdiagonal(string **arr, mapsize a, position b)
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
    if (count >= 5)
        return true;
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
        p.rowp = r; // Cập nhật vị trí thực tế trong mảng để kiểm tra thắng
        p.colp = c;
        return true;
    }
    cout << "Vi tri khong hop le! Vui long chon o khac.\n";
    return false;
}

bool checkGameOver(string **arr, mapsize a, position p, int moves)
{
    string mark = arr[p.rowp][p.colp];
    int dr[] = {0, 1, 1, 1}; // Ngang, Dọc, Chéo xuôi, Chéo ngược
    int dc[] = {1, 0, 1, -1};

    for (int i = 0; i < 4; i++)
    {
        int count = 1;
        for (int dir = -1; dir <= 1; dir += 2)
        {
            int r = p.rowp + dr[i] * dir;
            int c = p.colp + dc[i] * dir;
            while (r > 0 && r < a.row && c > 0 && c < a.col && arr[r][c] == mark)
            {
                count++;
                r += dr[i] * dir;
                c += dc[i] * dir;
            }
        }
        if (count >= 5)
        {
            cout << "\nNGUOI CHOI [" << mark << "] CHIEN THANG!\n";
            return true;
        }
    }
    if (moves == (a.row - 1) * (a.col - 1))
    {
        cout << "\nKET QUA HOA!\n";
        return true;
    }
    return false;
}

bool handleUndoOrContinue(string **arr,
                          Stack &history,
                          string &currentPlayer,
                          string player1,
                          string player2,
                          int &totalMoves)
{
    cout << "\nNhap 'u' de undo hoac ENTER de tiep tuc: ";
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

            switchTurn(currentPlayer,
                       player1,
                       player2);

            cout << "Da hoan tac nuoc di!(enter de tiep tuc)\n";
        }
        else
        {
            cout << "Khong co nuoc de hoan tac!(enter de tiep tuc)\n";
        }
        return true;
    }

    return false;
}

void undoMove(string **arr, Stack &history, string &currentPlayer, string player1, string player2, int &totalMoves)
{
    position prev;

    if (pop(history, prev))
    {
        // xóa nước đi gần nhất
        arr[prev.rowp][prev.colp] = ".";

        totalMoves--;

        // trả lượt lại cho người trước
        switchTurn(currentPlayer, player1, player2);

        cout << "Da hoan tac nuoc di!\n";
    }
    else
    {
        cout << "Khong co nuoc de hoan tac!\n";
    }
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