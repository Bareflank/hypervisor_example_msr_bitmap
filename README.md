# Bareflank Hypervisor Example

## Description

This example demonstrates how to extend the Bareflank hypervisor to utilize the MSR bitmap feature of Intel virtualization. For more information on how Bareflank extensions work, please see the following:

[API Documentation](http://bareflank.github.io/hypervisor/html/)

## Compilation / Usage

First, you must clone the repo into your existing Bareflank repo. To see instructions on how to setup Bareflank, please see the following:

[Bareflank Hypervisor](https://github.com/Bareflank/hypervisor)

At the moment, out-of-tree compilation is not supported.

```
cd ~/hypervisor
git clone https://github.com/Bareflank/hypervisor_example_msr_bitmap
```

Once the example repo is cloned, you can now build the example. Bareflank automatically looks for the examples, or any folder that starts with "src_", and builds these folders along with Bareflank itself. 

```
make
```

Finally, you can run the example. This can be done by running bfm manually, and providing the path to your custom modules list:

```
pushd bfm/bin/native
sudo LD_LIBRARY_PATH=. ./bfm load hypervisor_example_msr_bitmap/bin/msr_bitmap.modules
sudo LD_LIBRARY_PATH=. ./bfm start
sudo LD_LIBRARY_PATH=. ./bfm status
sudo LD_LIBRARY_PATH=. ./bfm dump
popd
```

or you can use the shortcuts:

```
make load MODULES=hypervisor_example_msr_bitmap/bin/msr_bitmap.modules
make start
make status
make dump
```
