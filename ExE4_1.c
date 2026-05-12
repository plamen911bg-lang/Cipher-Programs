#include <stdio.h>
#include <openssl/evp.h>

void calculate_file_hash(const char *filename, const EVP_MD *algorithm) {
    FILE *f = fopen(filename, "rb");
    if (!f) return;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, algorithm, NULL);

    unsigned char buf[1024], hash[EVP_MAX_MD_SIZE];
    unsigned int len;
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) 
        EVP_DigestUpdate(ctx, buf, n);

    EVP_DigestFinal_ex(ctx, hash, &len);
    
    for (int i = 0; i < len; i++) printf("%02x", hash[i]);
    printf("\n");

    EVP_MD_CTX_free(ctx);
    fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    printf("File 1: %s\nFile 2: %s\n\n", argv[1], argv[2]);

    printf("--- MD5 Hashes ---\n");
    calculate_file_hash(argv[1], EVP_md5());
    calculate_file_hash(argv[2], EVP_md5());

    printf("\n--- SHA-256 Hashes ---\n");
    calculate_file_hash(argv[1], EVP_sha256());
    calculate_file_hash(argv[2], EVP_sha256());

    return 0;
}