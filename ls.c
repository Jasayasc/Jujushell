#include "ls.h"

void print_detailed_info(const struct stat *statbuf, const char *name) {
    char permissions[11] = "----------";
    
    if (S_ISDIR(statbuf->st_mode)) permissions[0] = 'd';
    if (S_ISLNK(statbuf->st_mode)) permissions[0] = 'l';
    
    if (statbuf->st_mode & S_IRUSR) permissions[1] = 'r';
    if (statbuf->st_mode & S_IWUSR) permissions[2] = 'w';
    if (statbuf->st_mode & S_IXUSR) permissions[3] = 'x';
    if (statbuf->st_mode & S_IRGRP) permissions[4] = 'r';
    if (statbuf->st_mode & S_IWGRP) permissions[5] = 'w';
    if (statbuf->st_mode & S_IXGRP) permissions[6] = 'x';
    if (statbuf->st_mode & S_IROTH) permissions[7] = 'r';
    if (statbuf->st_mode & S_IWOTH) permissions[8] = 'w';
    if (statbuf->st_mode & S_IXOTH) permissions[9] = 'x';
    
    char timebuf[80];
    struct tm *timeinfo = localtime(&statbuf->st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", timeinfo);
    
    struct passwd *pw = getpwuid(statbuf->st_uid);
    struct group *gr = getgrgid(statbuf->st_gid);

    printf("%s %ld %s %s %5ld %s %s\n", 
           permissions,
           (long)statbuf->st_nlink,
           pw ? pw->pw_name : "UNKNOWN",
           gr ? gr->gr_name : "UNKNOWN",
           (long)statbuf->st_size,
           timebuf,
           name);
}

void list_directory(const char *path, int detailed) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error abriendo el directorio");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;  // Ignorar archivos ocultos

        if (detailed) {
            char fullpath[PATH_MAX];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

            struct stat statbuf;
            if (stat(fullpath, &statbuf) == -1) {
                perror("Error obteniendo información del archivo");
                continue;
            }
            print_detailed_info(&statbuf, entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}