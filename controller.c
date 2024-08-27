#include "controller.h"


cl_entry_t create_cl_entry(path_t path){
    // TODO finish function
    struct cl_entry_t cle;
    get_file_hash(path, cle.hash);

    // suppose abolute file path are given
    strcpy(cle.path, path);

    return cle;
}




int add_cl_entry(path_t path, FILE * control_list){

    // checking aren't entry already exsits

    if (check_cl_entry(path, control_list)){
        printf("Entry already exists\n");
        return 0;
    }

    cl_entry_t entry = create_cl_entry(path);
    //printf("hash is: %s\n", hexhash);
    //printf("path is: %s\n", entry.path);


    char str_entry[MAX_ENTRY_SIZE] = "";

    sprintf(str_entry, "%s %s\n", entry.hash, entry.path);


    fputs(str_entry, control_list);

    return 0;
}

void get_cl_entry(path_t _path, FILE * control_list, cl_entry_t *cle){

    char path[PATH_MAX];
    realpath(_path, path);


    char buffer[MAX_ENTRY_SIZE];

    while (fgets(buffer, sizeof(buffer), control_list) != NULL) {


        char entry_path[PATH_MAX];
        strncpy(entry_path, buffer + HASH_SIZE_HEX + 1, PATH_MAX);
        entry_path[strlen(entry_path) - 1] = '\0';

        char entry_hash[HASH_SIZE_HEX];
        strncpy(entry_hash, buffer, HASH_SIZE_HEX);




        if (strcmp(entry_path, path) == 0){
            syslog(LOG_DEBUG, "Found %s in control list", path);


            strcpy(cle -> hash, entry_hash);
            strcpy(cle->path, entry_path);

            return;

        }


    }
    syslog(LOG_DEBUG, "No found %s in control list", path);
    cle = NULL;

}

bool check_cl_entry(path_t path, FILE * control_list){


    cl_entry_t *cle;
    get_cl_entry(path, control_list, cle);

    if (cle == NULL) return false;
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
    if(control_list) return true;
    return false;
}



int control(args_t args){

    syslog(LOG_INFO, "Parsing arguments");

    if (!path_is_correct(args.path)) {

        syslog(LOG_ERR, "Incorrect path");
        return 1;

    }

    if (args.to_regist) return path_regist(args.path);

    if (args.to_inspect) return path_inspect(args.path);

    return 0;
}
