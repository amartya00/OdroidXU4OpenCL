/**
 * Main class
 */


#include "CLWrapper"
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

int main()
{
    const int len = 10 ;

    std::string buffer =
        "__kernel void simpleAdd(__global const float *A, \
                                 __global const float *B, \
                                 __global float *C) \
        { \
            int gid = get_global_id(0) ; \
            C[gid] = A[gid] + B[gid] ; \
        }";
    std::string logFile = "log.txt" ;
    OdroidXU4::CLWrapper C1 ;

    // Prepare mem objects
    int A[] = {1,2,3,4,5,6,7,8,9,10} ;
    int B[] = {1,2,3,4,5,6,7,8,9,10} ;
    int C[10] ;

    try {
        C1.setup(buffer, logFile) ;
        // Get buffers
        OdroidXU4::CLBuffer<int, CL_MEM_READ_ONLY > bA = C1.getBigBuffer<int, CL_MEM_READ_ONLY >(A, 10) ;
        OdroidXU4::CLBuffer<int, CL_MEM_READ_ONLY > bB = C1.getBigBuffer<int, CL_MEM_READ_ONLY >(B, 10) ;
        OdroidXU4::CLBuffer<int, CL_MEM_WRITE_ONLY> bC = C1.getBigBuffer<int, CL_MEM_WRITE_ONLY>(C, 10) ;

        // Flush buffers
        bA.flushWriteBuffer() ;
        bB.flushWriteBuffer() ;

        // Execute kernel
        C1.getKernelExecutorBig<0, 10, 0, cl::Buffer&, cl::Buffer&, cl::Buffer&>("simpleAdd")(bA.getBuffer(), bB.getBuffer(), bC.getBuffer());

        // Read buffer
        bC.getReadBuffer() ;

    } catch (OdroidXU4::CLWrapperException ex) {
        std::cout << ex.getMessage() << "\n" ;
        return 1 ;
    } catch (OdroidXU4::LoggerException ex) {
        std::cout << ex.getMessage() << "\n" ;
        return 1 ;
    }
    
    // Flush input buffers and execute kernel and read output buffer
    
    for(int i = 0; i < len; i++) {
        std::cout << C[i] <<"\n" ;
    }
    return 0 ;
}
