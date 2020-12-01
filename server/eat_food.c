/*************************************************************************
	> File Name: eat_food.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月27日 星期五 09时55分28秒
 ************************************************************************/

#include "snake.h"

#define MAX 50
extern User *user;
extern SnakeMsg msg;
extern pthread_mutex_t mutex;
/*void *eat_food(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
	    for (int i = 0; i < MAX; i++) {
            if(user[i].flag) continue;
            for(int j = 0; j < 10; j++) {
                if(msg.food[j].x == user[i].snake.l->head->x && msg.food[j].y == user[i].snake.l->head->y) {
                    insert(user[i].snake.l, user[i].snake.l->head->y, user[i].snake.l->head->x);
                }
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}*/
