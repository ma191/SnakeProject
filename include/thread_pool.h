/*************************************************************************
	> File Name: thread_pool.h
	> Author: 
	> Mail: 
	> Created Time: 2020年11月21日 星期六 19时13分29秒
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include "snake.h"

#define MAXTAASK 100
#define MAXTHREAD 10

typedef struct task_queue {
    int sum;
    int epollfd;
    User **user;
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}task_queue;

void task_queue_init(task_queue *task, int sum, int epollfd);

void task_queue_push(task_queue *task, User *user);
User *task_queue_pop(task_queue *task);
void *thread_run(void *arg);
#endif
