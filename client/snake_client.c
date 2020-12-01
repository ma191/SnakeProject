/*************************************************************************
    B
	> File Name: snake_client.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 21时29分46秒
 ************************************************************************/

#include "snake.h"

int sockfd;
pthread_mutex_t mutex;
SnakeMsg msg;
void logout(int signum) {
    SnakeMsg msg;
    msg.type = FT_FIN;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    endwin();
    exit(1);
}

//SnakeMsg chat_msg;
SnakeMsg ctl_msg;
int main(int argc, char **argv) {
    /*if (argc != 3) {
        printf("ip port ???");
        exit(1);
    }*/
    //char *ip = argv[1];
    //int port = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    setlocale(LC_ALL, "");
    pthread_mutex_init(&mutex, NULL);
    if (sockfd < 0) {
        perror("socket error");
        exit(1);
    }
    //bzero(&chat_msg, sizeof(SnakeMsg));
    bzero(&ctl_msg, sizeof(SnakeMsg));

    //chat_msg.type = FT_MSG;
    ctl_msg.type = FT_CTL;

    signal(SIGINT, logout);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("192.168.2.63");
    
    LogResquest resquest;
    LogResponse response;

    bzero(&resquest, sizeof(resquest));
    bzero(&response, sizeof(response));

    socklen_t len = sizeof(server);
    strcpy(resquest.name, "l c");
    sendto(sockfd, (void *)&resquest, sizeof(resquest), 0, (struct sockaddr *)&server, sizeof(server));
    
    
    //设置超时时间防止recvfrom阻塞

    fd_set set;
    FD_ZERO(&set);
    FD_SET(sockfd, &set);
    
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    
    snake_login();
    int retval = select(sockfd + 1, &set, NULL, NULL, &tv);
    if (retval < 0) {
        perror("select");
        exit(1);
    } else if (retval) {
        int recv_ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
        if ( (recv_ret != sizeof(response)) || response.type ) {
            printf("RED ERROR");
            printf(":%s\n", response.msg);
            exit(1);
        }
    } else {
        printf("超时\n");
    }
    int ret = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (ret < 0) {
        perror("connect");
        exit(1);
    }
    //读线程
    pthread_t draw_t, recv_x;
    pthread_create(&recv_x, NULL, recv_file, NULL);
    //绘画线程
    

    signal(14, send_ctl);
    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 40000;
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 10000;

    setitimer(ITIMER_REAL, &itimer, NULL);

    pthread_t draw_snake_t;
    //pthread_create(&draw_snake_t, NULL, draw_snake, NULL);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1) {
        char c = getchar();
        switch (c) {
            case 'a' : {
                pthread_mutex_lock(&mutex);
                msg.type = FT_CTL;
                ctl_msg.key = c;
                pthread_mutex_unlock(&mutex);
            } break;
            case 's' : {
                pthread_mutex_lock(&mutex);
                msg.type = FT_CTL;
                ctl_msg.key = c;
                pthread_mutex_unlock(&mutex);
            } break;
            case 'w' : {
                pthread_mutex_lock(&mutex);
                msg.type = FT_CTL;
                ctl_msg.key = c;
                pthread_mutex_unlock(&mutex);
            } break;
            case 'd' : {
                pthread_mutex_lock(&mutex);
                msg.type = FT_CTL;
                ctl_msg.key = c;
                pthread_mutex_unlock(&mutex);
            } break;
            case ' ' : {
                msg.type = FT_CTL;
                ctl_msg.key = c;
            } break;
            case 13: {
                send_chat();
            } break;
            default:
                break;
        }

    }
    return 0;
}
