CC=gcc
CFLAGS=-I.
DEPS = MergesortMulti.h MergesortSingle.h
OBJ_MULTI = MergesortMulti.o 
OBJ_SINGLE = MergesortSingle.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MergesortMulti: $(OBJ_MULTI)
	$(CC) -o $@ $^ $(CFLAGS)

MergesortSingle: $(OBJ_SINGLE)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_MULTI) $(OBJ_SINGLE) MergesortMulti MergesortSingle *.o