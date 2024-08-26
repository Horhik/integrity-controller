#include "controller.h"


int main(int argc, char * argv[]){

    args_t args = parse_args(argc, argv);

    // selecting mode: registration or verification
    //mode_t mode = select_program_mode(parsed);

    return control(args);
}
