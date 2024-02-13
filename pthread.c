#include <pthread.h>
#include <stdio.h>

int main(void) {
    int val = pthread_jit_write_protect_supported_np();
    printf("pthread_jit_write_protect_supported_np: %d\n", val);
    return 0;
}
