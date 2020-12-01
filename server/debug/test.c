/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2020年11月18日 星期三 19时35分59秒
 ************************************************************************/

#include <stdio.h>
#include "snake.h"
int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("port ????\n");
        exit(1);
    }
    int port = atoi(argv[1]);
    int sockfd = socket_create_udp(port);

    if (sockfd < 0) {
        perror("udp create");
        exit(1);
    }
    
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    
    socklen_t len = sizeof(client);
    while(1) {
        char buff[512] = {0};
        if ((recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&client, &len) < 0)) {
            perror("recvfrom()");
            exit(1);
        } else {
            printf("[%s]\n", inet_ntoa(client.sin_addr));
            printf("%s\n", buff);
        }
    }
    return 0;
}
