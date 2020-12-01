/*************************************************************************
	> File Name: send_chat.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月23日 星期一 15时20分13秒
 ************************************************************************/

#include "snake.h"

extern int sockfd;
//extern SnakeMsg chat_msg;
extern pthread_mutex_t mutex;

void send_chat() {
    SnakeMsg chat_msg;
    bzero(&chat_msg, sizeof(chat_msg));
    chat_msg.type = FT_MSG;
    echo();
    w_gotoxy_puts(wwrite, 1, 1, "快捷输入法: ");
    char w = getchar();
    switch(w) {
        case '1': {
            sprintf(chat_msg.msg, "%s", "你好");
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
        }break;
        case '2': {
            sprintf(chat_msg.msg, "%s", "干的漂亮");
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
        }break;
        case '3': {
            sprintf(chat_msg.msg, "%s", "无敌了你");
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
        }break;
        case '4': {
            sprintf(chat_msg.msg, "%s", "傻狗李二狗");
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
        }break;
        case '5': {
            sprintf(chat_msg.msg, "%s", "我是李傻春");
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
        }break;
        case '6': {
            sprintf(chat_msg.msg, "%s", "请叫我陈狗der");
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
        }break; 
        case '@': {
            /*nocbreak();
            char buff[512] = {0};
            mvwscanw(wwrite, 1, 2, buff);
            sprintf(chat_msg.msg, "%s", buff);
            send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
            cbreak();*/
        }break; 
    }
    //wclear(wwrite);
    w_gotoxy_puts(wwrite, 1, 1, "                  ");
    box(wwrite, 0, 0);
    wrefresh(wwrite);
    noecho();
}
