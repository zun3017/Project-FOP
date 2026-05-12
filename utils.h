#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
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

struct Node
{
    position data;
    Node *next;
};

struct Stack
{
    Node *top;
};

void init(Stack &s);
bool isEmpty(Stack s);
void push(Stack &s, position x);
bool pop(Stack &s, position &x);

void print(string **arr, mapsize a);
void enterName(string prompt, string &name);
void creatmap(string prompt, string **&arr, mapsize &a);
int displayAndSelectMenu(string *menuOptions, int numOptions);
void switchTurn(string &currentPlayer, string player1, string player2);
bool makeMove(string **arr, mapsize a, position &p, string playerMark);
bool checkGameOver(string **arr, mapsize a, position p, int moves);
bool UndoOrContinue(string **arr, Stack &history, string &currentPlayer, string player1, string player2, int &totalMoves);
void undoMove(string **arr, Stack &history, string &currentPlayer, string player1, string player2, int &totalMoves);
void deleteArray(string **arr, mapsize a);
bool playAgain();
void showScoreBoard(string player1, int win1, string player2, int win2);
void resetBoard(string **arr, mapsize a);
int displayAndSelectMenu(string *menuOptions, int numOptions);

#endif