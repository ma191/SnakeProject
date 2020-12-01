/*************************************************************************
	> File Name: heart.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月21日 星期六 10时36分15秒
 ************************************************************************/

#include "snake.h"

#define MAX 50
extern User *user;
extern int user_epollfd;
void heart_beat_user(User *user) {
    SnakeMsg msg;
    for (int i = 0; i < MAX; i++) {
        msg.type = FT_TEST;
        if (user[i].flag) {
            if (!user[i].time){
                user[i].flag = 0;
                printf("%s掉线\n", user->name);
                continue;
            }
            send(user[i].fd, (void *)&msg, sizeof(msg), 0);
            user[i].time--;
            if(user[i].time <= 0) {
                char tmp[512] = {0};
                user[i].flag = 0;
                sprintf(tmp, "%s is removd from list", user[i].name);
                show_message(wmessage, &user[i], tmp, 1);
                del_event(user_epollfd, user[i].fd);
            }
        }
    }
}

void *heart_beat(void *arg) {
    while (1) {
        sleep(2);
        heart_beat_user(user);
    }
}
