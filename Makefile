IDIR=src
CC=gcc-6
CFLAGS=-I$(IDIR)


CFLAGS += -std=gnu99 -Wall -pedantic
LDFLAGS += -L.

CFLAGS += -I/usr/local/Cellar/libscrypt/1.21/include
CFLAGS += -L/usr/local/Cellar/libscrypt/1.21/lib -lscrypt

ODIR=build
SDIR=src

SOURCES = $(wildcard src/*.c) $(wildcard src/*/*.c)
_OBJ = $(SOURCES:.c=.o)
OBJ = $(patsubst $(SDIR)/%,$(ODIR)/%,$(_OBJ))

all: triplesec tests

print-% : ; @echo $* = $($*)

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

TSEC_TST = $(filter $(ODIR)/test/%,$(OBJ))
TSEC_CLI = $(filter $(ODIR)/cli/%,$(OBJ))
TSEC_LIB = $(filter-out $(ODIR)/cli/%,$(filter-out $(ODIR)/test/%,$(OBJ)))

libtriplesec: $(TSEC_LIB)

triplesec: $(TSEC_CLI) $(TSEC_LIB)
	$(CC) -o $(ODIR)/triplesec $^ $(CFLAGS)

.PHONY: clean check

tests: $(TSEC_TST) $(TSEC_LIB)
	$(CC) -o $(ODIR)/triplesec_tests $^ $(CFLAGS)

check: tests
	$(ODIR)/triplesec_tests

clean:
	rm -fr $(ODIR)
