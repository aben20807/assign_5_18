CC = gcc
CFLAGS = -O1 -Wall
GEN_EXEC = gen_poly
DYNAMIC = dynamic_poly
TARGETS = $(DYNAMIC).o

all: $(TARGETS)

$(TARGETS): %.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(DYNAMIC).c: $(GEN_EXEC)
	./$(GEN_EXEC)

$(GEN_EXEC): $(GEN_EXEC).o
	$(CC) $(CFLAGS) $(GEN_EXEC).o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(GEN_EXEC) $(TARGETS) $(DYNAMIC).c $(DYNAMIC).h
