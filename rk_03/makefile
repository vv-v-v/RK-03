INCDIR := ./inc
SRCDIR := ./src
OUTDIR := ./out

vpath %.c $(SRCDIR)

CC := gcc
CFLAGS := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion 

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

.PHONY: build release run clean

build: release

release: app.exe

app.exe: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

run: app.exe
	./app.exe

clean:
	rm -fr $(OUTDIR)
	rm -f ./*.exe ./*.txt
