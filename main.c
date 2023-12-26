#include "wasc.h"

int main(int argc, char *argv[]) {


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
