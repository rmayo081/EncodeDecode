/**
 * @file filebuffer.h
 * @author your name (you@domain.com)
 * Header file that contains declarations, includes, and structs for the filebuffer component.
 */

#ifndef _FILEBUFFER_H_
#define _FILEBUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
/**
 * Max number of characters allowed in a string filename
 * 
 */
#define NAME_LEN 15

/** A shorthand for talking about a byte. */
typedef unsigned char byte;

/** Representation of a resizable array of bytes, with functions to
    make it easy to read and write the contents of this array to a
    file. */
typedef struct
{
  /** Resizable array of bytes stored in this filebuffer. */
  byte *data;

  // More fields added by you.
  // ..
  int len;
  int cap;
} FileBuffer;

/**
 * Creates a new file buffer in heap memory and returns a pointer to it.
 *
 * @return FileBuffer*
 */
FileBuffer *makeFileBuffer();

/**
 * Adds a byte to the buffer.
 *
 * @param buffer the buffer to store the new byte
 * @param val the byte to add
 */
void appendFileBuffer(FileBuffer *buffer, byte val);

/**
 * Reads from a binary file and stores its bytes into a filebuffer.
 *
 * @param filename string filename to be opened
 * @return a pointer to the filled filebuffer
 */
FileBuffer *loadFileBuffer(char const *filename);
/**
 * Saves the contents of the buffer to a binary file.
 *
 * @param buffer the filled buffer
 * @param filename string name of the file to be saved
 */
void saveFileBuffer(FileBuffer *buffer, char const *filename);
/**
 * Frees the memory allocated by the FileBuffer.
 *
 * @param buffer the allocated FileBuffer.
 */
void freeFileBuffer(FileBuffer *buffer);

#endif
