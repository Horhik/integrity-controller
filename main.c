#include "controller.h"


int main(int argc, char * argv[]){

    // switch to this line to print logs to stdout
    //openlog("FileController", LOG_CONS | LOG_PERROR , LOG_USER);
    //

    openlog("FileController", LOG_CONS , LOG_USER);

    syslog(LOG_INFO, "FileController had started");
    setlogmask(LOG_UPTO(LOG_DEBUG));
    args_t args = parse_args(argc, argv);

    // selecting mode: registration or verification
    //mode_t mode = select_program_mode(parsed);

    control(args);

    closelog();

    return 0;
}
