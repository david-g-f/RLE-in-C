/* Run length encoding with C
-- Main idea is to gather similar letters in sequence and compress it into a short form 
e.g "aaaaab" = "5a1b"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compress(char* input){
    FILE* in = fopen(input, "r");
    FILE* out = fopen("compressed.txt", "w");

    if (in == NULL || out == NULL){
        fprintf(stderr, "Error initializing FILE pointers\n");
        return 1;
    } 

    char curr, prev;
    int counter = 1;

    prev = fgetc(in); 
    while((curr = fgetc(in)) != EOF){ // Iterate through each character and count how many subsequent letters are the same
        if (curr == prev){
            counter++;
        }
        else {
            fprintf(out, "%d%c", counter, prev); // Write to the output in RLE format
            counter = 1;
        }
        prev = curr;
    }
    fprintf(out, "%d%c", counter, prev);

    fclose(in);
    fclose(out);
    return 0;
}

int decompress(char* input){
    FILE* in = fopen(input, "r");
    FILE* out = fopen("decompressed.txt", "w");

    if (in == NULL || out == NULL){
        fprintf(stderr, "Error initializing FILE pointers.\n");
        return 1;
    }

    int counter;
    char c;

    while(fscanf(in, "%d%c", &counter, &c) == 2){
        for (int i = 0; i < counter; i++){
            fputc(c, out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}

int main(int argc, char** argv){
    // commandline should look like: /comp [-c/-d] filename.txt
    if (argc != 3){
        fprintf(stderr, "You are missing an argument, or you put too many arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0){
        compress(argv[2]);
    }
    else if (strcmp(argv[1], "-d") == 0){
        decompress(argv[2]);
    }
    else{
        fprintf(stderr, "You've entered an incorrect mode in the terminal, please try again.\nFormat for using the terminal is: ./comp [-c/-d] filename.txt\n");
        return 1;
    }

    return 0;
}