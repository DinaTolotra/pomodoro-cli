build/pomodoro-cli: build main.c
	@gcc -Wextra -Wall -Werror -o build/pomodoro-cli -g main.c source/timer.c -Iinclude

build:
	@mkdir -p build

clean:
	@rm -r build
