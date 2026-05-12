#include <stdio.h>
#include <string.h>

void find_repeated_trigrams(const char *text) {
    int len = strlen(text);
    
    for (int i = 0; i <= len - 3; i++) {
        char current_trigram[4];
        strncpy(current_trigram, &text[i], 3);
        current_trigram[3] = '\0';

        for (int j = i + 1; j <= len - 3; j++) {
            if (strncmp(&text[i], &text[j], 3) == 0) {
                int distance = j - i;
                printf("Found \"%s\": Pos %d & Pos %d -> Distance: %d\n", 
                        current_trigram, i, j, distance);
            }
        }
    }
}

int main() {
    const char *cipher_text = "VUWMC CRYPTORVYO CRYPTOXAWZ";
    find_repeated_trigrams(cipher_text);
    return 0;
}