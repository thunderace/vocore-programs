include ../makedefs

INCLUDES = 
CFLAGS = 
#LIBS = -ldl
LIBS = 
LDFLAGS =

PROGRAM = IO
OBJ = main.o RT5350.o 

all: $(PROGRAM)


%.o: %.c
	@$(CC) -c $< $(INCLUDES) $(CFLAGS)
	@echo "	CC	"$@

$(PROGRAM): $(OBJ)
	@$(CCLD) -o $@ $(OBJ) $(LDFLAGS) $(LIBS)
	@echo "	CCLD	"$@

.SUFFIXES: all clean

clean:
	-rm -f *.o
	-rm -f $(PROGRAM)

upload: $(PROGRAM)
	scp $(PROGRAM) root@vocore1:/root & ssh root@vocore1
