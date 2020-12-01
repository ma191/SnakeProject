/*************************************************************************
	> File Name: sub_reactor.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月20日 星期五 17时01分30秒
 ************************************************************************/

#include "snake.h"

#define MAX 50

extern int user_epollfd;
void *sub_reactor(void *arg) {
    task_queue *task = (task_queue *)arg;
    pthread_t *tid = (pthread_t *)calloc(MAXTHREAD, sizeof(pthread_t));

    for (int i = 0; i < 30; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)task);
    }
    struct epoll_event ev, events[MAX];
    while (1) {
        int nfds = epoll_wait(user_epollfd, events, MAX, -1);
        if (nfds < 0) {
            perror("epoll_wait");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            User *user = (User *)events[i].data.ptr;
            if (events[i].events & EPOLLIN) {
                task_queue_push(task, user);
            }
        }
    }
    return NULL;
}
