#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int a = 0;
int condvar_id;
int mutex_id;

void first()
{
	sleep(10);
	puts("First work, Change A --> 1 and wakeup Second");
	mutex_lock(mutex_id);
	a = 1;
	puts("First changed A --> 1");
	condvar_signal(condvar_id);
	mutex_unlock(mutex_id);
	puts("First finish the job");
	exit(0);
}

void second()
{
	puts("Second want to continue,but need to wait A=1");
	mutex_lock(mutex_id);
	while (a == 0) {
		printf("Second : A is %d\n", a);
		condvar_wait(condvar_id, mutex_id);
	}
	mutex_unlock(mutex_id);
	printf("A is %d, Second can work now\n", a);
	exit(0);
}

int main()
{
	assert((condvar_id = condvar_create()) >= 0);
	assert((mutex_id = mutex_blocking_create()) >= 0);
	init_thread_io_buffer();
	int t1 = thread_create(first, 0);
	int t2 = thread_create(second, 0);
	waittid(t1);
	waittid(t2);
	puts("test_condvar passed!");
	return 0;
}