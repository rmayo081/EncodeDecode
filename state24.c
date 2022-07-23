/**
 * @file state24.c
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Implementation for the state24 component of the encode and decode programs.
 * Used to store the current state of byte to char (and vice versa) conversion.
 */
#include "filebuffer.h"
#include "state24.h"

void initState(State24 *state)
{
    for (int i = 0; i < STATE_CAP; i++){
        state->data[i] = 0;
    }
    state->i = 0;
}

/**
 * Converts a given encoded byte to a printable character.
 *
 * @param b the byte to be converted
 * @return the converted character, or EOF
 */
static byte charToByte(char ch)
{
    if (ch >= 'A' && ch <= 'Z'){
        return ch - 'A';
    }

    else if (ch >= 'a' && ch <= 'z'){
        return ch - 'a' + 0x1A;
    }

    else if (ch >= '0' && ch <= '9'){
        return ch - '0' + 0x34;
    }

    else if (ch == '+'){
        return 0x3E;
    }

    else{
        return 0x3F;
    }
}

/**
 * Converts a given encoded byte into a printable character.
 *
 * @param b the character encoded into a byte
 * @return the character converted from the byte
 */
static char byteToChar(byte b)
{

    if (b >= 0x00 && b <= 0x19){
        return b + 'A';
    }
    else if (b >= 0x1A && b <= 0x33){
        return b + 'a' - 0x1A;
    }
    else if (b >= 0x34 && b <= 0x3D){
        return b + '0' - 0x34;
    }
    else if (b == 0x3E){
        return '+';
    }
    else{
        return '/';
    }
}

bool validChar(char ch)
{
    if (ch >= 'A' && ch <= 'Z'){
        return true;
    }

    else if (ch >= 'a' && ch <= 'z'){
        return true;
    }

    else if (ch >= '0' && ch <= '9'){
        return true;
    }

    else if (ch == '+'){
        return true;
    }

    else if (ch == '/'){
        return true;
    }
    else
        return false;
}
void addByte(State24 *state, byte b)
{
    if (state->i <= BYTE_SIZE * 2){
        int j = state->i + BYTE_SIZE - 1;
        for (int i = 0; i < BYTE_SIZE * sizeof(byte); i++){
            if (b & (1 << i)){
                state->data[j] = 1;
            }
            j--;
        }
        state->i += BYTE_SIZE;
    }
}

void addChar(State24 *state, char ch)
{
    if (validChar(ch)){

        byte c = charToByte(ch);
        // c = c << 2;
        int j = state->i + CHAR_SIZE - 1;
        for (int i = 0; i < CHAR_SIZE; i++){
            if (c & (1 << i)){
                state->data[j] = 1;
            }
            else{
                state->data[j] = 0;
            }
            j--;
        }

        state->i += CHAR_SIZE;
    }
}

int getBytes(State24 *state, byte Buffer[])
{
    int j = BYTE_SIZE - 1;
    byte cur = 0;
    for (int i = 0; i < BYTE_SIZE; i++){

        if (state->data[j] == 1){
            cur |= (1 << i);
        }
        j--;
    }
    Buffer[0] = cur;

    cur = 0;
    j = (BYTE_SIZE * 2) - 1;
    cur = 0;
    for (int i = 0; i < BYTE_SIZE; i++){

        if (state->data[j] == 1){
            cur |= (1 << i);
        }
        j--;
    }
    Buffer[1] = cur;

    j = STATE_CAP - 1;
    cur = 0;
    for (int i = 0; i < BYTE_SIZE; i++){

        if (state->data[j] == 1)
        {
            cur |= (1 << i);
        }
        j--;
    }
    Buffer[2] = cur;

    int count = 0;
    if (state->i >= BYTE_SIZE){
        count++;
    }
    if (state->i >= BYTE_SIZE * 2){
        count++;
    }
    if (state->i == STATE_CAP){
        count++;
    }

    initState(state);
    return count;
}

int getChars(State24 *state, char buffer[])
{

    buffer[0] = '=';
    buffer[1] = '=';
    buffer[2] = '=';
    buffer[3] = '=';
    int count = 0;
    if (state->i > 0){

        int j = CHAR_SIZE - 1;
        byte b = 0;
        for (int i = 0; i < CHAR_SIZE; i++)
        {
            if (state->data[j] == 1)
            {
                b |= (1 << i);
            }
            j--;
        }
        buffer[0] = byteToChar(b);
        count++;
    }

    if (state->i > CHAR_SIZE){
        int j = 11;
        byte b = 0;
        for (int i = 0; i < CHAR_SIZE; i++){
            if (state->data[j] == 1){
                b |= (1 << i);
            }
            j--;
        }
        buffer[1] = byteToChar(b);
        count++;
    }

    if (state->i > CHAR_SIZE * 2){

        int j = (BYTE_SIZE * 2) + 1 ;
        byte b = 0;
        for (int i = 0; i < CHAR_SIZE; i++){
            if (state->data[j] == 1)
            {
                b |= (1 << i);
            }
            j--;
        }
        buffer[2] = byteToChar(b);
        count++;
    }
    if (state->i > (BYTE_SIZE * 2) + 2)
    {

        int j = STATE_CAP - 1;
        byte b = 0;
        for (int i = 0; i < CHAR_SIZE; i++){
            if (state->data[j] == 1){
                b |= (1 << i);
            }
            j--;
        }
        buffer[3] = byteToChar(b);
        count++;
    }

    initState(state);
    return count;
}