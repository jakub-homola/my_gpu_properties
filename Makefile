
.PHONY: clean cuda hip

clean:
	rm -f *.x

cuda: my_gpu_properties_cuda.x
	./$<

hip: my_gpu_properties_hip.x
	./$<



my_gpu_properties_cuda.x: my_gpu_properties.cu
	nvcc -g -O2 $< -o $@

my_gpu_properties_hip.x: my_gpu_properties.hip.cpp
	hipcc -g -O2 $< -o $@
