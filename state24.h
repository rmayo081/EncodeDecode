/**
 * @file state24.h
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Header file containing declarations, includes, and structs of the state24 component file.
 */

#ifndef _STATE64_H_
#define _STATE64_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define STATE_CAP 24
// Include filebuffer to get the byte type.
#include "filebuffer.h"
/**Number of bits in an encoded character*/
#define CHAR_SIZE 6
/**Number of bits in a byte*/
#define BYTE_SIZE 8
/**The maximum number of characters that can be in the state array at one time*/
#define MAX_CHAR 4
/**The max number of bytes that can be in the state array at one time*/
#define MAX_BYTE 3

/**
 * struct used to store a set of 24 bits modeled by an array of 24 shorts, called "data".
 * The field "i" is the number of bits that are currently read into the state.
 */
typedef struct
{
  short data[STATE_CAP];
  int i;
} State24;

/**
 * Initializes a State24 variable passed by reference.
 * Sets all values in the state to 0.
 *
 * @param state the state to be initialized
 */
void initState(State24 *state);
/**determines if a given character is among the valid 64 characters that can be encoded
 * @param ch the character to check
 * @return bool true if the character is valid in the encoding, false otherwise.
 */
bool validChar(char ch);
/**
 * Adds a byte to the state, fills in the next 8 available bits.
 *
 * @param state the state to add the byte too
 * @param b the byte to add
 */
void addByte(State24 *state, byte b);
/**
 * Converts a given character to the encoded binary and adds it to the state, fills in the next 6 available bits.
 *
 * @param state the state to add the char too
 * @param ch the char to add
 */
void addChar(State24 *state, char ch);
/**
 * Empties the state of all of its bits into a given byteBuffer array.
 * After the function is done, the given state's fields are reset.
 * @param state the state to get the bytes from
 * @param Buffer the buffer to add bytes too
 * @return the number of bytes retrieved from the state. Will return from 0 to 3, inclusive.
 */
int getBytes(State24 *state, byte Buffer[]);
/**
 * Empties the state of all its bits, converts them into characters, then fills the characters into the given charBuffer.
 * After the function is done, the given state's fields are reset.
 * @param state the state to get the bytes from to convert to characters
 * @param buffer the buffer to add the converted characters too.
 * @return the number of characters retrieved from the state. Will return from 0 to 4, inclusive.
 */
int getChars(State24 *state, char buffer[]);

#endif
