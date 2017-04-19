# Bareflank Hypervisor MST Bitmap Example

## Description

This example demonstrates how to extend the Bareflank hypervisor to use
Intel's MSR Bitmap to increase performance. For more information on how
Bareflank extensions work, please see the following:

[API Documentation](http://bareflank.github.io/hypervisor/html/)

## Compilation / Usage

To setup our extension, run the following (assuming Linux):

```
cd ~/
git clone https://github.com/Bareflank/hypervisor.git
git clone https://github.com/Bareflank/hypervisor_example_msr_bitmap.git
cd ~/hypervisor

./tools/scripts/setup-<xxx>.sh --no-configure
sudo reboot

cd ~/
mkdir build
cd ~/build

~/hypervisor/configure -m ~/hypervisor_example_msr_bitmap/bin/msr_bitmap.modules -e ~/hypervisor_example_msr_bitmap
make
```

To test out our extended version of Bareflank, all we need to do is run the
make shortcuts as usual:

```
make driver_load
make quick

make status
make dump

make stop
make driver_unload
```
