#include "types.h"
#include "riscv.h"  // Add this
#include "param.h"  // Add this
#include "spinlock.h"  // Add this
#include "memlayout.h" // Add this
#include "defs.h"
#include "sha256.h"

void
ksha256(void)
{
    const char *test_string = "Hello, World!";
    unsigned char hash[32];

    // Call our existing SHA256 implementation
    sha256((const unsigned char*)test_string, strlen(test_string), hash);
    
    // Print using kernel printf
    printf("Kernel SHA256:\n");
    printf("Input: %s\n", test_string);
    printf("SHA-256 Hash: ");
    for(int i = 0; i < 32; i++) {
        if(hash[i] < 16) {
            printf("0");
        }
        printf("%x", hash[i]);
    }
    printf("\n");
}