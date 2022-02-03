SRC=dgemm_test.c
OBJ=dgemm_test.o
EXE=dgemm_test

all: $(EXE)

$(OBJ): $(SRC)
	$(CC) -c $(SRC)  -I$(CONDA_PREFIX)/include

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) -L$(CONDA_PREFIX)/lib/ -lqmckldgemm

clean: 
	rm $(EXE) $(OBJ)
