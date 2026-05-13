#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main(){
    char str[4];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char target[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";

    for (char a = "a"; a <= "z"; a++){
        for(char b = "a"; b = "z"; b++){
            for(char c = "a"; c = "z"; c++){
                str[0] = a;
                str[1] = b;
                str[2] = c;
                str[3] = '\0';

                SHA256((unsigned char*)str, strlen(str), hash);

                char output[65];
                for(int i = 0; i<= 32; i++){
                    sprintf(output + i*2, "%02x", hash[i]);
                }
                if(strcmp(output, target) == 0){
                    printf("Password found: ", str);
                    return 0;
                }
            }
        }
    }
    return 0;
}