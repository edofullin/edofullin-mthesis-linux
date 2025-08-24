#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define READ_CSR(csr)						\
({								\
	register unsigned long __v;				\
	__asm__ __volatile__ ("csrr %0, " #csr	\
			      : "=r" (__v) :			\
			      : "memory");			\
	__v;							\
});

unsigned retrieve_data(char* reg) {
    unsigned ret;

    if(!strcmp("cycle",reg)) {
        ret = READ_CSR(cycle);
    } else if(!strcmp("cycleh",reg)) {
        ret = READ_CSR(cycleh);
    } else if(!strcmp("mcicycle",reg)) {
        ret = READ_CSR(0x9d0);
    } else if(!strcmp("mcicycleh",reg)) {
        ret = READ_CSR(0x9d2);
    } else if(!strcmp("rdcycle",reg)) {
        asm volatile("rdcycle %0" : "=r"(ret));
    } else if(!strcmp("mcycle",reg)) {
        ret = READ_CSR(mcycle);
    }

    return ret;
}

void command_read(int argc, char** argv) {
    unsigned data;

    if(argc < 3) {
        printf("expected registers to read");
        exit(-1);
    }

    for(int i = 2; i < argc; ++i) {
        data = retrieve_data(argv[i]);
        printf("%s: 0x%x\n", argv[i], data);
        fflush(stdout);
    }
}

void command_test() {
    unsigned cycle, cycleh;
    uint64_t cycles;
    pid_t pid = fork();
    printf("pid %u\n", getpid());

    while(1) {
        cycle = READ_CSR(cycle);
        cycleh = READ_CSR(cycleh);
        cycles = ((uint64_t)cycleh << 32) | cycle;
        printf("pid %u cycles %lu\n", getpid(), cycles);
        fflush(stdout);

        sleep(5);
    }
}

int main(int argc, char** argv) {
    unsigned data;

    if(argc < 2) {
        printf("expected command (read|test)");
        exit(-1);
    }

    if(!strcmp("read", argv[1])) {
        command_read(argc, argv);
    } else if(!strcmp("test", argv[1])) {
        command_test();
    }

    

    return 0;
}