#include "controller.h"



bool is_directory(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        // TODO SYSLOG
        return false; // Error occurred
    }
    return S_ISDIR(path_stat.st_mode);
}


int path_regist(char * path){
    // Opening file
    FILE * fp;
    fp = fopen(path, "r");

    // Checking are path correct
    if (fp == NULL) {

        printf("\nSmth is wrong with a path\n");
        return 1;
    }

    FILE * control_list;
    control_list = fopen(CONTROL_LIST_PATH, "a+");

    // Checking are control list are avaliable
    if (!control_list_avaliable(control_list)){

        printf("\nControl list %s is not avaliable", CONTROL_LIST_PATH);
        return 1;
    }

    // Checking are path already registered
    if (!check_cl_entry(path, control_list)){

        printf("\nPath already registered. \nNothing to do. \nExiting.\n");
        return 0;

    }

    // registrating path
    if (is_directory(path)){

    }



    fclose(fp);
    return 0;
}

int path_unregist(char * path){
    // TODO
    return 1;
}
