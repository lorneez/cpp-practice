#include <iso646.h>
//
// Created by Lorne Zhang on 5/24/21.
//

#include "ListFilesAndDirectories.h"
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

ListFilesAndDirectories::ListFilesAndDirectories() {
}

ListFilesAndDirectories::~ListFilesAndDirectories() {

}

void ListFilesAndDirectories::Show(const char * directory) {
    DIR* dirPtr = opendir(directory); // directory
    struct dirent *file; // current file
    struct stat fileStats; // file information
    struct passwd *tf; // file owner
    struct group *gf; // file group

    char buf[512];

    // continue to iterate as there are files
    while((file = readdir(dirPtr)) != NULL) {
        sprintf(buf, "%s/%s", directory, file->d_name);
        stat(buf, &fileStats);

        if(file->d_name[0] != '.') {
            // File Type
            switch (fileStats.st_mode & S_IFMT) {
                case S_IFBLK:  printf("b "); break; // block special file
                case S_IFCHR:  printf("c "); break; // special character field
                case S_IFDIR:  printf("d "); break; // directory
                case S_IFIFO:  printf("p "); break; // fifo
                case S_IFLNK:  printf("l "); break; // symbolic link
                case S_IFSOCK: printf("s "); break; // socket
                default:       printf("- "); break; // unknown (regular file)
            }

            // File Permissions
            printf( (fileStats.st_mode & S_IRUSR) ? " r" : " -"); // user read
            printf( (fileStats.st_mode & S_IWUSR) ? "w" : "-"); // user write
            printf( (fileStats.st_mode & S_IXUSR) ? "x" : "-"); // user execute
            printf( (fileStats.st_mode & S_IRGRP) ? "r" : "-"); // group read
            printf( (fileStats.st_mode & S_IWGRP) ? "w" : "-"); // group write
            printf( (fileStats.st_mode & S_IXGRP) ? "x" : "-"); // group execute
            printf( (fileStats.st_mode & S_IROTH) ? "r" : "-"); // others read
            printf( (fileStats.st_mode & S_IWOTH) ? "w" : "-"); // others write
            printf( (fileStats.st_mode & S_IXOTH) ? "x" : "-"); // others execute

            // File Hard Links
            // The number of hard links to the file. This count keeps track of how many directories have entries for
            // this file. If the count is ever decremented to zero, then the file itself is discarded as soon as no
            // process still holds it open. Symbolic links are not counted in the total.
            printf("%d ", fileStats.st_nlink);

            // File Owner
            // search the user database for an entry with a matching uid.
            tf = getpwuid(fileStats.st_uid); // user id
            printf("%s ", tf->pw_name);

            // File Group
            // search the group database for an entry with a matching gid.
            gf = getgrgid(fileStats.st_gid); // group id
            printf("%s ", gf->gr_name);

            // File Size
            printf("%zu",fileStats.st_size);

            // File Time of Last Modification
            char* c=ctime(&fileStats.st_mtime);
            for(int i=4;i<=15;i++)
                printf("%c",c[i]);

            // File Name
            printf(" %s\n", file->d_name);
        }
    }
}