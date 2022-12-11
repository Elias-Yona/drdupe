#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

// TODO: recursively traverse the filesystem
// TODO: compute the hashes of the files
// TODO: build the hash table
int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    const char *dir_path = ".";
    DIR *dir =  opendir(dir_path);

    if (dir == NULL) {
        fprintf(stderr, "ERROR! Could not open directory %s: %s\n", dir_path, strerror(errno));
        exit(1);
    }

    errno = 0;
    struct dirent *ent = readdir(dir);
    while (ent != NULL) {
        if (ent->d_name[0] != '.') {
            printf("File: %s\n", ent->d_name);
        }
        ent = readdir(dir);
    }

    if (errno != 0) {
        fprintf(stderr, "ERROR: Could not read directory %s:%s", dir_path, strerror(errno));
        exit(1);
    }

    closedir(dir);
    return 0;
}