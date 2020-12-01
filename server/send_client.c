/*************************************************************************
	> File Name: send_client.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月24日 星期二 15时05分11秒
 ************************************************************************/

#include "snake.h"

extern int sub;
extern pthread_mutex_t mutex;
extern SnakeMsg msg;
extern User *user;
#define MAX 50
void *send_client(void *arg) {
    while(1) {
        for(int i = 0; i < MAX; i++) {
            if (!user[i].flag) continue;
            pthread_mutex_lock(&mutex);
            msg.type = FT_GAME;
            send(user[i].fd, (void *)&msg, sizeof(msg), 0);
            pthread_mutex_unlock(&mutex);
        }
        usleep(10000);
    }
}

