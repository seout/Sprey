#include "wasc.h"


int inside(struct infoip * ip) {

    char *header = HEADER;
    char buff[1024];
    int sock, sendmsg, result, status, flags, temp;
    socklen_t strsize;
    struct sockaddr_in configuration;

    fd_set wset;

    configuration.sin_addr.s_addr = inet_addr(ip->addr);
    configuration.sin_port        = htons(ip->port);
    configuration.sin_family      = AF_INET;

    strsize = sizeof configuration;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket");
        return -1;
    }

    flags = fcntl(sock,F_GETFL);

    if (flags >= 0)
        flags = fcntl(sock, F_SETFL, O_NONBLOCK);


    status = connect(sock, (struct sockaddr *)&configuration, strsize);


    FD_ZERO(&wset);
    FD_SET(sock,&wset);

    temp = write(sock, header, 1024);

    temp = read(sock, &buff, 1024);

    if (errno != EINPROGRESS && errno != EWOULDBLOCK)
        return 1;

    if (status < 0) {

        struct timeval tv;

        tv.tv_sec = 0;
        tv.tv_usec = 70000;

        result = select(sock + 1,NULL,&wset,NULL,&tv);

        if (!result) {
            printf("\033[031m The %s is'nt responding: [Error]\n", ip->addr);
            close(sock);
            return -1;
        }
    }
    printf("\033[032m 64 bytes %s: 200 [+] \n", ip->addr);

    close(sock);

    return 0;
}

int getprm(int argc, char *argv[], struct infoip *config) {

    for (int countl = 0;countl < argc; countl++) {

        if (!strcmp(argv[countl], "-h")) {
            config->addr = argv[countl+1];
        }
        if (!strcmp(argv[countl], "-p")) {
            config->port = atoi(argv[countl+1]);
        }
        if (!strcmp(argv[countl], "-t")) {
            config->thread = atoi(argv[countl+1]);
        }
    }

    return 0;
}

int splithread(struct infoip *ip) {

    int numthr = ip->thread;

    pthread_t num[numthr];

    while (1)
        for (int i = 0; i < numthr; i++) {
            if (pthread_create(&num[i], NULL, (void *)&inside, &(*ip)) != 0) {
                pthread_detach(num[i]);
                break;
            }

//            pthread_join(num[i], 0);
        }

    return 0;
}
