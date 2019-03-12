//
// Created by PC on 2019/2/27.
//

#ifndef WORKSHOP_GLOBAL_H
#define WORKSHOP_GLOBAL_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
#define TRUE 1
#define FALSE 0
#define ROW 9
#define COL 9
#define NoAnwser -1
typedef int status;

typedef struct DataNode {
    int data = 0;
    DataNode *next{};
}DataNode;

typedef struct HeadNode {
    int Num = 0;
    DataNode *right{};
    HeadNode *down{};
}HeadNode;

struct consequence {
    int value = -1;//存真值 真时为true-1，假时为false-0
};

struct conse {
    int num = 0;
    int value = -1;//存真值 真时为true-1，假时为false-0
};

void Start();

HeadNode* CreateClause(int &,string &);

status DPLL(HeadNode *LIST,consequence *result);
HeadNode* IsSingleClause(HeadNode*);
status IsEmptyClause(HeadNode*);
HeadNode* ADDSingleClause(HeadNode*,int);
HeadNode* Duplication(HeadNode*);
void DeleteHeadNode(HeadNode*,HeadNode*&);
void DeleteDataNode(int,HeadNode*&);
void show(struct consequence *,int);

int Digit(int a[][COL], int i, int j);
void randomFirstRow(int a0[], int n);
void createSudoku(int a[][COL]);
void createStartinggrid(const int a[][COL], int b[][COL], int numDigits);
void print(const int a[][COL]);
string ToCnf(int a[][COL],int holes);
string createSudokuToFile();
status SudoDPLL(HeadNode *LIST,conse *result,int VARNUM);
void SudokuShow(conse *result,int VARNUM);

#endif //WORKSHOP_GLOBAL_H
