#include "timer.h"

#include <sys/timerfd.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <poll.h>

ptimer_t create_timer() {
	ptimer_t timer;

	timer.fd = timerfd_create(CLOCK_MONOTONIC, 0);
	return timer;
}

void delete_timer(ptimer_t timer) {
	close(timer.fd);
}

void start_timer(ptimer_t timer) {
	struct itimerspec duration;
	struct pollfd pfd;
	uint64_t i;

	pfd.fd = timer.fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	duration.it_value.tv_nsec = 0;
	duration.it_interval.tv_sec = 0;
	duration.it_interval.tv_nsec = 0;
	duration.it_value.tv_sec = timer.sec_duration;
	timerfd_settime(timer.fd, 0, &duration, 0);
	if (poll(&pfd, 1, -1) > 0)
		read(timer.fd, &i, sizeof(uint64_t));
}

void stop_timer(ptimer_t timer) {
	struct itimerspec duration;

	duration.it_value.tv_sec = 0;
	duration.it_value.tv_nsec = 0;
	duration.it_interval.tv_sec = 0;
	duration.it_interval.tv_nsec = 0;
	timerfd_settime(timer.fd, 0, &duration, 0);
}
