//
// Bareflank Hypervisor Examples
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <vcpu/vcpu_factory.h>
#include <vcpu/vcpu_intel_x64.h>
#include <vmcs_intel_x64_msr_bitmap.h>
#include <exit_handler_msr_bitmap/exit_handler_msr_bitmap.h>

std::shared_ptr<vcpu>
vcpu_factory::make_vcpu(int64_t vcpuid)
{
    // The vCPU Factory is used by the vCPU Manager to create vCPUs. This not
    // only provides a hook for unit testing (the classic factory pattern), but
    // also provides a clever place to hook in custom functionality above and
    // beyond what bareflank provides by default.

    // In this example, we are providing a custom exit handler that does not
    // have any MSR emulation included.
    auto exit_handler = std::make_shared<exit_handler_msr_bitmap>();

    // Provide a custom VMCS that initializes the MSR bitmap
    auto vmcs = std::make_shared<vmcs_intel_x64_msr_bitmap>();

    // Now that we have our custom exit handler, we can provide it to the
    // vCPU that bareflank provides. Note that you could create your own vCPU
    // if you need to, but in general, the existing vCPU should work for most
    // cases as it allows you to override each of the classes that are required.
    // In all cases here, if nullptr is provided, the code under the hood will
    // create the class for you using the defaults.
    return std::make_shared<vcpu_intel_x64>(vcpuid,
                                            nullptr,
                                            nullptr,
                                            vmcs,
                                            exit_handler,
                                            nullptr);
}
