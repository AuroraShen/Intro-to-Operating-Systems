//
//  main.c
//  537 P1a
//
//  Created by Aurora Shen on 1/27/20.
//  Copyright © 2020 Aurora Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    // If no arguments are provided case
    if(2 != argc){
        printf("wis-untar: tar-file\n");
        exit(1);
    }
    else{
        FILE *tarfile = fopen(argv[1], "r");
        // If the tar filename doesn’t exist case
        if ( tarfile == NULL) {
            printf("wis-untar: cannot open file\n");
            exit(1);
        }
        
        char filename[100];
        int size;
        char content[size];
        
        // Read filename for the first time
        size_t readsize = fread( &filename, sizeof(char), 100, tarfile );
        while( 100 == readsize ){
            // Write(overwrite) the new file
            FILE* fp = fopen(filename, "w");
            // Read sizes of the file
            fread(&size, sizeof(double), 1, tarfile);
            // Read contents of the file
            fread(&content, (size_t)size, 1, tarfile);
            // Write contents into the new file
            fwrite(&content, (size_t)size, 1, fp);
            
            // Close the current file and read filename for the next file
            fclose(fp);
            readsize = fread( &filename, sizeof(char), 100, tarfile );
        }
        fclose(tarfile);
    }
    return 0;
}
        
            
            
    

