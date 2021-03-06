#ifndef __MCOPY_GPU_H
#define __MCOPY_GPU_H

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

int mcopy_gpu_init(struct device_info *device_info);
int mcopy_gpu(struct device_info *device_info, CUdeviceptr *a_dev, CUdeviceptr
 *b_dev, CUdeviceptr *c_dev, unsigned int rows, unsigned int cols);
int mcopy_gpu_close(struct device_info *device_info);

#endif /* __MCOPY_GPU_H */
