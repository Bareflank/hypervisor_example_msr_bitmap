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

#include <bfvmm/memory_manager/memory_manager.h>
#include <bfvmm/vcpu/vcpu_factory.h>
#include <bfvmm/vcpu/arch/intel_x64/vcpu.h>

using namespace ::intel_x64::vmcs;

namespace example
{
namespace intel_x64
{

class vcpu : public bfvmm::intel_x64::vcpu
{
private:
    std::unique_ptr<uint8_t[]> m_msr_bitmap{std::make_unique<uint8_t[]>(x64::page_size)};
	
public:

    vcpu(vcpuid::type id) :
        bfvmm::intel_x64::vcpu{id}
    {
        address_of_msr_bitmap::set(g_mm->virtptr_to_physint(m_msr_bitmap.get()));
        primary_processor_based_vm_execution_controls::use_msr_bitmap::enable();
    }

    ~vcpu() override = default;  
};

}
}

namespace bfvmm
{

WEAK_SYM std::unique_ptr<vcpu>
vcpu_factory::make_vcpu(vcpuid::type vcpuid, bfobject *obj)
{
    bfignored(obj);
    return std::make_unique<example::intel_x64::vcpu>(vcpuid);
}

}
