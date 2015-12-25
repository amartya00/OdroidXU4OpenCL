CC     = clang++
SRC    = src/main.cc
INC    = headers/
CFLAGS = --std=c++11 -Wall
LIBS   = -lOpenCL
BIN    = Wrapper

bin:
	$(CC) -o build/$(BIN) $(SRC) -I $(INC) $(CFLAGS) $(LIBS) ;

