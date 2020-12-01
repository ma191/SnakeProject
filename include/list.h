/*************************************************************************
	> File Name: list.h
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 16时22分09秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H
#include "head.h"

typedef struct Node{
    int x;
    int y;
    struct Node *next;
}Node;

typedef struct List{
    Node *head;
    Node *tail;
    int len;
}List;


Node *getnode(int x, int y);
List *init();
void insert(List *l, int x, int y);
void pop(List *l);
#endif
