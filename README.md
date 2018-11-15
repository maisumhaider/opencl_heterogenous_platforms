# opencl_heterogenous_platforms

This is an evaluation of algorithm implementations across different platform types.
The platforms are abstracted using OpenCL API (khronos link)
The platform types in comparison are cpu(intel), gpu(Nvidia,Intel) and fpga-SoC(XC7Z020-CLG484-1).

## OpenCL Observations
1. On intel platform with intel cpu and intel gpu. Platform.getDevices() is used to get a vector of devices. In my scenario the vector contained intel cpu and intel gpu. Making a context with this vector of devices and making a command queue from vector without specifying the device leads to a suprising result. This command queue used the first device in the devices of context. This can be observed by saxpy with alpha = 1 and reversing the order of the vector between executions.
2. createSubDevices for nvidia gpu returns CL_INVALID_VALUE.
3. createSubDevices for intel gpu (hd graphics) results in a segmentation fault.
## Tested Algorithms
1.
2.
3.
...
### Parameters explored.
1.
2.
3.
...
### Metrics for comparison
1. Throughput optimisation
2. Latency optimisation
3. Memory optimisation
