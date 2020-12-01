/*************************************************************************
	> File Name: send_score.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月28日 星期六 12时13分42秒
 ************************************************************************/

#include "snake.h"

extern pthread_mutex_t mutex;
extern SnakeMsg msg;
extern User *user;
#define MAX 50
void *send_score(void *arg) {
	while(1) {
        for(int i = 0; i < MAX; i++) {
            if (!user[i].flag) continue;
            pthread_mutex_lock(&mutex);
            msg.type = FT_S;
            send(user[i].fd, (void *)&msg, sizeof(msg), 0);
            pthread_mutex_unlock(&mutex);
        }
        usleep(10000);
    }

}

