#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void vigenere_decrypt(const char *input_file, const char *key_file, const char *output_file) {
    FILE *fin = fopen(input_file, "r");
    FILE *fkey = fopen(key_file, "r");
    FILE *fout = fopen(output_file, "w");

    if (!fin || !fkey || !fout) {
        return;
    }

    char key[256];
    if (fscanf(fkey, "%s", key) != 1) {
        return;
    }

    int key_len = strlen(key);
    int key_index = 0;
    int ch;

    while ((ch = fgetc(fin)) != EOF) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int k = toupper(key[key_index % key_len]) - 'A';
            char decrypted_ch = ((ch - base - k + 26) % 26) + base;
            fputc(decrypted_ch, fout);
            key_index++;
        } else {
            fputc(ch, fout);
        }
    }

    fclose(fin);
    fclose(fkey);
    fclose(fout);
}

int main() {
    vigenere_decrypt("encrypted.txt", "key.txt", "decrypted.txt");
    return 0;
}