#include <stdio.h>
#include <unistd.h>

#include "timer.h"

int main(void) {
	ptimer_t timer;
	int stop;
	int is_break;
	char buf[2];

	stop = 0;
	is_break = 0;
	timer = create_timer();
	while (!stop) {
		timer.sec_duration = 60 * ((is_break)? 5: 25);
		printf("Session started(%is)!\n", timer.sec_duration);
		start_timer(timer);
		printf("Session ended!\n");
		printf("Continue? (Y/n) ");
		read(0, buf, 2);
		stop = buf[0] == 'n';
		is_break = !is_break;
	}
	delete_timer(timer);
	return (0);
}
