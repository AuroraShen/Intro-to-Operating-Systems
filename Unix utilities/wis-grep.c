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

int main(int argc, const char ** argv) {
    // Passed no command-line arguments case
    if(argc < 2){
        printf("wis-grep: searchterm [file ...]\n");
        exit(1);
    }
    
    char* line = NULL;
    size_t linecap = 0;
    
    // If a search term, but no file case
    if(argc == 2){
        while( -1 != getline(&line, &linecap, stdin) ){
            if( NULL != strstr(line, argv[1]) )
                printf("%s", line);
        }
    }
    else{
        for( int i = 2; i < argc; i++ ){
            FILE *fp = fopen(argv[i], "r");
            // If wis-grep encounters a file that it cannot open
            if (fp == NULL) {
                printf("wis-grep: cannot open file\n");
                exit(1);
            }
            while( -1 != getline(&line, &linecap, fp) ){
                if( NULL != strstr(line, argv[1]) )
                // The line should be printed
                    printf("%s", line);
            }
            // Free the buffer for line that getline allocated
            free(line);
            line = NULL;
            // Close after each opening
            fclose(fp);
        }
    }
    // wis-grep should exit with return code 0
    return 0;
}
