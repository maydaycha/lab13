#include <stdio.h>
#include <stdlib.h>

#define EXTRA_CHAR_LAST_YEAR  '\0'
#define EXTRA_CHAR_THIS_YEAR  ' '

#define ENCODE_CHAR_LAST_YEAR  '0'
#define ENCODE_CHAR_THIS_YEAR  ' '

#define EXTRA_CHAR       EXTRA_CHAR_LAST_YEAR
#define ENCODE_CHAR      ENCODE_CHAR_LAST_YEAR

#define ASCII_LEN_BASE  '0'
#define MAX_LEN_EACH_ENCODE   4
#define MAX_LEN_EACH_DECODE   3


void __decode_4char(char *e, char *d);

// num_of_char : number of original characters
// e_string : encoded string
int decode(char *e_string, int e_len)
{
    int n_ori_char = (int)e_string[0] - ASCII_LEN_BASE;
    char *s_decoded;
    int i = 0, j = 0;

#if 0
    printf("n_ori_char:%d\n", n_ori_char);
#endif

    s_decoded = (char *)malloc(n_ori_char + 1); // need add '\0' in the tail ?
    if (!s_decoded)
        return -1;

    for (i = 0, j = 0; i < e_len; i+=MAX_LEN_EACH_ENCODE, j+=MAX_LEN_EACH_DECODE) {
        __decode_4char(&e_string[1 + i], &s_decoded[j]);
    }

#if 0
    printf("\n\n\n");
#endif
    free(s_decoded);

    return 0;
}

void __decode_4char(char *e, char *d)
{
    char c1 = e[0], c2 = e[1], c3 = e[2], c4 = e[3];

    c1 -= ENCODE_CHAR;
    c2 -= ENCODE_CHAR;
    c3 -= ENCODE_CHAR;
    c4 -= ENCODE_CHAR;

    d[2] = (c4 & 0x3F) | ((c3 & 0x3) << 6);
    d[1] = ((c3 >> 2) & 0xF) | ((c2 & 0xF) << 4);
    d[0] = ((c2 >> 4) & 0x3) | ((c1 & 0x3F) << 2);
    printf("%c%c%c", d[0], d[1], d[2]);
}





int main(int argc, const char *argv[])
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
#if 0
        printf("Retrieved line of length %zu (oc len=%d, encode_len=%d) :\n",
                read,
                (line[0] - 48),
                read - 1 - 1);
        printf("%s", line);
#endif
        decode(line, read);
    }
    free(line);


    return 0;
}
