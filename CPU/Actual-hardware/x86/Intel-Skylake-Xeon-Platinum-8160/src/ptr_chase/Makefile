CC=gcc
TARGET=ptr_chase
TARGET_ARRAYGEN=arraygen

# Architectural details
cache_line_size = 64

# Benchmark configuration
array_size = $(shell bc <<< $${PTRCHASE_ARRAY_SIZE}) # using calculator to improve number readability
instructions = ${PTRCHASE_NUM_INSTRUCTIONS}
iterations = ${PTRCHASE_NUM_ITERATIONS}
# Compute derived parameters
array_elems:=$(shell bc <<< "$(array_size) / $(cache_line_size)")
loop_instr:=$(shell bc <<< "$(instructions) / $(iterations)")

all: ptr_chase array

ptr_chase: ptr_chase.c loop.h
	$(CC) -O0 -DARRAY_ELEMS=$(array_elems) -DITERS=$(iterations) -o ptr_chase ptr_chase.c

loop.h: loop_template.h
	awk '{for(i=0; i<${loop_instr}; i++)print}' loop_template.h > loop.h

arraygen: arraygen.c
	$(CC) -O3 -DARRAY_ELEMS=$(array_elems) -o $(TARGET_ARRAYGEN) arraygen.c

array: arraygen
	./$(TARGET_ARRAYGEN)

clean:
	rm -f $(TARGET) $(TARGET_ARRAYGEN)
	rm -f loop.h

fullclean: clean
	rm -f array.dat

.PHONY: all array clean fullclean
