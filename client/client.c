/*************************************************************************
        > File Name: client.c
        > Author: ZHJ
        > Remarks:
        > Created Time: Tue 07 Dec 2021 06:13:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>//selcet
#include<unistd.h>//uni std
#include<string.h>

#define SOCKET int
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)

int main()
{
    //获取数据
    system("/usr/bin/bash /home/pi/Weather-Pi/getData.sh > /home/pi/temp");
    sleep(5);

    //建立一个socket
    SOCKET _mysocket = socket(AF_INET,SOCK_STREAM,0);//IPV4 数据流类型 类型可以不用写
    if(INVALID_SOCKET == _mysocket)//建立失败
    {
        printf("socket error\n");
        return 0;
    }

    //连接服务器
    int host = 8888;
    struct sockaddr_in _sin = {};//sockaddr结构体
    _sin.sin_family = AF_INET;//IPV4
    _sin.sin_port = htons(host);//想要连接的端口号
    _sin.sin_addr.s_addr =  inet_addr("x.x.x.x");//想要连接的IP

    if(SOCKET_ERROR == connect(_mysocket,(struct sockaddr*)&_sin,sizeof(struct sockaddr_in)))
    {
        printf("connect error\n");
        //关闭socket/LINUX
        close(_mysocket);
    }
    else
    {
        printf("connect success\n");
    }
    char line[30];
    FILE* fp=fopen("/home/pi/temp", "r");
    if(fp == NULL)
    {
        return 0;
    }
    int i = 0;
    while (i < 3)
    {
        fgets(line, 30, fp);
        //printf("%s", line);
        send(_mysocket, line, strlen(line) + 1, 0);//客户端套接字 数据 数据长短 flag
        i++;
        sleep(1);
    }
    sleep(2);
    fclose(fp);
    //关闭socket/LINUX
    close(_mysocket);

    return 0;
}

