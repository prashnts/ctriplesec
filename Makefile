IDIR=src
CC=gcc
CFLAGS=-I$(IDIR)

CFLAGS += -std=gnu99 -Wall -pedantic
LDFLAGS += -L.

ODIR=build
SDIR=src

SOURCES = $(wildcard src/*.c) $(wildcard src/*/*.c)
_OBJ = $(SOURCES:.c=.o)
OBJ = $(patsubst $(SDIR)/%,$(ODIR)/%,$(_OBJ))

print-% : ; @echo $* = $($*)

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

triplesec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean _build_dir

_build_dir:
	mkdir -p $(ODIR)

clean:
	rm -fr $(ODIR)
	rm -f *~ triplesec
