CC := $(CROSS_COMPILE)gcc

CFLAGS := -Wall -Werror -O2

.PHONY: clean

SysClkCheck: SysClkCheck.c
	$(CC) $(CFLAGS) -o SysClkCheck SysClkCheck.c
clean:
	$(RM) SysClkCheck
