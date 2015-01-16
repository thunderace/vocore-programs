include ../makedefs

CROSS_COMPILE ?= $(ROOT)/mipsel-openwrt-linux-uclibc-

CC = $(CROSS_COMPILE)gcc
INCLUDES = 
CFLAGS = 

CCLD = $(CC)
LIBS = -ldl
LDFLAGS =

PROGRAM = test
OBJ = $(PROGRAM).o 

all: $(PROGRAM)


%.o: %.c
	@$(CC) -c $< $(INCLUDES) $(CFLAGS)
	@echo "	CC	"$@

$(PROGRAM): $(OBJ)
	@$(CCLD) -o $@ $(OBJ) $(LDFLAGS) $(LIBS)
	@echo "	CCLD	"$@

.SUFFIXES: all clean plugins

plugins: $(PLUGINS)

clean:
	-rm -f *.o
	-rm -f $(PROGRAM)

upload: $(PROGRAM)
	scp $(PROGRAM) root@vocore1:/root

