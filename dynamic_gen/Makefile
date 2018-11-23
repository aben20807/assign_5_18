CC = gcc
CFLAGS = -O1 -Wall -g
GEN_EXEC = gen_poly
DYNAMIC_C = dynamic_poly.c
DYNAMIC_H = dynamic_poly.h
TARGETS = dynamic_poly.o

all: $(TARGETS)

$(TARGETS): %.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(DYNAMIC_C): $(GEN_EXEC)
	./$(GEN_EXEC)

$(GEN_EXEC): $(GEN_EXEC).o
	$(CC) $(CFLAGS) $(GEN_EXEC).o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(GEN_EXEC) $(TARGETS) $(DYNAMIC_C) $(DYNAMIC_H)
