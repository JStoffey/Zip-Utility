#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 528

int main(int argc, char* argv[]){

    // If there is more than 1 file
    if(argc > 2){
        char fileBuffer[MAX_LEN];
        char * temp = malloc(sizeof(char)*MAX_LEN);

        // Loop through each file and concatenate them together
        for(int i = 1; i < argc; i++){
            FILE* fp = fopen(argv[i], "r");
            while(fgets(fileBuffer, sizeof(fileBuffer), fp) != NULL) {
                temp[strcspn(temp, "\n")] = 0; //remove newline
                strcat(temp, &fileBuffer[0]);
            }
            fclose(fp);
        }


        char c;
        char cur;
        int count = 0;
        for(int j = 0; j <= sizeof(temp); j++){
            while((c = temp[j]) != '\0'){
                if(count == 0){
                    cur = c;
                }
                if(c == cur){
                    count++;
                }else{
                    fwrite(&count, 1, sizeof(int), stdout);
                    printf("%c", cur);
                    count = 0;
                    cur = c;
                }
                j++;
            }
            fwrite(&count, 1, sizeof(int), stdout);
            printf("%c", cur);
            free(temp);
        }
        
    // If there is 1 file
    }else{
        if(argv[1] != NULL){
            FILE* fp = fopen(argv[1], "r");
            if(fp == NULL){
                fprintf(stderr, "Failed to open file.\n");
                exit(1);
            }

            char c;
            char cur;
            int count = 0;
            while((c = getc(fp)) != EOF){
                if(count == 0){
                    cur = c;
                }
                if(c == cur){
                    count++;
                }else{
                    fwrite(&count, 1, sizeof(int), stdout);
                    printf("%c", cur);
                    count = 1;
                    cur = c;
                }
            }
            if(cur == '\n'){
                count = 1;
                fwrite(&count, 1, sizeof(int), stdout);
                printf("%c", cur);
            }else{
                fwrite(&count, 1, sizeof(int), stdout);
                printf("%c", cur);
            }

            fclose(fp);

        }else{
            printf("wzip: file1 [file2 ...]\n");
            exit(1);
        }
    }
}