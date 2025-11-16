#include <sys/timerfd.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <poll.h>

int init_timer();
void start_timer(int fd, int sec_duration);

int main(void) {
	int fd;
	int stop;
	int duration;
	int is_break;
	char buf[2];

	stop = 0;
	is_break = 0;
	fd = init_timer();
	while (!stop) {
		duration = 60 * (is_break)? 5: 25;
		start_timer(fd, duration);
		write(1, "Session ended!\n", 15);
		write(1, "Continue? (Y/n) ", 16);
		read(0, buf, 2);
		stop = buf[0] == 'n';
		is_break = !is_break;
	}
	close(fd);
	return (0);
}

int init_timer() {
	return timerfd_create(CLOCK_MONOTONIC, 0);
}

void start_timer(int fd, int sec_duration) {
	struct itimerspec duration;
	struct pollfd pfd;
	uint64_t i;

	pfd.fd = fd;
	pfd.revents = 0;
	pfd.events = POLLIN;
	duration.it_value.tv_nsec = 0;
	duration.it_interval.tv_sec = 0;
	duration.it_interval.tv_nsec = 0;
	duration.it_value.tv_sec = sec_duration;
	timerfd_settime(pfd.fd, 0, &duration, 0);
	if (poll(&pfd, 1, -1) > 0)
		read(pfd.fd, &i, sizeof(uint64_t));
}
