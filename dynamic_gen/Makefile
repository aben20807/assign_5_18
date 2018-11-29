CC = gcc
CFLAGS = -O1 -Wall -Werror
TARGETS = gen_poly.o
DYNAMICS = dynamic_poly.c dynamic_poly.h

all: $(TARGETS)

$(TARGETS): %.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(GEN_EXEC): $(GEN_EXEC).o
	$(CC) $(CFLAGS) $(GEN_EXEC).o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGETS) $(DYNAMICS)
