#include "wasc.h"

int inside(struct infoip * ip) {

    int sock, port, argv, result;

    char buff[64];

    char header[] = HEADER;

    socklen_t usize;

    struct sockaddr_in host;

            host.sin_addr.s_addr = inet_addr(ip->addr);
            host.sin_port        = htons(ip->port);
            host.sin_family      = AF_INET;

            usize = sizeof host;

    sock = socket(AF_INET, SOCK_STREAM, 0);


//    int flags = fcntl(sock,F_GETFL);

//    if (flags >= 0)
//        flags = fcntl(sock, F_SETFL, O_NONBLOCK);

    int status = connect(sock, (struct sockaddr *)&host, usize);


//    if (errno != EINPROGRESS && errno != EWOULDBLOCK)
//        return 1;

    result = write(sock, &header, sizeof header);

    result = read(sock, &buff, 64);

//
//    if (status < 0) {
//
//        struct timeval tv;
//
//        tv.tv_sec = 3;
//        tv.tv_usec = 0;
//
//        fd_set wset;
//
//        FD_ZERO(&wset);
//        FD_SET(sock,&wset);
//
//        status = select(sock + 1,NULL,&wset,NULL,&tv);
//
//        if (status) {
            printf("\033[032m 64 bytes %s: 200 [+] \n", ip->addr);
//            close(sock);
//
//            return 0;
//        } else {
//            printf("\033[031m The %s is'nt responding: [Error]\n", ip->addr);
//            close(sock);
//
//            return -1;
//        }
//    }

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

        inside(ip);
        pthread_t num[numthr];

//        for (int i = 0; i < numthr; i++) {
//            if (pthread_create(&num[i], NULL, (void *)&inside, &(*ip)) != 0) {
//                pthread_detach(num[i]);
//                continue;
//            } else {
//
//            }
//        }


    return 0;
}