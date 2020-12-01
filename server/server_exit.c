/*************************************************************************
	> File Name: server_exit.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月22日 星期日 14时15分09秒
 ************************************************************************/

#include "snake.h"

#define MAX 50
extern User *user;
void server_exit(int signum) {
    SnakeMsg msg;
    msg.type = FT_FIN;
    for (int i = 0; i < MAX; i++) {
        if (user[i].flag) send(user[i].fd, (void *)&msg, sizeof(msg), 0);
    }
    endwin();
    exit(0);
}
