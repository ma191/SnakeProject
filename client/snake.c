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

extern pthread_mutex_t mutex;
int message_num = 1;
//移动蛇的位置
WINDOW *login;
void *snake_move(void *arg, int i) {
    User *user = (User *)arg;
    pthread_mutex_lock(&mutex);
    mvwprintw(wsnake, user->tail.y, user->tail.x, " ");
    wattron(wsnake, COLOR_PAIR(2));
    mvwprintw(wsnake, user->head.y, user->head.x, "0");
    wattron(wsnake, COLOR_PAIR(6));
    wrefresh(wsnake);
    pthread_mutex_unlock(&mutex);
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
void snake_login() {
    initscr();
    clear();
    login = create_newwin(50, 30, 1, 1);
    cbreak();
    w_gotoxy_puts(login, 1, 1, "登录请按y");
    w_gotoxy_puts(login, 1, 2, "退出请按n");
    char c = getchar();
    switch(c) {
        case 'y' : {
            initsnake();
        } break;
        case 'n' : {
            endwin();
            exit(1);
        } break;
    }
}

void show_message(WINDOW *win, User *user, char *msg, int type) {
    pthread_mutex_lock(&mutex);
    time_t time_now = time(NULL);
    struct tm *tm = localtime(&time_now);
    char timestr[20] = {0};
    char username[20] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);

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
    pthread_mutex_unlock(&mutex);
    wrefresh(win);
}
void keydown(char key, User *user) { 
    if(key == UP) user->snake.key = UP;
    if(key == DOWN) user->snake.key = DOWN;
    if(key == LIFT) user->snake.key = LIFT;
    if(key == RIGHT) user->snake.key = RIGHT;
}

