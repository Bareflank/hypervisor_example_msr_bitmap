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
#include <vmcs_msr_bitmap/vmcs_intel_x64_msr_bitmap.h>
#include <exit_handler_msr_bitmap/exit_handler_msr_bitmap.h>

std::shared_ptr<vcpu>
vcpu_factory::make_vcpu(int64_t vcpuid)
{
    auto vmcs = std::make_shared<vmcs_intel_x64_msr_bitmap>();
    auto exit_handler = std::make_shared<exit_handler_msr_bitmap>();

    // Return a vCPU with our custom objects instead of the defaults which
    // are represented by the null pointers.
    return std::make_shared<vcpu_intel_x64>(vcpuid,
                                            nullptr,
                                            nullptr,
                                            vmcs,
                                            exit_handler,
                                            nullptr);
}
