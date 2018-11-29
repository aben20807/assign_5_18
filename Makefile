CC = gcc
CFLAGS = -O1 -Wall -Werror
OBJS = ./dynamic_gen/gen_poly.o ./dynamic_gen/gen_plot.o
EXEC = test_poly
CPU_FREQ = sudo cpupower frequency-set -g
SUBDIR = ./dynamic_gen
INCLUDES = -I$(SUBDIR)
LIBS = -ldl

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

.PHONY: plot1 plot2 plot3 plot4 all clean

./dynamic_gen/%.o:
	$(MAKE) -C $(SUBDIR)

$(EXEC): $(OBJS) $(EXEC).o
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(EXEC).o -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

boost:
	@sudo cpupower frequency-set -g performance > /dev/null
	@sleep 1
	@cat /proc/cpuinfo | grep MHz

recover:
	@sudo cpupower frequency-set -g powersave > /dev/null
	@sleep 1
	@cat /proc/cpuinfo | grep MHz

default: $(EXEC) boost
	./$(EXEC) 
	@$(MAKE) recover

plot1: $(EXEC) boost
	./$(EXEC) 1 > output.txt
	gnuplot plot/5_5_vs_5_6_original.gp
	eog 5_5_vs_5_6_original.png &
	@$(MAKE) recover

plot2: $(EXEC) boost
	taskset -c 0 ./$(EXEC) 2 > output.txt
	gnuplot plot/5_5_vs_5_5_rev.gp
	eog 5_5_vs_5_5_rev.png &
	@$(MAKE) recover

plot3: $(EXEC) boost
	./$(EXEC) 3 > output.txt
	gnuplot plot/5_6_vs_5_6_rev.gp
	eog 5_6_vs_5_6_rev.png &
	@$(MAKE) recover

plot4: $(EXEC) boost
	taskset -c 1 ./$(EXEC) 4 > output.txt
	gnuplot plot/5_05_comparison_all.gp
	eog 5_05_comparison_all.png &
	@$(MAKE) recover

clean:
	rm -f *.so *.o *.gp $(EXEC)
	$(MAKE) -C $(SUBDIR) clean
