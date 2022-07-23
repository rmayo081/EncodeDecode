/**
 * @file decode.c
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Main file of the decode program, only consists of main function.
 * Reads a text file and decodes it into a binary file.
 * Delegates all functionality to filbuffer.c and state24.c.
 */
#include "filebuffer.h"
#include "state24.h"
#include <errno.h>

/**Main function of the decode program
 * must be run with the following usage: encode [-b] [-p] <input-file> <output-file>
 * @param argc number of arguments
 * @param argv strings of agruments
 */
int main(int argc, char *argv[])
{

    if (argc != 3){
        fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>");
        exit(EXIT_FAILURE);
    }

    char inputFile[NAME_LEN];
    char outputFile[NAME_LEN];

    strcpy(inputFile, argv[1]);
    strcpy(outputFile, argv[2]);

    FileBuffer *buffer = makeFileBuffer();
    FILE *fp = fopen(inputFile, "r");
    if (fp == NULL){
        perror(inputFile);
        freeFileBuffer(buffer);
        
        exit(EXIT_FAILURE);
    }

    State24 state;
    initState(&state);
    char cur;
    int read = 0;
    byte byteBuffer[MAX_BYTE];
    bool hitPadding = false;
    while ((cur = fgetc(fp)) != EOF){

        if (isspace(cur) == 0){

            if (!validChar(cur)){
                if (cur == '='){
                    hitPadding = true;
                }
                else{
                    fprintf(stderr, "Invalid input file\n");
                    fclose(fp);
                    freeFileBuffer(buffer);
                    exit(EXIT_FAILURE);
                }
            }
            if (hitPadding && validChar(cur)){
                fprintf(stderr, "Invalid input file\n");
                fclose(fp);
                freeFileBuffer(buffer);
                exit(EXIT_FAILURE);
            }
            addChar(&state, cur);
            if (state.i == STATE_CAP){

                read = getBytes(&state, byteBuffer);

                for (int i = 0; i < read; i++)
                    appendFileBuffer(buffer, byteBuffer[i]);
            }
        }
    }

    if (state.i > 0){
        read = getBytes(&state, byteBuffer);

        for (int i = 0; i < read; i++)
            appendFileBuffer(buffer, byteBuffer[i]);
    }

    saveFileBuffer(buffer, outputFile);
    fclose(fp);
    freeFileBuffer(buffer);
    return EXIT_SUCCESS;
}