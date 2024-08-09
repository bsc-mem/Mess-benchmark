nvcc=nvcc

PAPI_HOME=/apps/ACC/PAPI/7.1.0/

main: main.cu
	$(nvcc) -I$(PAPI_HOME)/include -o main main.cu -D__x86__=$(x86_ISA) -L$(PAPI_HOME)/lib -lpapi 

clean:
	rm -f main
