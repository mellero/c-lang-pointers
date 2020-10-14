CFLAGS=-Wall -Wextra -Werror
SRCS=$(wildcard *.c)
OBJS=$(SRCS:c=o)
PROGS=$(SRCS:.c=)

.phony: all
all: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o challenge

$(OBJS): $(SRCS)
	gcc -c $(SRCS)

clean:
	rm -f $(PROGS) $(OBJS) challenge