/*************************************************************************
	> File Name: snake_server.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 21时31分23秒
 ************************************************************************/

#include <stdio.h>
#include "snake.h"

//用户列表
User *user;
int user_epollfd;
int sub;
#define DATA_PORT  9999
#define MAX 50

SnakeMsg msg;
pthread_mutex_t mutex;
int main(int argc, char **argv) {
    
    pthread_t pid, sub_t, heart_t, draw_t, move_t, send_client_t;
    int port ,listener;
   
    srand(time(NULL));
    //创建用户队列
    user = (User *)calloc(USER_MAX, sizeof(User));
    for (int i = 0; i < USER_MAX; i++) user[i].flag = 0;
    
    if (argc != 2) {
        printf("port ???\n");
        exit(1);
    }
    
    port = atoi(argv[1]);
    listener = socket_create_udp(port);
    if (listener < 0) {
        perror("socket_create_udp error???");
        exit(1);
    }
    
    pthread_mutex_init(&mutex, NULL);
    struct sockaddr_in client, server;
    socklen_t len = sizeof(client);

    //创建epoll句柄
    int epoll_fd = epoll_create(100);
    user_epollfd = epoll_create(100);
    //int flag = fcntl(F_FGET_FL, flag);
    if ((epoll_fd < 0) || (user_epollfd < 0)) {
        perror("epoll_create error");
        exit(1);
    }
    //y用户队列
    task_queue task;

    //初始化框框
    initsnake(); 
    //初始化
    task_queue_init(&task, MAX, user_epollfd);
    //创建从反应堆
    pthread_create(&sub_t, NULL, sub_reactor, (void *)&task);
    //心跳线程
    pthread_create(&heart_t, NULL, heart_beat, NULL);
    //发送画面
    pthread_create(&send_client_t, NULL, send_client, NULL);
    //画食物
    pthread_t food_t;
    pthread_create(&food_t, NULL, draw_food, NULL);
    //吃食物
    pthread_t ear_t;
    //pthread_create(&ear_t, NULL, eat_food, NULL);
    pthread_t score_t;
    pthread_create(&score_t, NULL, send_score, NULL);
    struct epoll_event ev, events[USER_MAX];
    ev.data.fd = listener;
    ev.events = EPOLLIN;

    signal(SIGINT, server_exit);
    signal(14, re_draw);
    
    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 300000;
    itimer.it_value.tv_sec = 2;
    itimer.it_value.tv_usec = 0;
    
    setitimer(ITIMER_REAL, &itimer, NULL);

    LogResquest request;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener, &ev);
    //无限死循环
    while (1) {
        User luser;
        char buff[1024];
        //返回发生的时间总数
        int nfds = epoll_wait(epoll_fd, events, USER_MAX, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == listener) {
                int newfd = udp_accept(epoll_fd, listener, &luser);
                if (newfd > 0) {
                    sprintf(buff, "%s login the Game.", luser.name);
                    //pthread_mutex_lock(&mutex);
                    sub = add_to_sub(&luser);
                    //pthread_mutex_unlock(&mutex);
                    show_message(wmessage, &luser, buff, 1);
                }
            } 
        }
    }
    return 0;
}

