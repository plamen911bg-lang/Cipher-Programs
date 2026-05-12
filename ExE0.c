#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char transform(char c, int key, char mode) {
    if (isupper(c)) {
        if (mode == 'e') return ((c - 'A' + key) % 26) + 'A';
        else return ((c - 'A' - key + 26) % 26) + 'A';
    }
    if (islower(c)) {
        if (mode == 'e') return ((c - 'a' + key) % 26) + 'a';
        else return ((c - 'a' - key + 26) % 26) + 'a';
    }
    return c;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s -e/-d <input_file> <key_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char mode = argv[1][1];
    FILE *fin = fopen(argv[2], "r");
    FILE *fkey = fopen(argv[3], "r");
    FILE *fout = fopen(argv[4], "w");

    if (!fin || !fkey || !fout) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    int key;
    if (fscanf(fkey, "%d", &key) != 1) {
        fprintf(stderr, "Invalid key format in %s\n", argv[3]);
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        fputc(transform((char)ch, key, mode), fout);
    }

    printf("Success! Result saved in %s\n", argv[4]);

    fclose(fin);
    fclose(fkey);
    fclose(fout);

    return EXIT_SUCCESS;
}