/*************************************************************************
	> File Name: draw_snake.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月24日 星期二 15时18分58秒
 ************************************************************************/

#include "snake.h"


extern SnakeMsg msg;
extern int sockfd;
extern pthread_mutex_t mutex;
void *draw_snake(void *arg) {
    while(1) {
        for(int i = 0; i < msg.cnt; i++) {
            pthread_mutex_lock(&mutex);
            snake_move((void *)&msg.user, i);
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }
    }
}

