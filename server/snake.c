/*************************************************************************
	> File Name: snake.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 11时57分51秒
 ************************************************************************/

//#include <curses.h>
//#include "list.h"
//#include <pthread.h>
#include "snake.h"

int g = 10;
extern pthread_mutex_t mutex;
int message_num = 1;
extern SnakeMsg msg;
extern int user_epollfd;
void init_snake(Snake *snake) {
    //初始化链表
    snake->l = init();
    //初始坐标
    insert(snake->l, 1, 1);
    snake->l->tail = snake->l->head;

    //蛇的初始长度
    snake->snake_len = 1;
    //分数
    snake->fraction = 0;
    //是否死亡
    snake->die = 0;
    //蛇的方向
    snake->key = RIGHT;
}
//移动蛇的位置
void *snake_move(void *arg, int i) {
    //pthread_mutex_lock(&mutex);
    User *user = (User *)arg;
 	w_gotoxy_putc(wsnake, user->snake.l->tail->x, user->snake.l->tail->y, ' ');
    pop(user->snake.l);
    insert(user->snake.l, user->snake.l->head->x, user->snake.l->head->y);
    w_gotoxy_putc(wsnake, user->snake.l->head->x, user->snake.l->head->y, 'o');

    if (user->snake.l->head->x == COLS - 1) {
        user->snake.die = 1;
        msg.die[i] = 1;
    }
    if (user->snake.l->head->y == LINES - 1) {
        user->snake.die = 1;
        msg.die[i] = 1;
    }
    if (user->snake.l->head->x == 0) {
        user->snake.die = 1;
        msg.die[i] = 1;
    }
    if (user->snake.l->head->y == 0) {
        user->snake.die = 1;
        msg.die[i] = 1;
    }
    switch(user->snake.key) {
        case RIGHT :{
            user->snake.l->head->x += 1;
        } break;
        case LIFT :{
            user->snake.l->head->x -= 1;
        } break;
        case UP: {
            user->snake.l->head->y -= 1;
        } break;
        case DOWN:{
            user->snake.l->head->y += 1;
        }break;
    }
    msg.user[i].tail.x = user->snake.l->tail->x;
    msg.user[i].tail.y = user->snake.l->tail->y;
    msg.user[i].head.y = user->snake.l->head->y;
    msg.user[i].head.x = user->snake.l->head->x;
    for (int i = 0; i < 10; i++) {
        if(msg.food[i].x == user->snake.l->head->x && msg.food[i].y == user->snake.l->head->y) {
            insert(user->snake.l, user->snake.l->head->x, user->snake.l->head->y);
            msg.food[i].x = rand() % 69 + 1;
            msg.food[i].y = rand() % 29 + 1;
            user->snake.fraction++;
            msg.score[i].type = user->snake.fraction;
            char score[5] = {0};
            sprintf(score, "%d", user->snake.fraction);
            w_gotoxy_puts(wscore, 5, 5, score);
            w_gotoxy_putc(wsnake, msg.food[i].x, msg.food[i].y, '1');
        }
    }
    //pthread_mutex_unlock(&mutex);
    return NULL;
}


WINDOW *create_newwin(int width, int height, int startx, int starty) {
    WINDOW *win;
    win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, int c) {
    move(y, x);
    addch(c);
    move(LINES - 1, 1);
    refresh();
}

void gotoxy_puts(int x, int y, char* s) {
    move(y, x);
    addstr(s);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, int c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
}
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
}

void initsnake() {
    initscr();
    clear();
    if (!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色\n");
        exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

    wsnake = create_newwin(LINES, COLS, 0, 0);
    wmessage = create_newwin(LINES, 8, 0, COLS);
    //scrollok(wmessage, 1);
    wscore = create_newwin(20, COLS + 13, LINES, 0);
    wwrite = create_newwin(LINES, 5, 0, COLS + 8);
}
void *draw(void *arg) {
    initsnake();
    while(1) {
        sleep(10);
    }
}

void show_message(WINDOW *win, User *user, char *msg, int type) {
    time_t time_now = time(NULL);
    struct tm *tm = localtime(&time_now);
    char timestr[20] = {0};
    char username[20] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    //pthread_mutex_lock(&mutex);
    if (type) {
        wattron(win, COLOR_PAIR(4));
        strcpy(username, "Server Info : ");
    } else {
        wattron(win, COLOR_PAIR(6));
        sprintf(username, "%s : ", user->name);
    }

    if (message_num < 7) {
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
        message_num++;
    } else {
        message_num = 4;
        scroll(win);
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
        message_num++;
    }
   // epthread_mutex_unlock(&mutex);
    wrefresh(win);
}

void keydown(char key, User *user) { 
    if(key == UP) user->snake.key = UP;
    if(key == DOWN) user->snake.key = DOWN;
    if(key == LIFT) user->snake.key = LIFT;
    if(key == RIGHT) user->snake.key = RIGHT;
}

