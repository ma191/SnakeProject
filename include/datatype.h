/*************************************************************************
	> File Name: type.h
	> Author: 
	> Mail: 
	> Created Time: 2020年11月20日 星期五 11时59分21秒
 ************************************************************************/

#ifndef _TYPE_H
#define SNAKE_MAX 1000

#define USER_MAX 100
#define UP 'w'
#define DOWN 's'
#define LIFT 'a'
#define RIGHT 'd'
#define SNAKE_SIZE 10

#define LINES 100
#define COLS 30

#define MAXMSG 1024

WINDOW *wsnake, *wmessage, *wscore, *wwrite;

typedef struct LogResquest{
    char name[20];
    char msg[512];
}LogResquest;

typedef struct LogResponse {
    int type; //0 success 1 failed
    char msg[512];
}LogResponse;

typedef struct Point{
    int x;
    int y;
    //int type;
}Point;

typedef struct Ctrl {
    int carry;
    int kick;
}Ctrl;


#define _TYPE_H
typedef struct Snake {
    List *l;
    Point point[100];
    int snake_len;
    int fraction;
    int die;
    char key;
}Snake;



typedef struct User {
    Snake snake;
    Point head;
    Point tail;
    int fd;
    char name[25];
    //响应时间
    int time;
    pthread_t pid;
    struct sockaddr_in addr;
    int flag;//是否在线
    int cnt;
}User;


typedef struct Score {
    char name[25];
    int type;
}Score;
#define FT_TEST 0x01 //服务的心跳
#define FT_WALL 0x02 //广播游戏情况
#define FT_MSG 0x04 //服务的转发的信息
#define FT_ACK 0x08 //客户端对心跳AKC确认
#define FT_FIN 0x10 //服务的下线前， 对彼此的告知
#define FT_CTL 0x20 //客户端发送的控制信息json发送
#define FT_GAME 0x40 //服务端向客户端广播游戏画面 json发送
#define FT_S 0x80 
#define FT_GAMEOVER //游戏结束



typedef struct SnakeMsg {
    Point food[10];
    int type;
    int size;
    char key;
    char msg[MAXMSG]; 
    char name[20];
    User user[50];
    int cnt;
    Score score[50];
    int die[50];
}SnakeMsg;

#endif
