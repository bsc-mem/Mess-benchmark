CC = gcc
MPICC = mpicc
CFLAGS = -march=native -Wall
CFLAGS += -fopenmp
LDFLAGS = -pthread -lrt

SRCDIR=src
BUILDDIR=build


PRG_SUFFIX=.x
TARGET=stream_mpi$(PRG_SUFFIX)

all: init $(TARGET)

init:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/nop.o: $(SRCDIR)/nop.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/utils.o: $(SRCDIR)/utils.c
	$(CC) $(CFLAGS) -Wno-unused-but-set-variable -O0 -c $< -o $@

$(BUILDDIR)/stream_mpi_c.o: $(SRCDIR)/stream_mpi.c
	$(MPICC) $(CFLAGS)  -O0 -c $< -o $@

$(TARGET): $(BUILDDIR)/nop.o $(BUILDDIR)/utils.o $(BUILDDIR)/stream_mpi_c.o
	$(MPICC) $(CFLAGS)  -O0 $(LDFLAGS) $^ -o $@

clean:
	rm -f $(BUILDDIR)/*.o *.x

