#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXTRA_CHAR ' '
#define ENCODE_CHAR ' '
#define ASCII_LEN_BASE  '0'
#define MAX_LEN_EACH_ENCODE   4
#define MAX_LEN_EACH_DECODE   3


void __decode_4char(char *e, char *d);  // function declartion.

/*
 * to get the nearest "multiple" value of from "numToRound.
 * @numtoRound : value to round up
 * @multiple : base value to multiple
 *
 */
static int roundUp(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
        if (remainder == 0)
            return numToRound;

    return numToRound + multiple - remainder;
}


/*
 * decode the string based on description
 * @e_string : encoded string.
 * @e_len : length of encoded string
 * */
int decode(char *e_string, int e_len)
{
    int n_ori_char = (int)e_string[0] - ASCII_LEN_BASE; // decode the value of length of chars.
    char *s_decoded;
    int i = 0, j = 0;
    size_t size_alloc = roundUp(n_ori_char, MAX_LEN_EACH_DECODE);  // we allocat multuple of "MAX_LEN_EACH_DECODE" to store decoded chars including "extra char for encoding"

    s_decoded = (char *)malloc(size_alloc);
    if (!s_decoded)
        return -1;

    memset(s_decoded, '\0', size_alloc);

    for (i = 0, j = 0; i < e_len; i += MAX_LEN_EACH_ENCODE, j += MAX_LEN_EACH_DECODE) {
        __decode_4char(&e_string[1 + i], &s_decoded[j]);  // dececode 4 encoded chars, follow the description in pdf.
    }
    s_decoded[n_ori_char] = '\0';  // to prevent printf %s to print "extra char" added when encode.

    printf("%s", s_decoded);

    free(s_decoded);

    return 0;
}


/* Inverse the procedure of encoding */
void __decode_4char(char *e, char *d)
{
    char c1 = e[0], c2 = e[1], c3 = e[2], c4 = e[3];

    c1 -= ENCODE_CHAR;
    c2 -= ENCODE_CHAR;
    c3 -= ENCODE_CHAR;
    c4 -= ENCODE_CHAR;

    /* decode each encoded char base on description in pdf.
     * bitwise operation for four encoded chars to three decoded chars
     * */
    d[2] = (c4 & 0x3F) | ((c3 & 0x3) << 6);
    d[1] = ((c3 >> 2) & 0xF) | ((c2 & 0xF) << 4);
    d[0] = ((c2 >> 4) & 0x3) | ((c1 & 0x3F) << 2);
    /*printf("%c%c%c", d[0], d[1], d[2]);*/
}



int main(int argc, const char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {  // read each line of string from standard input
        decode(line, read);
    }
    free(line);

    return 0;
}
