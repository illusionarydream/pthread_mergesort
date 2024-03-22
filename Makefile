CC=gcc
CFLAGS=-Wall -pthread
TARGETS = MergesortMulti MergesortSingle

all: $(TARGETS)

MergesortSingle: MergesortSingle.c
	$(CC) $(CFLAGS) -o $@ $^

MergesortMulti: MergesortMulti.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(TARGETS)