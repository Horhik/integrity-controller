#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>


#include <sys/stat.h>
#include <sys/types.h>

#define CONTROL_LIST_PATH "~/.config/file-controller-list.txt"

// command line arguments
typedef struct args_t {
    bool to_regist;
    bool to_inspect;
    char *path;
} args_t;

// control list entry
typedef struct cl_entry_t {
    char * filepath;
    SHA256_CTX filehash;
} cl_entry_t;

// arg_parser.c
args_t parse_args(int argc, char **argv);
bool path_is_correct(char * path);

// controller.c
int control(args_t args);
bool control_list_avaliable(FILE * control_list);

cl_entry_t create_cl_entry(char * path);
int add_cl_entry(char * path, FILE * control_list);
cl_entry_t get_cl_entry(char * path, FILE * control_list);
bool check_cl_entry(char * path, FILE * control_list);

int modify_cl_entry(cl_entry_t entry, FILE * control_list);
int delete_cl_entry(char * path, FILE * control_list);

int create_control_list(FILE * control_list);



// registrator.c
int path_regist(char * path);
int path_unregist(char * path);
bool already_registrated(char * path, FILE * control_list);
SHA256_CTX get_file_hash(char * path);
bool is_directory(char * path);
int regist_directory(char * path);



// inspector.c
int path_inspect(char * path);





#endif // CONTROLLER_H_
