.SUFFIXES:
.SUFFIXES: .c .h .o

CC	= gcc
INCLDIR	= include/
BINDIR	= bin/
OBJDIR	= obj/
SRCDIR	= src/

_BIN	= a.out
BIN	= $(addprefix $(BINDIR), $(_BIN))

# files; here all object files will be stored in $(OBJDIR), with the
# same base names as corresponding c files from SRCDIR
SRC	= $(wildcard src/*.c)
_OBJS	= $(patsubst src/%.c, %.o, $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(_OBJS))

# compilation flags
CFLAGS = -Werror -std=c99 -pedantic -g -I$(INCLDIR)
OFLAGS =


# compile binary and object files
.PHONY: all
all: $(BIN)

$(BIN): $(BINDIR) $(OBJS)
	$(CC) $(OFLAGS) $(OBJS) -lncurses -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJS): $(OBJDIR) $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)


# clean entire project directory
.PHONY: clean
clean:
	- rm -rf $(BINDIR) $(OBJDIR)
