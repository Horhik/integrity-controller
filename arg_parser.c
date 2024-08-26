#include "controller.h"


args_t parse_args(int argc, char **argv){

    // TODO write function
    args_t res;
    res.to_inspect = false;
    res.to_regist  = true;
    res.path = "/tmp/popa.txt";

    return res;
}

bool path_is_correct(char * path){

    // TODO write function
    return true;
}
