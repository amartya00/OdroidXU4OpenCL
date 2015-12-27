/**
 * Host program con 2D convolution
 */


#include "CLWrapper"
#include "Utils"

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#define SIZE 10

int main()
{
	std::vector <std::string> files = {"kernels/Convolve.cl"} ;
    std::string logFile = "log.txt" ;
    OdroidXU4::CLWrapper C1 ;


    // Prepare mem objects
	float *input = MyUtils::getMatrix<float>(SIZE, SIZE, MyUtils::MemoryMode::FIXED, 1) ;
	float *output = MyUtils::getMatrix<float>(SIZE - 2, SIZE - 2, MyUtils::MemoryMode::FIXED, 0) ;
	float kernel[] = {1, 1, 1,
					  1, 0, 1,
					  1, 1, 1} ;

    try {
        C1.setup(files, logFile) ;
        // Get buffers
        OdroidXU4::CLBuffer<float, CL_MEM_READ_ONLY > bInput  = C1.getBigBuffer<float, CL_MEM_READ_ONLY >(input, SIZE * SIZE)      ;
		OdroidXU4::CLBuffer<float, CL_MEM_WRITE_ONLY> bOutput = C1.getBigBuffer<float, CL_MEM_WRITE_ONLY>(output, (SIZE - 2) * (SIZE - 2)) ;
		OdroidXU4::CLBuffer<float, CL_MEM_READ_ONLY > bKernel = C1.getBigBuffer<float, CL_MEM_READ_ONLY >(kernel, 9)        ;

        // Flush buffers
        bInput.flushWriteBuffer() ;
        bKernel.flushWriteBuffer() ;

        // Execute kernel
        OdroidXU4::KernelExecutor <cl::Buffer&, cl::Buffer&, cl::Buffer&, int> k = 
            C1.getKernelExecutorBig<cl::Buffer&, cl::Buffer&, cl::Buffer&, int>("convolve2D", cl::NullRange, cl::NDRange(SIZE - 2, SIZE - 2, 1), cl::NullRange) ;
        k(bInput.getBuffer(), bOutput.getBuffer(), bKernel.getBuffer(), SIZE);

        // Read buffer
        bOutput.getReadBuffer() ;

    } catch (OdroidXU4::CLWrapperException ex) {
        std::cout << ex.getMessage() << "\n" ;
        return 1 ;
    } catch (OdroidXU4::LoggerException ex) {
        std::cout << ex.getMessage() << "\n" ;
        return 1 ;
    }
    
    // Flush input buffers and execute kernel and read output buffer
    
    MyUtils::displayMatrix(output, SIZE - 2, SIZE - 2) ;
    return 0 ;
}
