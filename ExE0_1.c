#include <stdio.h>
#include <string.h>

void caesar_breaker(const char *cipher) {
    printf("--- BRUTE FORCE ATTACK START ---\n");
    
    for (int key = 1; key <= 25; key++) {
        printf("Key %02d: ", key);
        
        for (int i = 0; cipher[i] != '\0'; i++) {
            char c = cipher[i];
            
            if (c >= 'A' && c <= 'Z') {
               
                char decoded = ((c - 'A' - key + 26) % 26) + 'A';
                printf("%c", decoded);
            } else {
                
                printf("%c", c);
            }
        }
        printf("\n");
    }
    
    printf("--------------------------------\n");
    printf("Scan the list above to find the English message!\n");
}

int main() {
    const char *secret = "WKLV LV D VHFUHW PHVVDJH";
    
    caesar_breaker(secret);
    
    return 0;
}