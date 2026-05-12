#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("Грешка в OpenSSL!\n");
}

int main() {
    unsigned char *key = (unsigned char *)"0123456789012345";
    unsigned char *iv = (unsigned char *)"0123456789012345";
    unsigned char *plaintext = (unsigned char *)"Top Secret Message!";
    
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];
    int len, ciphertext_len, decrypted_len;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    // --- КРИПТИРАНЕ ---
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, strlen((char *)plaintext));
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    printf("Ciphertext is %d bytes long\n", ciphertext_len);

    // --- ДЕКРИПТИРАНЕ ---
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len);
    decrypted_len = len;

    // DecryptFinal връща грешка, ако padding-ът е невалиден
    if (EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len) <= 0) {
        handleErrors();
    } else {
        decrypted_len += len;
        decryptedtext[decrypted_len] = '\0';
        printf("Decrypted text: %s\n", decryptedtext);
    }

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}