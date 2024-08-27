#include "controller.h"


cl_entry_t create_cl_entry(path_t path){

    struct cl_entry_t cle;
    char hash[HASH_SIZE_HEX];
    get_file_hash(path, hash);
    strcpy(cle.hash, hash);

    // suppose abolute file path are given
    strcpy(cle.path, path);
    cle.path[PATH_MAX -1] = '\0';
    cle.hash[HASH_SIZE_HEX -1] = '\0';

    syslog(LOG_DEBUG, "NEW ENTRY: \nHash: %s \nPath: %s", cle.hash, cle.path);
    return cle;
}




int add_cl_entry(path_t path, FILE * control_list){

    // checking aren't entry already exsits

    if (check_cl_entry(path, control_list)){
        printf("Entry already exists\n");
        return 0;
    }



    syslog(LOG_DEBUG, "Creating entry for %s", path);
    cl_entry_t entry = create_cl_entry(path);
    //printf("hash is: %s\n", hexhash);
    //printf("path is: %s\n", entry.path);


    char str_entry[MAX_ENTRY_SIZE] = "";

    sprintf(str_entry, "%s %s\n", entry.hash, entry.path);


    fputs(str_entry, control_list);
    syslog(LOG_DEBUG, "Entry created");

    return 0;
}

bool get_cl_entry(path_t _path, FILE * control_list, cl_entry_t *cle){

    char path[PATH_MAX];
    realpath(_path, path);

    cl_entry_t _cle;

    char buffer[MAX_ENTRY_SIZE];

    while (fgets(buffer, sizeof(buffer), control_list) != NULL) {


        char entry_path[PATH_MAX];
        strncpy(entry_path, buffer + HASH_SIZE_HEX + 1, PATH_MAX);
        entry_path[strlen(entry_path) - 1] = '\0';

        char entry_hash[HASH_SIZE_HEX];
        strncpy(entry_hash, buffer, HASH_SIZE_HEX -0);
        entry_hash[strlen(entry_hash)] = '\0';


        entry_path[PATH_MAX -1] = '\0';
        entry_hash[HASH_SIZE_HEX -1] = '\0';

        /*
        syslog(LOG_DEBUG, "\n\n\n");
        syslog(LOG_DEBUG, "BUFFER -%s- ", buffer);
        syslog(LOG_DEBUG, "HASH   -%s- ", entry_hash);
        syslog(LOG_DEBUG, "PATH   -%s- ", entry_path);
        syslog(LOG_DEBUG, "\n\n\n");
        */


        if (strcmp(entry_path, path) == 0){
            syslog(LOG_DEBUG, "Found %s in control list", path);


            strcpy(_cle.hash, entry_hash);
            strcpy(_cle.path, entry_path);

            *cle = _cle;

            return true;

        }


    }
    syslog(LOG_DEBUG, "Not found %s in control list", path);
    return false;

}

bool check_cl_entry(path_t path, FILE * control_list){

    syslog(LOG_DEBUG, "Checking path %s in control list", path);



    cl_entry_t cle;

    return get_cl_entry(path, control_list, &cle);

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
