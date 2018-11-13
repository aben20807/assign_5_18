CC = gcc
CFLAGS = -O1 -Wall -Werror -g
OBJS = poly_5_05.o poly_5_06.o poly_5_06_rev.o
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

plot1: $(EXEC)
	./$(EXEC) 1 > output.txt
	gnuplot plot/p5_05.gp
	eog assign_5_5_and_5_6.png &

plot2: $(EXEC)
	./$(EXEC) 2 > output.txt
	gnuplot plot/p5_05.gp
	eog assign_5_5_and_5_6.png &

plot3: $(EXEC)
	./$(EXEC) 3 > output.txt
	gnuplot plot/p5_06_vs_5_06_rev.gp
	eog 5_6_vs_5_6_rev.png &

clean:
	rm -f *.o $(EXEC)
