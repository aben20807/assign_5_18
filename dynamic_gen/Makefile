CC = gcc
CFLAGS = -O1 -Wall -Werror
GEN_EXEC = gen_poly
DYNAMIC = dynamic_poly
TARGETS = $(DYNAMIC).o gen_plot.o

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
	rm -f *.o *.gp $(TARGETS) $(DYNAMIC).c $(DYNAMIC).h $(GEN_EXEC)
