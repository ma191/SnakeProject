/*************************************************************************
	> File Name: re_draw.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月24日 星期二 10时20分21秒
 ************************************************************************/

#include "snake.h"

#define MAX 50

extern User *user;
extern int user_epollfd;
extern int sub;

void re_draw() {
    //wclear(wsnake);
    for (int i = 0; i < MAX; i++) {
        if (!user[i].flag) {
            continue;
        }
     snake_move(&user[i], i);
    }    
}

