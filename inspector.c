#include "controller.h"
int path_inspect(path_t _path){

    char path[PATH_MAX];
    realpath(_path, path);

    syslog(LOG_INFO, "Inspecting entry: %s", path);
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

        syslog(LOG_DEBUG, "Is directory. inspecting...");
        path_t * paths = NULL;
        size_t paths_size = 0;


        list_dir(path, &paths, &paths_size);

        bool broken = false;
        for(size_t i = 0; i < paths_size; i++){

            if (!path_inspect(paths[i])){

                syslog(LOG_INFO, "Integrity is broken!: %s", paths[i]);
                broken=true;
            }

        }

        if (!broken)
        syslog(LOG_INFO, "Integrity preserved!");

    } else {

        syslog(LOG_DEBUG, "Is file. inspecting...");


        cl_entry_t existing_cle;
        cl_entry_t *p_existing_cle = &existing_cle;
        syslog(LOG_DEBUG, "Getting entry for %s", path);
        int cle_exists = get_cl_entry(path, control_list, p_existing_cle);

        if (cle_exists == -1){
            syslog(LOG_ERR, "File not found in control list");
            return -1;
        } else {


            cl_entry_t new_cle = create_cl_entry(path);

            //syslog(LOG_INFO, "E HASH %s", existing_cle.hash);
            //syslog(LOG_INFO, "O HASH %s", new_cle.hash);

            if (match(existing_cle.hash, new_cle.hash)){
                printf("File is correct: %s\n", path);
                return 1;
            } else {
                printf("File had changed: %s\n", path);
                return 0;
            }

        }



    }


    fclose(control_list);
    return 0;
}
