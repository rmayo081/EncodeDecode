/**
 * @file filebuffer.c
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Component program used for the encode and decode programs.
 * Handles loading and saving bytes from and to files.
 */
#include "filebuffer.h"
FileBuffer *makeFileBuffer()
{

    FileBuffer *buffer = (FileBuffer *)malloc(sizeof(FileBuffer));

    buffer->cap = 1;
    buffer->data = (byte *)malloc(buffer->cap * sizeof(byte));
    buffer->len = 0;

    return buffer;
}

void appendFileBuffer(FileBuffer *buffer, byte val)
{
    if (buffer->len >= buffer->cap){
        buffer->cap += 1;
        buffer->data = (byte *)realloc(buffer->data, buffer->cap * sizeof(byte));
    }

    buffer->data[buffer->len] = val;
    (buffer->len)++;
}

FileBuffer *loadFileBuffer(char const *filename)
{

    FileBuffer *buffer = makeFileBuffer();

    FILE *fb = fopen(filename, "rb");
    if (fb == NULL){
        perror(filename);
        freeFileBuffer(buffer);
        exit(EXIT_FAILURE);
    }
    // assert(fb);
    byte b;
    int read = fread(&b, sizeof(byte), 1, fb);
    if (read != 0)
        appendFileBuffer(buffer, b);
    while (read != 0){
        read = fread(&b, sizeof(byte), 1, fb);
        appendFileBuffer(buffer, b);
    }

    fclose(fb);

    return buffer;
}

void saveFileBuffer(FileBuffer *buffer, char const *filename)
{

    FILE *dest = fopen(filename, "wb");
    if (dest == NULL){
        perror(filename);
        freeFileBuffer(buffer);
        exit(EXIT_FAILURE);
    }
    fwrite(buffer->data, sizeof(byte), buffer->len, dest);
    fclose(dest);
}

void freeFileBuffer(FileBuffer *buffer)
{

    free(buffer->data);
    free(buffer);
}