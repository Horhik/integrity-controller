#include "controller.h"


bool match(char * a, char * b){
    return (strcmp(a, b) == 0);
}

args_t parse_args(int argc, char **argv){

    args_t res;
    res.path = NULL;
    res.to_regist = false;
    res.to_inspect = false;

    int i = 1;
    while (i < argc) {

        char *arg = argv[i];

        if (match(arg, "--help") || match(arg, "-h") ){
            printf("\n--------------\n");
            printf("FileController v0.1\n");
            printf("--------------\n\n");
            printf("--help, -h: printing this help info\n");
            printf("-s ,-r, --regist : set file on control (registrate it)\n");
            printf("-c, -i, --inspect : check file/dir integrity (inspect it)\n");
            printf("-p, --path : select path\n\n\n");

            exit(0);

        } else if (match(arg, "--regist") || match(arg, "-s") || match(arg, "-r")) {
            res.to_regist = true;

        } else if (match(arg, "--inspect") || match(arg, "-c") ||  match(arg, "-i")) {
            res.to_inspect = true;

        } else if (match(arg, "--path") || match(arg, "-p")) {

            if(i + 1 >= argc){
                printf("ERROR: Please specify path!\n");
                exit(1);
            }

            res.path = argv[i + 1];
            i++;
        } else {
            printf("Wrong arument: %s\n", argv[i]);
        }

        i++;
    }

    if (res.path == NULL) {

        printf("ERROR: Please choose the path using `--path <YOUR_PATH_HERE>`\n");
        exit(1);
    }

    if (!(res.to_regist || res.to_inspect)) {

        printf("ERROR: Please choose mode `--regist` or `--inspect`\n");
        exit(1);
    }


    return res;
}

bool path_is_correct(path_t path){

    // TODO write function
    return true;
}
