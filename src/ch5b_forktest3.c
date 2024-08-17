#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int num = 0;
    int pid = fork();
    if (pid == 0) {
        num++;
        printf("child: %d\n", num);
        printf("child: %p\n\n", &num);
        exit(0);
    } else {
        int xstate = 0;
        assert(wait(&xstate) > 0);
        assert_eq(xstate, 0);
        printf("p: %d\n", num);
        printf("p: %p\n", &num);
    }
	
	return 0;
}
