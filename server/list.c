/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 15时18分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node *getnode(int x, int y){
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->x = x;
    node->y = y;
    return node;
}

List *init() {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

void insert(List *l, int x, int y) {
    Node *node = getnode(x, y);
    if(l == NULL) {
        l->head = node;
    }
    node->next = l->head;
    l->head = node;
    l->len++;
}

void pop(List *l) {
    if(l == NULL) return ;
    if(l->head == NULL) return;
    Node *p = l->head;
    for(int i = 0; i < l->len - 1; i++) {
        p = p->next;
    }
    free(p->next);
    p->next = NULL;
    l->tail = p;
    l->len--;
    return ;
}

void output(List *l) {
    if(l ==  NULL) return;
    if(l->head == NULL) return ;
    /*List *p = l;
    for(int i = 0; i < p->len; i++){
        printf("x=%d\n", p->head->x);
        printf("y=%d\n", p->head->y);
        p->head = p->head->next;
    }*/
    Node *p = l->head;
    for (int i = 0; i < l->len; i++){
        printf("x=%d\n", p->x);
        printf("y=%d\n", p->y);
        p = p->next;
        
    }
    return ;
}
