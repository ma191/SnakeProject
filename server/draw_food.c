/*************************************************************************
	> File Name: draw_food.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月26日 星期四 10时46分55秒
 ************************************************************************/

#include "snake.h"
extern SnakeMsg msg;
pthread_mutex_t mutex;
User *user;
void *draw_food(void *arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10; i++) {
        msg.food[i].x = rand() % 60 + 2;
        msg.food[i].y = rand() % 30 + 2;
        w_gotoxy_putc(wsnake, msg.food[i].x, msg.food[i].y, '1');
    }
    pthread_mutex_unlock(&mutex);
    sleep(2);
}
