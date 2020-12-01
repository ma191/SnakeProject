/*************************************************************************
	> File Name: udp_epoll.h
	> Author: 
	> Mail: 
	> Created Time: 2020年11月19日 星期四 17时21分34秒
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H
#include "snake.h"

int udp_accept(int epoll_fd, int fd, User *user);
int udp_create_sock(int port);
void add_event(int epoll_fd, int fd, int events);
void add_event_ptr(int epoll_fd, int fd, int events, User *user);
void del_event(int epoll_fd, int fd);
int udp_connect(int epoll_fd, struct sockaddr_in *server);
int add_to_sub(User *luser);
int check_flag(LogResquest *request);

#endif
