#include "socketserver.h"

int m_listenSocket = -1;
int m_bindSocket = -1;

void accept_process();

void start_tcp_server()
{
    //socket()
    m_listenSocket = socket(AF_INET,SOCK_STREAM,0);

    if(m_listenSocket < 0){
        close(m_listenSocket);
        m_listenSocket = -1;
        return;
    }

    struct sockaddr_in client_addr;

    bzero(&client_addr,sizeof(struct sockaddr_in));

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(LISTEN_PORT);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind();
    int nRet = bind(m_listenSocket,(struct sockaddr *)&client_addr,sizeof(client_addr));

    if(nRet < 0){
        close(m_listenSocket);
        m_listenSocket = -1;
        return;
    }

    //listen()
    nRet = listen(m_listenSocket,20);
    if(nRet < 0){
        close(m_listenSocket);
        m_listenSocket = -1;
        return;
    }

    accept_process();
}

void accept_process()
{
    struct sockaddr_in peerInAddr;
    socklen_t size;
    pid_t pid;

    while(1){
        size = sizeof(struct sockaddr_in);
        m_bindSocket = accept(m_listenSocket,(struct sockaddr *)&peerInAddr,&size);
        puts("喵呜");
        if(m_bindSocket > 0){
            //链接成功
            puts("success");
            //处理数据，收发数据


            pid = fork();
            if(pid == 0){
                //创建子进程成功
                close(m_listenSocket);
                //do_process();
                close(m_bindSocket);
                exit(0);
            }


        }
        close(m_bindSocket);

        usleep(2000 * 1000);
    }
}
