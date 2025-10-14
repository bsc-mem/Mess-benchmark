CC = gcc
#CC = icc
MPICC = icx
CFLAGS = -march=native -Wall
#CFLAGS += -fopenmp
LDFLAGS = -pthread -lrt
#CFLAGS += -no-multibyte-chars added to work around the error Catastrophic error: could not set locale "" to allow processing of multibyte characters

MPI_LIB = -L$(I_MPI_ROOT)/lib
MPI_INCLUDE = -I$(I_MPI_ROOT)/include

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
	$(MPICC) $(CFLAGS) $(MPI_INCLUDE) -O3 -c $< -o $@

$(TARGET): $(BUILDDIR)/nop.o $(BUILDDIR)/utils.o $(BUILDDIR)/stream_mpi_c.o
	$(MPICC) $(CFLAGS) $(MPI_INCLUDE) $(MPI_LIB) -O3 $(LDFLAGS) $^ -o $@

clean:
	rm -f $(BUILDDIR)/*.o *.x

