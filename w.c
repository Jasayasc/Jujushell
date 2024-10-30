#include "w.h"

void print_time(time_t rawtime) {
    struct tm *info;
    char buffer[80];
    info = localtime(&rawtime);
    strftime(buffer, 80, "%Y-%m-%d %H:%M", info);
    printf("%s", buffer);
}

void who() {
    struct utmp *ut;
    setutent();

    printf("%-8s %-8s %-12s %s\n", "USER", "TTY", "LOGIN@", "FROM");

    while ((ut = getutent()) != NULL) {
        if (ut->ut_type == USER_PROCESS) {
            printf("%-8s ", ut->ut_user);
            printf("%-8s ", ut->ut_line);
            print_time(ut->ut_tv.tv_sec);
            printf(" %s\n", *ut->ut_host ? ut->ut_host : "-");
        }
    }
    endutent();
}