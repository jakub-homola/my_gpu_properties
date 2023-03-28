#include <cstdio>
#include <string>
#include <vector>

#include <sycl/sycl.hpp>



const char * device_type_to_str(sycl::info::device_type type)
{
    switch(type)
    {
        case sycl::info::device_type::cpu:         return "CPU";
        case sycl::info::device_type::gpu:         return "GPU";
        case sycl::info::device_type::accelerator: return "accelerator";
        case sycl::info::device_type::host:        return "host";
        case sycl::info::device_type::custom:      return "custom";
        case sycl::info::device_type::automatic:   return "automatic";
        case sycl::info::device_type::all:         return "all";
        default: return "not recognized device type, cannot convert to string";
    }
}

void print_device_properties(const sycl::device & device)
{
    printf("  Platform name: %s\n",        device.get_info<sycl::info::device::platform>().get_info<sycl::info::platform::name>().c_str());
    printf("  Platform vendor: %s\n",      device.get_info<sycl::info::device::platform>().get_info<sycl::info::platform::vendor>().c_str());
    printf("  Platform version: %s\n",     device.get_info<sycl::info::device::platform>().get_info<sycl::info::platform::version>().c_str());
    printf("  Device name: %s\n",          device.get_info<sycl::info::device::name>().c_str());
    printf("  Device vendor: %s, ID %u\n", device.get_info<sycl::info::device::vendor>().c_str(), device.get_info<sycl::info::device::vendor_id>());
    printf("  Device version: %s\n",       device.get_info<sycl::info::device::version>().c_str());
    printf("  Driver version: %s\n",       device.get_info<sycl::info::device::driver_version>().c_str());
    printf("  Type: %s\n",                 device_type_to_str(device.get_info<sycl::info::device::device_type>()));
    printf("  Compute units: %u\n",        device.get_info<sycl::info::device::max_compute_units>());
    printf("  Global memory: %lu MiB\n",   device.get_info<sycl::info::device::global_mem_size>() >> 20);
    printf("  Memory alignment: %u\n",     device.get_info<sycl::info::device::mem_base_addr_align>());
}

int main()
{
    std::vector<sycl::device> devices = sycl::device::get_devices();

    for(size_t i = 0; i < devices.size(); i++)
    {
        const sycl::device & device = devices[i];
        printf("Device %zu:\n", i);
        print_device_properties(device);
    }

    return 0;
}
