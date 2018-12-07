CC = gcc
CFLAGS = -O1 -Wall -Werror
EXEC = test_poly
CPU_FREQ = sudo cpupower frequency-set -g
SUBDIR = ./dynamic_gen
OBJS = $(SUBDIR)/gen_plot.o $(SUBDIR)/dynamic_poly.o
INCLUDES = -I$(SUBDIR)
LIBS = -ldl
ARGS ?= 1,5 1,6 1,10 1,12

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

.PHONY: default plot compare all clean

./dynamic_gen/%.o:
	$(MAKE) -C $(SUBDIR)

$(EXEC): $(OBJS) $(EXEC).o
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(EXEC).o -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

boost:
	@$(CPU_FREQ) performance > /dev/null
	@sleep 1

recover:
	@$(CPU_FREQ) powersave > /dev/null
	@sleep 1

default: $(EXEC) boost
	./$(EXEC) default
	@$(MAKE) -s recover

plot: $(EXEC) boost
	./$(EXEC) plot $(ARGS)
	@$(MAKE) -s recover
	gnuplot dynamic_gen/plot.gp
	eog poly.png &

compare: $(EXEC) boost
	./$(EXEC) compare $(ARGS)
	@$(MAKE) -s recover

clean:
	rm -f *.so *.o *.gp $(EXEC)
	$(MAKE) -s -C $(SUBDIR) clean
