#include <cstdio>
#include <string>
#include <vector>

#include <CL/sycl.hpp>



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

int main()
{
    std::vector<sycl::device> devices = sycl::device::get_devices();

    for(size_t i = 0; i < devices.size(); i++)
    {
        const sycl::device & device = devices[i];
        std::string name = device.get_info<sycl::info::device::name>();
        sycl::info::device_type type = device.get_info<sycl::info::device::device_type>();
        const char * type_str = device_type_to_str(type);
        std::string vendor = device.get_info<sycl::info::device::vendor>();
        uint32_t vendor_id = device.get_info<sycl::info::device::vendor_id>();
        uint32_t cus = device.get_info<sycl::info::device::max_compute_units>();
        uint64_t global_mem = device.get_info<sycl::info::device::global_mem_size>();
        std::string version = device.get_info<sycl::info::device::version>();
        std::string driver_version = device.get_info<sycl::info::device::driver_version>();

        printf("Device %zu: %s\n", i, name.c_str());
        printf("  Vendor: %s\n", vendor.c_str());
        printf("  Vendor ID: %u\n", vendor_id);
        printf("  Type: %s\n", type_str);
        printf("  Compute units: %u\n", cus);
        printf("  Global memory: %lu MiB\n", global_mem >> 20);
        printf("  Version: %s\n", version.c_str());
        printf("  Driver version: %s\n", driver_version.c_str());
    }

    



    return 0;
}
