/*************************************************************************
	> File Name: send_ctl.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月23日 星期一 18时57分07秒
 ************************************************************************/

#include "snake.h"

extern int sockfd;
extern SnakeMsg ctl_msg;
void send_ctl() {
    if (ctl_msg.key) 
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
}
