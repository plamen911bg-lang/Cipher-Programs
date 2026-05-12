#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void process_file(const char *mode, FILE *fin, FILE *fout, unsigned char *key) {
    unsigned char iv[16] = {0}; // За учебни цели IV е нулев, в реални условия е случаен
    unsigned char in_buf[1024], out_buf[1024 + EVP_MAX_BLOCK_LENGTH];
    int in_len, out_len;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    
    int is_encrypt = (strcmp(mode, "enc") == 0);
    
    if (is_encrypt)
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    else
        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    while ((in_len = fread(in_buf, 1, 1024, fin)) > 0) {
        if (is_encrypt)
            EVP_EncryptUpdate(ctx, out_buf, &out_len, in_buf, in_len);
        else
            EVP_DecryptUpdate(ctx, out_buf, &out_len, in_buf, in_len);
        fwrite(out_buf, 1, out_len, fout);
    }

    if (is_encrypt)
        EVP_EncryptFinal_ex(ctx, out_buf, &out_len);
    else
        EVP_DecryptFinal_ex(ctx, out_buf, &out_len);
    
    fwrite(out_buf, 1, out_len, fout);
    EVP_CIPHER_CTX_free(ctx);
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s [enc|dec] <input_file> <output_file> <key_string>\n", argv[0]);
        return 1;
    }

    unsigned char key[32] = {0};
    strncpy((char *)key, argv[4], 32);

    FILE *fin = fopen(argv[2], "rb");
    FILE *fout = fopen(argv[3], "wb");

    if (!fin || !fout) {
        perror("File error");
        return 1;
    }

    process_file(argv[1], fin, fout, key);

    fclose(fin);
    fclose(fout);
    printf("Done!\n");

    return 0;
}