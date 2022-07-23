/**
 * @file encode.c
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Main file of the encode program. Reads a binary file and encodes it into a string of printable characters.
 * Only consists of main function, delegates all major functionality to filebuffer.c and state24.c.
 */
#include "filebuffer.h"
#include "state24.h"
/**
 * Constant for the length of a line if the -b flag is not added
 */
#define LINE_LEN 76


/**
 * Main function of the encode program.
 *
 * @param argc number of arguments
 * @param argv array of string argument
 * @return int
 */
int main(int argc, char *argv[])
{
    if (argc < 3){
        fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>");
        exit(EXIT_FAILURE);
    }

    bool markP = false;
    bool markB = false;
    bool inRead = false;
    bool outRead = false;
    char inputFile[NAME_LEN];
    char outputFile[NAME_LEN];

    for (int i = 1; i < argc; i++){
        if (argv[i][0] == '-'){
            if (strcmp("-p", argv[i]) == 0){
                markP = true;
            }
            else if (strcmp("-b", argv[i]) == 0){
                markB = true;
            }
            else{
                fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");

                exit(EXIT_FAILURE);
            }
        }

        else if (!inRead){
            strcpy(inputFile, argv[i]);
            inRead = true;
        }
        else if (!outRead){
            strcpy(outputFile, argv[i]);
            outRead = true;
        }
        else{
            fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
            exit(EXIT_FAILURE);
        }
    }

    FileBuffer *buffer = loadFileBuffer(inputFile);

    FILE *output = fopen(outputFile, "w");
    State24 state;
    char charBuffer[MAX_CHAR];
    initState(&state);
    int bufferSize = buffer->len;
    int lineLen = 0;
    int read = 0;
    for (int i = 0; i < bufferSize - 1; i++){

        addByte(&state, buffer->data[i]);
        if (state.i == STATE_CAP){

            lineLen += MAX_CHAR;
            read = getChars(&state, charBuffer);

            fputc(charBuffer[0], output);
            fputc(charBuffer[1], output);
            fputc(charBuffer[2], output);
            fputc(charBuffer[3], output);
            if (lineLen == LINE_LEN && !markB){
                fputc('\n', output);
                lineLen = 0;
            }
        }
    }

    read = getChars(&state, charBuffer);

    for (int i = 0; i < read; i++){
        fputc(charBuffer[i], output);
    }
    if (read != 0 && !markP){
        for (int i = 0; i < MAX_CHAR - read; i++){
            fputc('=', output);
        }
    }

    fputc('\n', output);

    fclose(output);
    freeFileBuffer(buffer);
    return EXIT_SUCCESS;
}