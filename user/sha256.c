#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int result = sha256();  
    if(result < 0) {
        printf("sha256 failed\n");
        exit(1);
    }
    exit(0);
}