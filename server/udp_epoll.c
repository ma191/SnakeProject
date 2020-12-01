/*************************************************************************
	> File Name: udp_epoll.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月19日 星期四 16时55分54秒
 ************************************************************************/

#include "snake.h"

#define MAX 50
extern User *user;
extern int user_epollfd;
extern SnakeMsg msg;
extern pthread_mutex_t mutex;
void add_event(int epoll_fd, int fd, int events) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
}

void add_event_ptr(int epoll_fd, int fd, int events, User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
}


void del_event(int epoll_fd, int fd){
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
}

int udp_create_sock(int port) {
    int sockfd_udp;
    
    char msg[512] = {0};
    //创建套接字
    if ((sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("udp socket error");
        exit(1);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("192.168.2.63");
    
    int opt = 1;
    setsockopt(sockfd_udp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
   
    int flag = fcntl(sockfd_udp, F_GETFL);
    flag | O_NONBLOCK;
    fcntl(sockfd_udp, F_SETFL, flag);
    int ret_bind = bind(sockfd_udp, (struct sockaddr *)&server, sizeof(server));
    if (ret_bind < 0) {
        perror("udp bind");
        exit(1);
    }

    return sockfd_udp;

}

int udp_connect (int epoll_fd, struct sockaddr_in *server) {
    int sockfd;
    
    if((sockfd = udp_create_sock(9999)) < 0) {
        perror("udp sockfd error");
        exit(1);
    }
    if(connect(sockfd, (struct sockaddr *)server, sizeof(struct sockaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    //printf("%s连接\n", user->name);
    //add_event(epoll_fd, sockfd, EPOLLIN);
    return sockfd;
}

int check_flag(LogResquest *request) {
    for (int i = 0; i < MAX; i++) {
        if (user[i].flag && !strcmp(user[i].name, request->name)) return 1;
    }
    return 0;
}

int udp_accept(int epoll_fd, int fd, User *user) {
    struct sockaddr_in client;
    int new_fd, ret;
    LogResquest resquest;
    LogResponse response;

    bzero(&resquest, sizeof(resquest));
    bzero(&response, sizeof(response));
    socklen_t len = sizeof(client);
    ret = recvfrom(fd, (void *)&resquest, sizeof(resquest), 0, 
    (struct sockaddr *)&client, &len);
    if (ret != sizeof(resquest)) {
        response.type = 1;
        strcpy(response.msg, "Login failed With NetWork");
        sendto(fd, (void *)&response, sizeof(response), 0, 
        (struct sockaddr *)&client, sizeof(client));
        return -1;
    }

    if (check_flag(&resquest)) {
        response.type = 1;
        strcpy(response.msg, "You Are Alreadly Play This Game SomeWhere");
        sendto(fd, (void *)&response, sizeof(response), 0, 
        (struct sockaddr *)&client, sizeof(client));
    }

    response.type = 0;
    strcpy(response.msg, "Login success");
    strcpy(user->name, resquest.name);
    new_fd = udp_connect(epoll_fd, (struct sockaddr_in *)&client);
    user->fd = new_fd;
    sendto(new_fd, (void *)&response, sizeof(response), 0, 
    (struct sockaddr *)&client, sizeof(client));
    return new_fd;
}


int find_sub() {
    for (int i = 0; i < MAX; i++) {
        if(!user[i].flag) return i;
    }
    return -1;
}

int add_to_sub(User *luser) {
    int sub = find_sub();
    user[sub] = *luser;
    user[sub].flag = 1;
    user[sub].time = 10;
    init_snake(&user[sub].snake);
    msg.user[sub] = user[sub];
    msg.user[sub].snake = user[sub].snake;
    msg.cnt = sub;
    pthread_t pid;
    strcpy(msg.score[sub].name, user[sub].name);
    //printf("%s\n", user[sub].fd);
    add_event_ptr(user_epollfd, user[sub].fd, EPOLLIN, &user[sub]); 
    return sub;
}

