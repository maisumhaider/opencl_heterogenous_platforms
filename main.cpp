#include <iostream>
#include <vector>
#include <CL/cl.hpp>
#include <cassert>
#include <string>
#include <map>
#include <array>
#include <algorithm>
using std::map;
using std::array;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using cl::Platform;
using cl::Device;
std::string stringToLower(std::string str)
{
    using std::string;
    assert(str.length() > 0);
    string s;
    s.resize(str.size());
    std::transform(str.begin(), str.end(), s.begin(), ::tolower);
    assert(s.length() > 0);
    return s;
}
bool checkGPUVendor(const Device& device, const string& vendor){
    assert(device.getInfo<CL_DEVICE_TYPE>()==CL_DEVICE_TYPE_GPU);
    cl_int err;
     string device_vendor = device.getInfo<CL_DEVICE_VENDOR>(&err);
    return stringToLower(device_vendor).find(vendor)!=string::npos;
}
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
    vector<Device> temp;
    array<cl_device_partition_property,3> partition_properties = {CL_DEVICE_PARTITION_EQUALLY,1,CL_DEVICE_PARTITION_BY_COUNTS_LIST_END};
    for(auto &device:devices){
        if(device.second.getInfo<CL_DEVICE_TYPE>()==CL_DEVICE_TYPE_CPU){
            err = device.second.createSubDevices(partition_properties.data(),&temp);
            assert(err==CL_SUCCESS);
            cout<<device.first<<"has "<<device.second.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()
                <<" partitioned into "<<temp.size()<<" devices."<<endl;

        }
        else if(device.second.getInfo<CL_DEVICE_TYPE>()==CL_DEVICE_TYPE_GPU){
            if(checkGPUVendor(device.second,"nvidia")){
                err = device.second.createSubDevices(partition_properties.data(),&temp);
                if ( err==CL_SUCCESS){
                    cout<<device.first<<"has compute units "<<device.second.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()
                            <<" partitioned into "<<temp.size()<<" devices."<<endl;
                }else {
                    cout<<device.first<<" partitioned failed."<<endl;
                }
            }
            else if (checkGPUVendor(device.second,"intel")){
                cout<<device.first<<" has "<<device.second.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()<<"compute units but cannot be split"<<endl;
            }
        }
        else if (device.second.getInfo<CL_DEVICE_TYPE>()==CL_DEVICE_TYPE_ACCELERATOR){
            err = device.second.createSubDevices(partition_properties.data(),&temp);
            if ( err==CL_SUCCESS){
                cout<<device.first<<"has compute units "<<device.second.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()
                    <<" partitioned into "<<temp.size()<<" devices."<<endl;
            }else {
                cout<<device.first<<" partitioned failed."<<endl;
            }
        }
    }
    return 0;
}