//
//  main.c
//  537 P1a
//
//  Created by Aurora Shen on 1/27/20.
//  Copyright © 2020 Aurora Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, const char ** argv) {
    // Fewer than two arguments are supplied case
    if(argc < 3){
        printf("wis-tar: tar-file file […]\n");
        exit(1);
    }
    else{
        // Write(overwrite) the tarfile with fopen function
        FILE *tarfile = fopen(argv[1], "w");
        
        char* line = NULL;
        size_t linecap = 0;
        
        for( int i = 2; i < argc; i++ ){
            FILE *fp = fopen(argv[i], "r");
            // Files that should be tared are not found case
            if (fp == NULL) {
                printf("wis-tar: cannot open file\n");
                exit(1);
            }
            
            // Write file names
            char newname[100];
            // Strncpy filled the remain spots with null
            strncpy(newname, argv[i], 100);
            fwrite(&newname, sizeof(char), 100, tarfile);

            // Write file sizes
            struct stat info;
            int err = stat( argv[i], &info);
            if(err == 0){
                fwrite(&info.st_size, sizeof(double), 1, tarfile);
            }
            else{
                printf("wis-tar: cannot get file size\n");
                exit(1);
            }
            
            // Read files and write contents into the tar file
            while( -1 != getline(&line, &linecap, fp) ){
                fprintf(tarfile, "%s", line);
            }
            
            // Free the buffer for line that getline allocated
            free(line);
            line = NULL;
            // Close after each opening
            fclose(fp);
        }
        fclose(tarfile);
    }
    return 0;
}
        
            
            
    

