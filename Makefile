CC = gcc
CFLAGS = -O1 -Wall -Werror
# OBJS = ./dynamic_gen/dynamic_poly.o ./dynamic_gen/gen_poly.o ./dynamic_gen/gen_plot.o
EXEC = test_poly
CPU_FREQ = sudo cpupower frequency-set -g
SUBDIR = ./dynamic_gen
OBJS = $(SUBDIR)/gen_plot.o $(SUBDIR)/dynamic_poly.o
INCLUDES = -I$(SUBDIR)
LIBS = -ldl
ARGS ?= 1,1 1,5 8,8

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
	@$(CPU_FREQ) performance > /dev/null
	@sleep 1
	@cat /proc/cpuinfo | grep MHz

recover:
	@$(CPU_FREQ) powersave > /dev/null
	@sleep 1
	@cat /proc/cpuinfo | grep MHz

default: $(EXEC) boost
	./$(EXEC) default
	@$(MAKE) -s recover

plot: $(EXEC) boost
	./$(EXEC) plot $(ARGS)
	@$(MAKE) -s recover
	gnuplot dynamic_gen/plot.gp
	eog poly.png

compare: $(EXEC) boost
	./$(EXEC) compare $(ARGS)
	@$(MAKE) -s recover

# plot1: $(EXEC) boost
# 	./$(EXEC) 1 > output.txt
# 	gnuplot plot/5_5_vs_5_6_original.gp
# 	eog 5_5_vs_5_6_original.png &
# 	@$(MAKE) -s recover
#
# plot2: $(EXEC) boost
# 	taskset -c 0 ./$(EXEC) 2 > output.txt
# 	gnuplot plot/5_5_vs_5_5_rev.gp
# 	eog 5_5_vs_5_5_rev.png &
# 	@$(MAKE) -s recover
#
# plot3: $(EXEC) boost
# 	./$(EXEC) 3 > output.txt
# 	gnuplot plot/5_6_vs_5_6_rev.gp
# 	eog 5_6_vs_5_6_rev.png &
# 	@$(MAKE) -s recover
#
# plot4: $(EXEC) boost
# 	taskset -c 1 ./$(EXEC) 4 > output.txt
# 	gnuplot plot/5_05_comparison_all.gp
# 	eog 5_05_comparison_all.png &
# 	@$(MAKE) -s recover

clean:
	rm -f *.so *.o *.gp $(EXEC)
	$(MAKE) -s -C $(SUBDIR) clean
