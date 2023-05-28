#include <cstdio>
#include <cstdlib>

#include <hip/hip_runtime.h>



void print_properties_for_gpu(int gpu_idx)
{
    hipDeviceProp_t p;
    hipGetDeviceProperties(&p, gpu_idx);

    printf("Device %d:\n", gpu_idx);
    printf("  Name: %s\n", p.name);
    printf("  GCN architecture: %d\n", p.gcnArch);
    printf("  Compute units: %d\n", p.multiProcessorCount);
    printf("  Warp size: %d\n", p.warpSize);
    printf("  ECC memory enabled: %s\n", p.ECCEnabled ? "yes" : "no");
    printf("  Global memory: %ld MiB\n", p.totalGlobalMem >> 20);
    printf("  L2 cache: %d KiB\n", p.l2CacheSize >> 10);
    printf("  Max shared memory per CU: %ld KiB\n", p.maxSharedMemoryPerMultiProcessor >> 10);
    printf("  Shared memory per workgroup: %ld KiB\n", p.sharedMemPerBlock >> 10);
    printf("  Registers per workgroup: %d\n", p.regsPerBlock);
}



int main(int argc, char ** argv)
{
    int device = -1;
    int device_count;

    if(argc > 1)
        device = atoi(argv[1]);

    hipGetDeviceCount(&device_count);

    printf("There are %d HIP devices detected\n\n", device_count);

    if(device >= 0)
    {
        if(device < device_count)
        {
            print_properties_for_gpu(device);
        }
        else
        {
            printf("Invalid device index\n");
        }
    }
    else
    {
        for(device = 0; device < device_count; device++)
        {
            if(device != 0)
                printf("\n");
            print_properties_for_gpu(device);
        }
    }
}
