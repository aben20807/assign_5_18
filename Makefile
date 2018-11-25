CC = gcc
CFLAGS = -O1 -Wall -Werror -g
OBJS = poly_funcs_5_5.o poly_funcs_5_6.o
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
	gnuplot plot/5_5_vs_5_6_original.gp
	eog 5_5_vs_5_6_original.png &

plot2: $(EXEC)
	taskset -c 0 nice --adjustment=20 ./$(EXEC) 2 > output.txt
	gnuplot plot/5_5_vs_5_5_rev.gp
	eog 5_5_vs_5_5_rev.png &

plot3: $(EXEC)
	./$(EXEC) 3 > output.txt
	gnuplot plot/5_6_vs_5_6_rev.gp
	eog 5_6_vs_5_6_rev.png &

plot4: $(EXEC)
	./$(EXEC) 4 > output.txt
	gnuplot plot/5_05_comparison_all.gp
	eog 5_05_comparison_all.png &

clean:
	rm -f *.o $(EXEC)
