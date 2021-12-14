/*************************************************************************
	> File Name: server.c
	> Author: ZHJ
	> Remarks: 
	> Created Time: Tue 07 Dec 2021 05:54:52 PM CST
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
	//建立一个socket
	SOCKET _mysocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//IPV4 数据流类型 TCP类型
	if(INVALID_SOCKET == _mysocket)//建立失败
    {
        return 0;
    }

	//绑定网络端口和IP地址
    int host = 8888;
	struct sockaddr_in _myaddr = {};//建立sockaddr结构体  sockaddr_in结构体方便填写 但是下面要进行类型转换
	_myaddr.sin_family = AF_INET;//IPV4
	_myaddr.sin_port = htons(host);//端口 host to net unsigned short
	_myaddr.sin_addr.s_addr = INADDR_ANY;//想要监听的ip

	if(SOCKET_ERROR == bind(_mysocket,(struct sockaddr*)&_myaddr,sizeof(struct sockaddr_in)))//socket (强制转换)sockaddr结构体 结构体大小
	{
		printf("bind %d error\n", host);
	}
	else
	{
		printf("bind %d success\n", host);
	}

	//监听网络端口
	if(SOCKET_ERROR == listen(_mysocket,5))//套接字 最大多少人连接
	{
		printf("listen error\n");
	}
	else
	{
		printf("listen success\n");
	}

	while(1)
	{
        struct sockaddr_in _clientAddr = {};//新建sockadd结构体接收客户端数据
		int _addr_len = sizeof(struct sockaddr_in);//获取sockadd结构体长度
		SOCKET _temp_socket = INVALID_SOCKET;//声明客户端套接字

		_temp_socket = accept(_mysocket,(struct sockaddr*)&_clientAddr,(socklen_t*)&_addr_len);//自身套接字 客户端结构体 结构体大小

		if(INVALID_SOCKET == _temp_socket)//接收失败
		{
			printf("Socket error");
		}
		else
        {
            printf("new client join - IP: %s \n", inet_ntoa(_clientAddr.sin_addr));
            //接收数据操作   
            //接收客户端发送的数据 
            char _buf[256] = {};
            int _buf_len, i;
            FILE* fp = fopen("/var/www/html/index.html", "w");
            fputs("<h1>\n<font size=\"20\">", fp);
            for(i = 0; i < 4; ++i)
            {
                _buf_len= recv(_temp_socket, _buf, 256, 0);
                if(_buf_len > 0)
                {
                    fputs(_buf, fp);
                    fputs("\n</br>", fp);
                    //printf("%s", _buf);
                }
                //fflush(stdout);
                sleep(1);
            }
            fputs("</font>\n</h1>", fp);
            fclose(fp);
            sleep(2);
            //关闭客户端socket
            printf("new client close - IP: %s \n", inet_ntoa(_clientAddr.sin_addr));
            close(_temp_socket);
        }
	}


	//关闭socket/LINUX
	close(_mysocket);


	printf("任务结束，程序已退出");

	getchar();

	return 0;
}

