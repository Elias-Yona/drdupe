#define _DEFAULT_SOURCE

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>


#define PATH_SEP "/"
#define PATH_SEP_LEN (sizeof(PATH_SEP) - 1)

long long int getFileSize(char *filename) {
  // Use the stat function to get information about the file
  struct stat st;
  if (stat(filename, &st) != 0) {
    printf("Error: unable to stat file %s\n", filename);
    return 1;
  }

  // Print the size of the file
  // printf("Size of %s: %lld bytes\n", filename, st.st_size);

  return st.st_size;
}

char *join_path(const char *base, const char *file) 
{
    size_t base_len = strlen(base);
    size_t file_len = strlen(file);
    
    // beginning
    char *begin = malloc(base_len + file_len + PATH_SEP_LEN + 1);
    assert(begin != NULL);

    // assigning end to beginning and append individual parts to end
    char *end = begin;
    memcpy(end, base, base_len);
    end += base_len;
    memcpy(end, PATH_SEP, PATH_SEP_LEN);
    end += PATH_SEP_LEN;
    memcpy(end, file, file_len);
    end += file_len;
    *end = '\0';

    return begin;
}


void print_files_recursively(const char *dir_path) 
{
    DIR *dir =  opendir(dir_path);

    if (dir == NULL) {
        fprintf(stderr, "ERROR! Could not open directory %s: %s\n", dir_path, strerror(errno));
        exit(1);
    }

    errno = 0;
    struct dirent *ent = readdir(dir);
    while (ent != NULL) {
        // check if the entry if a directory or a file
        // if entry is a directory, loop through it's contents (directories and files)
        if (ent->d_type == DT_DIR) {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
                char *child_path = join_path(dir_path, ent->d_name);
                print_files_recursively(child_path);
                free(child_path);
            }
        } else {
            printf("file: %s/%s/ size: %lld  \n", dir_path, ent->d_name, getFileSize(ent->d_name));
        }
        ent = readdir(dir);
    }

    if (errno != 0) {
        fprintf(stderr, "ERROR: Could not read directory %s:%s", dir_path, strerror(errno));
        exit(1);
    }

    closedir(dir);
}

// TODO: recursively traverse the filesystem
// TODO: compute the hashes of the files
// TODO: build the hash table
int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    print_files_recursively(".");
    return 0;
}