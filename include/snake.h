/*************************************************************************
	> File Name: snake.h
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 11时57分13秒
 ************************************************************************/

#ifndef _SNAKE_H
#define _SNAKE_H

#include "head.h"
#include <curses.h>
#include "list.h"
#include <pthread.h>
#include "snake.h"
#include "datatype.h"
#include "udp_epoll.h"
#include "thread_pool.h"
#include "sub_reactor.h"
#include "heart.h"
#include "recv_file.h"
#include "server_exit.h"
#include "send_chat.h"
#include "send_ctl.h"
#include "re_draw.h"
#include "send_client.h"
#include "draw_snake.h"
#include "draw_food.h"
#include "eat_food.h"
#include "send_score.h"
#include <locale.h>

#define DEFARG(name, default_value) ((#name[0]) ? (name + 0) : default_value)

#define Show_Message(arg0, arg1, arg2, arg3) show_message(DEFARG(arg0, Message),  DEFARG(arg1, NULL), DEFARG(arg2, NULL), DEFARG(arg3, 0))


void init_snake(Snake *snake);
void initsnake();
void *draw(void *arg);
int socket_create_udp(int port);
void *snake_move(void *arg, int i);
WINDOW *create_newwin(int width, int height, int startx, int starty);
void destroy_win(WINDOW *win);
void gotoxy_putc(int x, int y, int c);
void gotoxy_puts(int x, int y, char *s);
void w_gotoxy_putc(WINDOW *win, int x, int y, int c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char* s);
void show_message(WINDOW *win, User *user, char *msg, int type);
void keydown(char c, User *user);
void snake_login();


#endif
