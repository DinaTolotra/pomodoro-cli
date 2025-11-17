#ifndef TIMER_H
#define TIMER_H

typedef struct {
	int fd;
	unsigned int sec_duration;
} ptimer_t;

ptimer_t create_timer();
void delete_timer(ptimer_t timer);

void start_timer(ptimer_t timer);
void stop_timer(ptimer_t timer);

#endif // TIMER_H
