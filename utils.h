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
void enterName(string prompt, string name);
void creatmap(string prompt, string **&arr, mapsize &a);
bool checkrow(string **arr, mapsize a, position b);
bool checkcol(string **arr, mapsize a, position b);
bool checkdiagonal(string **arr, mapsize a, position b);
void switchTurn(string &currentPlayer);
bool makeMove(string **arr, mapsize a, position &p, string playerMark);
bool checkGameOver(string **arr, mapsize a, position p, int moves);
bool handleUndoOrContinue(string **arr, Stack &history, string &currentPlayer, int &totalMoves);
void undoMove(string **arr, Stack &history, string &currentPlayer, int &totalMoves);
void deleteArray(string **arr, mapsize a);

#endif