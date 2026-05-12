#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

unsigned char get_second_byte(char *key, int key_len) {
    unsigned char s[256];
    for (int i = 0; i < 256; i++) s[i] = i;

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % key_len]) % 256;
        swap(&s[i], &s[j]);
    }

    int i = 0;
    j = 0;
    unsigned char result;
    
    for (int k = 0; k < 2; k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(&s[i], &s[j]);
        int t = (s[i] + s[j]) % 256;
        result = s[t];
    }
    return result;
}

int main() {
    int iterations = 100000;
    int zero_count = 0;
    char key[16];
    srand(time(NULL));

    for (int i = 0; i < iterations; i++) {
        for (int k = 0; k < 16; k++) key[k] = rand() % 256;
        
        if (get_second_byte(key, 16) == 0x00) {
            zero_count++;
        }
    }

    printf("Iterations: %d\n", iterations);
    printf("Second byte was 0x00: %d times\n", zero_count);
    printf("Probability: %f (Expected 1/256 = 0.003906)\n", (float)zero_count / iterations);
    printf("Bias factor: %f\n", ((float)zero_count / iterations) / (1.0/256.0));

    return 0;
}