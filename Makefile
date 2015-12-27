CC     = clang++
INC    = headers/
CFLAGS = --std=c++11 -Wall
LIBS   = -lOpenCL

default:
	@ echo "Here are all build gtargets: "
	@ echo "-----------------------------"
	@ echo "[1] convolve - 2D convolution "
	@ echo ""
	@ echo "** all"
	@ echo "** clean"

convolve:
	$(CC) -o build/Convolve src/convolve.cc -I $(INC) $(CFLAGS) $(LIBS) ;

all: convolve

clean:
	@ rm -rf build/* 2>&1 >> /dev/null
	@ echo "Cleaned up build folder"

