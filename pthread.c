#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <libkern/OSCacheControl.h>

int main(void) {
    int val = pthread_jit_write_protect_supported_np();
    printf("pthread_jit_write_protect_supported_np: %d\n", val);
    fflush(stdout);

    int *mem = mmap(NULL, 4096, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    printf("mem = %p\n", mem);
    fflush(stdout);

    // pthread_jit_write_protect_np(0);
    // mov w0, 42
    mem[0] = 0x52800540;
    // ret
    mem[1] = 0xd65f03c0;
    // pthread_jit_write_protect_np(1);
    // mprotect(mem, 4096, PROT_READ|PROT_EXEC);

    sys_icache_invalidate(mem, 4096);

    int (*func)(void) = (int (*)(void))mem;
    int result = func();
    printf("result: %d\n", result);
    fflush(stdout);

    return 0;
}
