shm_proc: shm_processes.c
	gcc shm_processes.c -D_SVID_SOURCE -pthread -std=c99 -lpthread  -o shm_proc
example: example.c
	gcc example.c -pthread -std=c99 -lpthread  -o example

shared_mem: shared_mem.c
	gcc shared_mem.c -D_SVID_SOURCE -D_GNU_SOURCE -Wall -pthread -std=c99 -lpthread -std=c99 -Werror=cpp -pedantic  -o shared_mem
