#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void rc4_init(unsigned char *s, char *key, int key_len) {
    for (int i = 0; i < 256; i++)
        s[i] = i;

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % key_len]) % 256;
        swap(&s[i], &s[j]);
    }
}

void rc4_crypt(unsigned char *s, unsigned char *data, int data_len) {
    int i = 0, j = 0;
    for (int k = 0; k < data_len; k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(&s[i], &s[j]);
        int t = (s[i] + s[j]) % 256;
        data[k] ^= s[t];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <input_file> <output_file> <password>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    FILE *fout = fopen(argv[2], "wb");
    char *password = argv[3];

    if (!fin || !fout) {
        perror("Error opening files");
        return 1;
    }

    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    unsigned char *buffer = malloc(size);
    fread(buffer, 1, size, fin);

    unsigned char s[256];
    rc4_init(s, password, strlen(password));
    rc4_crypt(s, buffer, size);

    fwrite(buffer, 1, size, fout);

    free(buffer);
    fclose(fin);
    fclose(fout);

    return 0;
}