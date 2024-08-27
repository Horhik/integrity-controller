#include "controller.h"


cl_entry_t create_cl_entry(path_t path){
    // TODO finish function
    cl_entry_t control_list_entry;
    return control_list_entry;
}

int add_cl_entry(path_t path, FILE * control_list){
    // TODO finish function
    return 0;
}

cl_entry_t get_cl_entry(path_t path, FILE * control_list){
    // TODO finish function
    cl_entry_t control_list_entry;
    return control_list_entry;
}

bool check_cl_entry(path_t path, FILE * control_list){
    // TODO finish function
    return true;
}

int modify_cl_entry(cl_entry_t entry, FILE * control_list){
    // TODO finish function
    return 0;
}

int delete_cl_entry(path_t path, FILE * control_list){
    // TODO finish function
    return 0;
}

// creating  control list file if it doesn't exist
int create_control_list(FILE * control_list){
    // TODO finish function
    return 0;
}




bool control_list_avaliable(FILE * control_list){
    // TODO write function
    return true;
}



int control(args_t args){

    syslog(LOG_INFO, "Parsing arguments");
    if (!path_is_correct(args.path)) {

        printf("\nIncorrect path!\n");
        return 1;

    }

    if (args.to_regist) return path_regist(args.path);

    if (args.to_inspect) return path_inspect(args.path);

    return 0;
}
