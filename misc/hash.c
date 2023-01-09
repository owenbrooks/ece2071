#include <tomcrypt.h>

unsigned char* hashSHA256(const char* input, unsigned long inputSize);

int main(void) {
    unsigned long inputSize = 5;
    const char * input = "input string";
    unsigned char* hashResult = hashSHA256(input, inputSize);
    printf("%s", hashResult);

    return 0;
}

/**
 * Hashes a given sequence of bytes using the SHA256 algorithm
 * @param input The input sequence pointer
 * @param inputSize The size of the input sequence
 * @return A malloc-allocated pointer to the resulting data. 20 bytes long.
 */
unsigned char* hashSHA256(const char* input, unsigned long inputSize) {
    //Initial
    unsigned char* hashResult = (unsigned char*)malloc(sha256_desc.hashsize);
    //Initialize a state variable for the hash
    hash_state md;
    sha256_init(&md);
    //Process the text - remember you can call process() multiple times
    sha256_process(&md, (const unsigned char*) input, inputSize);
    //Finish the hash calculation
    sha256_done(&md, hashResult);
    // Return the result
    return hashResult;
}