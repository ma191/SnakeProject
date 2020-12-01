/*************************************************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月21日 星期六 19时12分00秒
 ************************************************************************/

#include "snake.h"

#define MAX 50
extern pthread_mutex_t mutex;
extern User *user;
extern int user_epollfd;
void do_echo(User *luser) {
    SnakeMsg msg;
    char tmp[512] = {0};
    bzero(tmp, sizeof(tmp));
    int size = recv(user->fd, (void *)&msg, sizeof(msg), 0);
    user->time = 10;
    //pthread_mutex_lock(&mutex);
    if (msg.type & FT_ACK) {
        //printf("%s:❤\n", user->name);
        //show_message(wmessage, user, msg.msg, 1);
    } else if (msg.type & (FT_MSG | FT_WALL)) {
        //pthread_mutex_lock(&mutex);
        printf("%s:%s\n", user->name, msg.msg);
        strcpy(msg.name, user->name);
        show_message(wmessage, user, msg.msg, 0);
        for(int i = 0; i < MAX; i++) {
            if(!user[i].flag)continue;
            send(user[i].fd, (void *)&msg, sizeof(msg), 0);
        }
    
    } else if (msg.type & FT_FIN) {
        sprintf(tmp, "%s Logout.", user->name);
        //show_message(wmessage, user, tmp, 1);
        user->flag = 0;
        //printf("%s客户端关闭\n", user->name);
        del_event(user_epollfd, user->fd);
    } else if (msg.type & FT_CTL) {
        keydown(msg.key, user);
    }
    //pthread_mutex_unlock(&mutex);
}

void task_queue_init(task_queue *task, int sum, int epollfd) {
    task->sum = sum;
    task->epollfd = epollfd;
    task->user = calloc(sum, sizeof(void *));
    task->head = task->tail = 0;
    pthread_mutex_init(&task->mutex, NULL);
    pthread_cond_init(&task->cond, NULL);
}

void task_queue_push(task_queue *task, User *user) {
    pthread_mutex_lock(&task->mutex);
    task->user[task->tail] = user;

    if (++task->tail == task->sum) {
        task->tail = 0;
    }
    pthread_cond_signal(&task->cond);
    pthread_mutex_unlock(&task->mutex);
}

User *task_queue_pop(task_queue *task) {
    pthread_mutex_lock(&task->mutex);
    while (task->tail == task->head) {
        pthread_cond_wait(&task->cond, &task->mutex); 

    }
    
    User *user = task->user[task->head];
    if (++task->head == task->sum) {
        //printf("head\n");
        task->head = 0;
    }
    pthread_mutex_unlock(&task->mutex);
    return user;
}

void *thread_run(void *arg) {
    pthread_t tid = pthread_self();
    pthread_detach(tid);
    task_queue *task = (task_queue *)arg;

    while(1) {
        User *user = task_queue_pop(task);
        do_echo(user);
    }
}
