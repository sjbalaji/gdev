#ifndef __MADD_GPU_H
#define __MADD_GPU_H

#include <cuda.h>

#ifdef __KERNEL__
#include <linux/vmalloc.h>
#include <linux/time.h>
#define printf printk
#define malloc vmalloc
#define free vfree
#define gettimeofday(x, y) do_gettimeofday(x)
#else
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#define MODULE_FILE_NAME "mmult_gpu.cubin"
#define KERNEL_NAME "_Z12mmult_kernelPjS_S_jj"

/* Access an element of a matrix */
//#define get_element_index(i, j, cols) ((((i) + 1) * (cols)) + ((j) + 1))
#define get_element_index(i, j, cols) ((i) * (cols) + (j))

#define X_THREADS_PER_BLOCK 8
#define X_THREADS_PER_BLOCK_SHIFT 3
#define Y_THREADS_PER_BLOCK 8
#define Y_THREADS_PER_BLOCK_SHIFT 3

/* Contains pointers to device information from initialization */
struct device_info {
	CUdevice dev;
	CUcontext context;
	CUfunction kernel;
	CUmodule module;
};

int mmult_gpu_init(struct device_info *device_info);
int mmult_gpu(struct device_info *device_info, unsigned int *a, unsigned int *b,
 unsigned int *c, unsigned int rows, unsigned int cols);
int mmult_gpu_close(struct device_info *device_info);

#endif /* __MADD_GPU_H */
