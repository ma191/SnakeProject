/*************************************************************************
	> File Name: udp_server.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 19时50分16秒
 ************************************************************************/

#include "snake.h"

int socket_create_udp(int port) {
    int sockfd_udp;

    //创建套接字
    if ((sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("udp socket error");
        exit(1);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("192.168.2.63");

    int ret_bind = bind(sockfd_udp, (struct sockaddr *)&server, sizeof(server));
    if (ret_bind < 0) {
        perror("udp bind");
        exit(1);
    }
    return sockfd_udp;
}
