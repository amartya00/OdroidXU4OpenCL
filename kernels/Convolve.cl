// -*-c-*-
__kernel void convolve2D(__global const float *input,
						 __global float *output,
						 __global const float *kern,
						 const int   inputSize)
{
	int rowNum = get_global_id(0) ;
    int colNum = get_global_id(1) ;
	int outputSize = inputSize - 2 ;
	output[outputSize * rowNum + colNum] = 0 ;
	output[outputSize * rowNum + colNum] +=
		input[inputSize * (rowNum + 0) + colNum + 0] * kern[0*3 + 0] +
		input[inputSize * (rowNum + 0) + colNum + 1] * kern[0*3 + 1] +
		input[inputSize * (rowNum + 0) + colNum + 2] * kern[0*3 + 2] +

		input[inputSize * (rowNum + 1) + colNum + 0] * kern[1*3 + 0] +
		input[inputSize * (rowNum + 1) + colNum + 1] * kern[1*3 + 1] +
		input[inputSize * (rowNum + 1) + colNum + 2] * kern[1*3 + 2] +

		input[inputSize * (rowNum + 2) + colNum + 0] * kern[2*3 + 0] +
		input[inputSize * (rowNum + 2) + colNum + 1] * kern[2*3 + 1] +
		input[inputSize * (rowNum + 2) + colNum + 2] * kern[2*3 + 2] ;
}
