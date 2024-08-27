#include "controller.h"


cl_entry_t create_cl_entry(path_t path){

    struct cl_entry_t cle;
    char hash[HASH_SIZE_HEX];

    get_file_hash(path, hash);

    syslog(LOG_DEBUG, "FILE HASH:   %s ", hash);

    char * _path  = path;

    _path[PATH_MAX -1] = '\0';
    hash[HASH_SIZE_HEX -1] = '\0';

    strcpy(cle.hash, hash);
    strcpy(cle.path, _path);

    syslog(LOG_DEBUG, "NEW ENTRY: \nHash: %s \nPath: %s", cle.hash, cle.path);

    return cle;
}




int add_cl_entry(path_t path, FILE * control_list){

    // checking aren't entry already exsits


    cl_entry_t cle;
    cl_entry_t *p_cle = &cle;
    int cle_line = get_cl_entry(path, control_list, p_cle);

    if (cle_line != -1){


        char hash[HASH_SIZE_HEX];
        get_file_hash(path, hash);
        syslog(LOG_DEBUG, "FILE HASH:   %s ", hash);
        syslog(LOG_DEBUG, "STORED HASH: %s ", cle.hash);
        if (!match(hash, cle.hash)){

        printf("REregistrating entry: %s\n", path);

        /*fclose(control_list);
        FILE *fp = fopen(CONTROL_LIST_PATH, "r+");

        modify_cl_entry(path, entry_line, fp );

        fclose(fp);
        fp = fopen(CONTROL_LIST_PATH, "w");
        control_list = fp;
        */

        } else {
            printf("Path already registrated: %s\n", path);
        }
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
    printf("Entry registrated: %s\n", path);

    return 0;
}

int get_cl_entry(path_t _path, FILE * control_list, cl_entry_t *cle){

    char path[PATH_MAX];
    realpath(_path, path);

    cl_entry_t _cle;

    char buffer[MAX_ENTRY_SIZE];

    int line = 0;
    while (fgets(buffer, sizeof(buffer), control_list) != NULL) {


        char entry_path[PATH_MAX];
        strncpy(entry_path, buffer + HASH_SIZE_HEX, PATH_MAX);
        entry_path[strlen(entry_path) -1] = '\0';

        char entry_hash[HASH_SIZE_HEX];
        strncpy(entry_hash, buffer, HASH_SIZE_HEX -0);


        entry_path[PATH_MAX -1] = '\0';
        entry_hash[HASH_SIZE_HEX -1] = '\0';

        syslog(LOG_DEBUG, "\n\n\n");
        syslog(LOG_DEBUG, "BUFFER -%s- ", buffer);
        syslog(LOG_DEBUG, "HASH   -%s- ", entry_hash);
        syslog(LOG_DEBUG, "PATH   -%s- ", entry_path);
        syslog(LOG_DEBUG, "MY PATH   -%s- ", path);
        syslog(LOG_DEBUG, "MATCH   -%d- ", match(path, entry_path));
        syslog(LOG_DEBUG, "\n\n\n");


        if (strcmp(entry_path, path) == 0){
            syslog(LOG_DEBUG, "Found %s in control list", path);

            strcpy(_cle.hash, entry_hash);
            strcpy(_cle.path, entry_path);

            *cle = _cle;

            return line;

        }

        line++;
    }
    syslog(LOG_DEBUG, "Not found %s in control list", path);
    return -1;

}

int check_cl_entry(path_t path, FILE * control_list){

    syslog(LOG_DEBUG, "Checking path %s in control list", path);



    cl_entry_t cle;

    return get_cl_entry(path, control_list, &cle);

}

int modify_cl_entry(path_t path, int line, FILE * control_list){

    cl_entry_t cle = create_cl_entry(path);
    char buffer[MAX_ENTRY_SIZE];
    char new_line[MAX_ENTRY_SIZE];
    int current_line = 1;
    long position = 0;

    sprintf(new_line, "%s %s\n", cle.hash, cle.path);


    // Find the position of the line
    while (fgets(buffer, MAX_ENTRY_SIZE, control_list) != NULL) {
        printf("%d: %s\n", current_line, buffer);
        if (current_line == line) {
            position = ftell(control_list) - strlen(buffer);
            printf("Replacing \n %s \n with \n %s", buffer, new_line );
            break;
        }
        current_line++;
    }


    fseek(control_list, position, SEEK_SET);
    fprintf(control_list, "%s", new_line);


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
