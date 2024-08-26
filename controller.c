#include "controller.h"

bool control_list_avaliable(FILE * control_list){
    // TODO write function
    return true;
}



int control(args_t args){
    if (!path_is_correct(args.path)) {

        printf("\nIncorrect path!\n");
        return 1;

    }

    if (args.to_regist) return path_regist(args.path);

    if (args.to_inspect) return path_inspect(args.path);
    return 0;
}
