CC = gcc
CFLAGS = -O1 -Wall -Werror -g
OBJS = poly_5_05.o poly_5_06.o
EXEC = test_poly
LIBS = -lpapi

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

.PHONY: plot all clean

$(EXEC): $(OBJS) $(EXEC).o
	$(CC) $(CFLAGS) $(OBJS) $(EXEC).o -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

output.txt: $(EXEC)
	./$(EXEC) > output.txt

plot: output.txt
	gnuplot plot/p5_05.gp
	eog assign_5_5_and_5_6.png &

clean:
	rm -f *.o $(EXEC)
