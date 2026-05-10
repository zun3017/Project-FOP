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