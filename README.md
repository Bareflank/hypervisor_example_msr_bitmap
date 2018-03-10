# Bareflank Hypervisor MST Bitmap Example

## Description

This example demonstrates how to extend the Bareflank hypervisor to use
Intel's MSR Bitmap to increase performance. For more information on how
Bareflank extensions work, please see the following:

[API Documentation](http://bareflank.github.io/hypervisor/html/)

## Compilation / Usage

To setup our extension, run the following (assuming Linux):

```
git clone -b dev https://github.com/Bareflank/hypervisor
git clone -b dev https://github.com/Bareflank/hypervisor_example_msr_bitmap.git
mkdir build; cd build
cmake ../hypervisor -DDEFAULT_VMM=example_vmm -DEXTENSION=../hypervisor_example_msr_bitmap
make -j<# cores + 1>
```

To test out our extended version of Bareflank, run the following commands:

```
make driver_quick
make quick
```

to get status information, use the following:

```
make status
make dump
```

to reverse this:

```
make unload
make driver_unload
```
