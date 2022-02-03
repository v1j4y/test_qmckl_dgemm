SRCDIR=src/
OBJDIR=src/
OBJEXT=o
SRCEXT=c
SOURCES= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
EXE=dgemm_test
CPPFLAGS=-I$(CONDA_PREFIX)/include
CFLAGS=-I$(CONDA_PREFIX)/include 
LDFLAGS=-L$(CONDA_PREFIX)/lib/ -lqmckldgemm

all: $(EXE)

$(OBJDIR)/.%o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LDFLAGS)

clean: 
	rm $(EXE) $(OBJECTS)

.PHONY: all clean
