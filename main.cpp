#include <iostream>
#include <vector>
#include <CL/cl.hpp>
#include <cassert>
#include <string>
#include <map>
using std::map;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using cl::Platform;
using cl::Device;
int main()
{ 
    std::cout << "OpenCL Experiments!" << std::endl;
    vector<Platform> all_platforms;
    vector<Device> all_devices;
    Platform::get(&all_platforms);
    cout<<all_platforms.size()<<" platforms found"<<endl;
    cl_int err ;
    map<string,Device> devices;
    for(auto &platform: all_platforms){
        auto platform_name = platform.getInfo<CL_PLATFORM_NAME>(&err);
        assert(err==CL_SUCCESS);
        vector<Device> platform_devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL,&platform_devices);
        for(auto &device: platform_devices){
            string device_name = device.getInfo<CL_DEVICE_NAME>(&err);
            assert(err==CL_SUCCESS);
            devices[device_name]= device;

        }
    }
    cout<<"Total platforms "<<all_platforms.size()<<"."<<endl;
    cout<<"Total devices "<<devices.size()<<"."<<endl;
    return 0;
}