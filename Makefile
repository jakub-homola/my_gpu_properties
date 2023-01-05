
.PHONY: clean cuda hip sycl

clean:
	rm -f *.x

cuda: my_gpu_properties_cuda.x
	./$<

hip: my_gpu_properties_hip.x
	./$<

sycl: my_sycl_device_properties.x
	./$<


my_gpu_properties_cuda.x: my_gpu_properties.cu Makefile
	nvcc -g -O2 $< -o $@

my_gpu_properties_hip.x: my_gpu_properties.hip.cpp Makefile
	hipcc -g -O2 $< -o $@

my_sycl_device_properties.x: my_sycl_device_properties.cpp Makefile
	icpx -g -O2 -fsycl $< -o $@
