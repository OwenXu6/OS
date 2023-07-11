#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

typedef enum { WRONG_CHAR, SUCCESS_PARSE, TOO_MANY_CHAR } cmd_parse;

cmd_parse parse_cmd(int argc, char *argv[]);

int
main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(2, "Usage: sleep duration\n");
        exit(1);
    }

    cmd_parse parse_result = parse_cmd(argc, argv);
    if (parse_result == TOO_MANY_CHAR) {
        fprintf(2, "sleep: too many arguments\n");
        exit(1);
    } else if (parse_result == WRONG_CHAR) {
        fprintf(2, "sleep: invalid duration\n");
        exit(1);
    }

    int duration = atoi(argv[1]);
    if (duration < 0) {
        fprintf(2, "sleep: invalid duration\n");
        exit(1);
    }

    sleep(duration * 1000);

    exit(0);
}

cmd_parse
parse_cmd(int argc, char *argv[])
{
    if (argc > 2) {
        return TOO_MANY_CHAR;
    }

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!('0' <= argv[1][i] && argv[1][i] <= '9')) {
            return WRONG_CHAR;
        }
    }

    return SUCCESS_PARSE;
}
