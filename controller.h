#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <dirent.h>


#include <sys/stat.h>
#include <sys/types.h>

#include <syslog.h>

#define CONTROL_LIST_PATH "control-list.txt"
#define HASH_SIZE_HEX SHA256_DIGEST_LENGTH * 2 + 1
#define MAX_ENTRY_SIZE (PATH_MAX + HASH_SIZE_HEX + 1)
#define MAX_TOKENS 2

typedef const char* path_t;

typedef char hash;
// command line arguments
typedef struct args_t {
    bool to_regist;
    bool to_inspect;
    path_t path;
} args_t;

// control list entry
typedef struct cl_entry_t {
    char hash[HASH_SIZE_HEX];
    char path[PATH_MAX];
} cl_entry_t;

// arg_parser.c
args_t parse_args(int argc, char **argv);
bool path_is_correct(path_t path);
bool match(char * a, char * b);

// controller.c
int control(args_t args);
bool control_list_avaliable(FILE * control_list);

cl_entry_t create_cl_entry(path_t path);
int add_cl_entry(path_t path, FILE * control_list);
int get_cl_entry(path_t path, FILE * control_list, cl_entry_t * cle);
int check_cl_entry(path_t path, FILE * control_list);

int modify_cl_entry(path_t path, int line, FILE * control_list);
int delete_cl_entry(path_t path, FILE * control_list);

int create_control_list(FILE * control_list);



// registrator.c
int path_regist(path_t path);
int path_unregist(path_t path);
int get_file_hash(path_t path, char hash[HASH_SIZE_HEX] );
bool is_directory(path_t path);
int regist_directory(path_t path);

int list_dir(path_t path, path_t * paths[], size_t *paths_size);
int append_string(path_t * array[], path_t element, size_t *size );



// inspector.c
int path_inspect(path_t path);




#endif // CONTROLLER_H_
