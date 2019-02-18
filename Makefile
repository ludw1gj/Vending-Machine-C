CC = gcc

CFLAGS = -Wall -ansi
INCLUDES = -I./src/
LFLAGS = -L/usr/include/
SRCS = src/*.c
MAIN = bin/VM

all: $(MAIN)
	@echo $(MAIN) has compiled successfully

$(MAIN): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS) $(LFLAGS)

clean:
	$(RM) $(MAIN)