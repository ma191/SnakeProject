/*************************************************************************
	> File Name: send_file.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月21日 星期六 14时12分14秒
 ************************************************************************/

#include "snake.h"

extern int sockfd;
extern pthread_mutex_t mutex;
#define MAX 50
int flag = 0;
void *recv_file(void *arg) {
    while(1) {
	    SnakeMsg msg;
        User user;
        char tmp[512] = {0};
        bzero(&msg, sizeof(msg));
        bzero(tmp, sizeof(tmp));
        recv(sockfd, (void *)&msg, sizeof(msg), 0);
        strcpy(user.name, msg.name);
        if (msg.type & FT_TEST) {
            //printf("心跳\n");
            msg.type = FT_ACK;
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        } else if (msg.type & FT_MSG ) {
                show_message(wmessage, &user, msg.msg, 0);
        } else if (msg.type & FT_WALL) {
            show_message(wmessage, &user, msg.msg, 1);
        } else if (msg.type & FT_FIN) {
            //printf("Server stop\n");
            endwin();
        } else if (msg.type & FT_GAME) {
            for (int i = 0; i < MAX; i++) {
                if (!msg.user[i].flag)continue;
                snake_move(&msg.user[i], i); 
            }
            for (int i = 0; i < 10; i++) {
                wattron(wsnake, COLOR_PAIR(6));
                mvwprintw(wsnake, msg.food[i].y, msg.food[i].x, "1");
                wrefresh(wsnake);
            }
        } else if (msg.type & FT_S){
            int num = 1;
            pthread_mutex_lock(&mutex);
            for(int i = 0; i < MAX; i++) {
                if(!msg.user[i].flag) {
                    continue;
                }
                w_gotoxy_puts(wscore, 1, num, msg.user[i].name);
                char score[10] = {0};
                sprintf(score, "%d", msg.score[i].type);
                w_gotoxy_puts(wscore, 10, num, score);
                num++;
            }
            pthread_mutex_unlock(&mutex);
        }
    }
}

