#include <cstdio>
#include <cstdlib>


void print_properties_for_gpu(int gpu_idx)
{
    cudaDeviceProp p;
    cudaGetDeviceProperties(&p, gpu_idx);

    printf("Device %d:\n", gpu_idx);
    printf("  Name: %s\n", p.name);
    printf("  Compute capability: %d.%d\n", p.major, p.minor);
    printf("  Multiprocesor count: %d\n", p.multiProcessorCount);
    printf("  Warp size: %d\n", p.warpSize);
    printf("  ECC memory enabled: %s\n", p.ECCEnabled ? "yes" : "no");
    printf("  Global memory: %ld MiB\n", p.totalGlobalMem >> 20);
    printf("  L2 cache: %d KiB\n", p.l2CacheSize >> 10);
    printf("  Shared memory per SM: %ld KiB\n", p.sharedMemPerMultiprocessor >> 10);
    printf("  Shared memory per block: %ld KiB\n", p.sharedMemPerBlock >> 10);
    printf("  Shared memory per block opt-in: %ld KiB\n", p.sharedMemPerBlockOptin >> 10);
    printf("  Registers per SM: %d\n", p.regsPerMultiprocessor);
    printf("  Registers per block: %d\n", p.regsPerBlock);
    printf("  Single:Double performance ratio: %d:1\n", p.singleToDoublePrecisionPerfRatio);
}



int main(int argc, char ** argv)
{
    int device = -1;
    int device_count;

    if(argc > 1)
        device = atoi(argv[1]);

    cudaGetDeviceCount(&device_count);

    printf("There are %d cuda-capable devices detected\n\n", device_count);

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

    return 0;
}
