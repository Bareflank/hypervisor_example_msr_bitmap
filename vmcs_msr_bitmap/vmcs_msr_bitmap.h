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

#ifndef VMCS_MSR_BITMAP_H
#define VMCS_MSR_BITMAP_H

#include <memory_manager/memory_manager_x64.h>

#include <vmcs/vmcs_intel_x64.h>
#include <vmcs/vmcs_intel_x64_32bit_control_fields.h>
#include <vmcs/vmcs_intel_x64_64bit_control_fields.h>

using namespace intel_x64;
using namespace vmcs;

class vmcs_msr_bitmap : public vmcs_intel_x64
{
public:

    /// Default Constructor
    ///
    vmcs_msr_bitmap() = default;

    /// Destructor
    ///
    ~vmcs_msr_bitmap() override  = default;

    /// Write Fields
    ///
    /// This function is provided by the VMCS class as a means to
    /// extend the existing VMCS setup with custom logic. In this
    /// example, we add MSR Bitmap support.
    ///
    void
    write_fields(gsl::not_null<vmcs_intel_x64_state *> host_state,
                 gsl::not_null<vmcs_intel_x64_state *> guest_state) override
    {
        bfdebug << "enabling pass through msr bitmap" << bfendl;

        // Before we setup the MSR bitmap, we let the existing VMCS set itself
        // up. This way whatever changes we are making are done on top of the
        // default setup.
        vmcs_intel_x64::write_fields(host_state, guest_state);

        // Finally we setup the MSR bitmap. This is done by providing the VMCS
        // with the physical location of the MSR bitmap, as well as enabling
        // the MSR bitmap
        address_of_msr_bitmap::set(g_mm->virtptr_to_physint(m_msr_bitmap.get()));
        primary_processor_based_vm_execution_controls::use_msr_bitmap::enable();
    }

private:

    std::unique_ptr<uint8_t[]> m_msr_bitmap{std::make_unique<uint8_t[]>(x64::page_size)};
};

#endif
