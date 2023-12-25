#include "wasc.h"

int main(int argc, char *argv[]) {
    argc = 4;
    argv[1] = "443";
    argv[2] = "1.1.1.1";
    argv[3] = "2";

    struct infoip configuration;

    /* Setting a params */

    if ((getprm(argc, argv, &configuration) != 0) || argc < 3) {

        perror("\033[031m\n");

        return -1;
    };

    if (splithread(&configuration) != 0) {

        perror("\033[031m\n");

        return -1;
    }

    return (0);
}