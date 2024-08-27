#include "controller.h"




bool is_directory(path_t path) {

    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        syslog(LOG_ERR, "path: %s neither file or directory ", path);
        return false; // Error occurred
    }
    return S_ISDIR(path_stat.st_mode);
}

int append_string(path_t * array[], path_t element, size_t *size ) {

    path_t * array_ptr  = realloc(*array, sizeof(path_t) * (*size + 1));

    if (array_ptr == NULL) {

        syslog(LOG_ERR, "Error allocating memory for array ");
        return -1;

    } else {

        *array = array_ptr;

        (*array)[*size] = element;

        (*size)++;

    }

    return 0;
}



int list_dir(path_t path, path_t * paths[], size_t *paths_size) {

    char _path[PATH_MAX];
    realpath(path, _path);
    strcat(_path, "/");
    const char * fullpath = _path;



    //syslog(LOG_DEBUG, "Fullpath is %s ", fullpath);


    // Open dir
    DIR *dir;
    struct dirent *entry;
    dir = opendir(fullpath);

    if (dir == NULL) {

        syslog(LOG_ERR, "Error opening dir: %s ", path);
        perror("opendir");
        return 1;
    }

    // Reading dir
    while ((entry = readdir(dir)) != NULL) {

        path_t name = entry -> d_name;
        char fullname[PATH_MAX] = "";
        strcat(fullname, fullpath);



        if (strcmp(name, ".") !=0 && strcmp(name ,"..") != 0){

            strcat(fullname, name);

            char *new_path = strdup(fullname);

            if (new_path == NULL) {
                syslog(LOG_ERR, "Error allocating memory for new path");
                closedir(dir);
                return 1;
            }


            append_string(paths, new_path, paths_size);

        }

    }


    closedir(dir);
    return 0;
}

int regist_directory(path_t path){
    //TODO finish function
    return 0;
}

void hash_to_hex(const unsigned char hash[SHA256_DIGEST_LENGTH], char *hexastr) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexastr + (i * 2), "%02x", hash[i]);
    }
    hexastr[SHA256_DIGEST_LENGTH * 2] = '\0'; // Null-terminate the string
}

int get_file_hash(path_t path, char hash_hex[HASH_SIZE_HEX]){

    unsigned char output[SHA256_DIGEST_LENGTH];

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    const size_t buffer_size = 32768;
    unsigned char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return 1;
    }

    size_t bytes_read = 0;
    while ((bytes_read = fread(buffer, 1, buffer_size, file))) {
        SHA256_Update(&sha256, buffer, bytes_read);
    }

    SHA256_Final(output, &sha256);
    hash_to_hex(output, hash_hex);


    fclose(file);
    free(buffer);
    return 0;
}





int path_regist(path_t path){

    syslog(LOG_INFO, "Registrating new entry: %s\n\n\n", path);
    // Opening file
    FILE * fp;
    fp = fopen(path, "r");

    // Checking are path correct
    if (fp == NULL) {
        syslog(LOG_ERR, "No such file or directory: %s", path);
        return 1;
    }

    fclose(fp);

    FILE * control_list;

    control_list = fopen(CONTROL_LIST_PATH, "a+");


    // Checking are control list are avaliable
    if (!control_list_avaliable(control_list)){

        syslog(LOG_ERR, "Control list is not avaliable");
        exit(1);
    }


    // registrating path
    if (is_directory(path)){

        syslog(LOG_DEBUG, "Registrating directory: %s", path);
        path_t * paths = NULL;
        size_t paths_size = 0;


        list_dir(path, &paths, &paths_size);


        for(size_t i = 0; i < paths_size; i++){

            path_regist(paths[i]);

        }

    } else {

        syslog(LOG_DEBUG, "Registrating file: %s", path);
        char _path[PATH_MAX];
        realpath(path, _path);


        add_cl_entry(_path, control_list);


    }



    fclose(control_list);
    return 0;
}

int path_unregist(path_t path){
    // TODO
    return 1;
}
