//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: GPLE/common.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-01
//  
//  Description: 通用头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>  
#include <stdbool.h>  
#include <stdint.h>  
#include <malloc.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <getopt.h>  
#include <fcntl.h>  
#include <ctype.h>  
#include <errno.h>  
#include <limits.h>  
#include <time.h> 
#include <locale.h>  
#include <signal.h>  
#include <pthread.h>

#include <sys/unistd.h>  
#include <sys/stat.h>  
#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <linux/fb.h>
#include <arpa/inet.h>

#include "libxml/xmlmemory.h"
#include "libxml/parser.h"
#include "jpeglib.h"

// 通用
int Open(const char *pathname, int flag);
ssize_t Read(int fildes, void *buf, size_t nbyte);
ssize_t Write(int fildes, const void *buf, size_t nbyte);

// 网络相关
#define DEF_PORT 54321
#define XMLSIZE  1024

int Socket(int domain, int type, int protocol);
int Setsockopt(int sockfd, int level, int optname,
	       const void *optval, socklen_t optlen);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);

int init_sock(const char *ubuntu_ip);
void send_pcm(int sockfd, char *pcmfile);
xmlChar *wait4id(int sockfd);

// 触摸屏相关
void wait4touch(void);

// XML相关
#define XMLFILE "result.xml"
xmlChar *parse_xml(char *xmlfile);

// 显示相关
void show_someone(char *FB, int id);
char *init_lcd(void);
char *get_rgb(char *filename);

void show_in (char *FB, char *filename);
void fade_out(char *FB, char *filename);

#define WIDTH  800
#define HEIGHT 480
#define SCREEN_SIZE WIDTH*HEIGHT
#define BLIND  5

enum motion{left, right, up, down, click};

struct argument
{
	unsigned long (*FB)[WIDTH];
	unsigned long (*image)[WIDTH];
	int offset;
	int flag;
};

// 定义了一个表示LCD一行宽度的数组指针类型
typedef unsigned long (*stride)[WIDTH];

#define IN  1
#define OUT 0


void blind_window_in(char *FB, stride image);
void blind_window_out(char *FB, stride image);
void blind_window(char *FB, stride image);

#endif