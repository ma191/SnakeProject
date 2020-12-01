/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: 2020年11月17日 星期二 17时38分03秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pwd.h>
#include <pthread.h>
#include <wait.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdarg.h>
#include <sys/epoll.h>
#include <errno.h>
#include <signal.h>

#ifndef _D
#define DBG(fmt, args...) printf(fmt, ##args);
#else 
#define DBG(fmt, args...);
#endif


#endif
