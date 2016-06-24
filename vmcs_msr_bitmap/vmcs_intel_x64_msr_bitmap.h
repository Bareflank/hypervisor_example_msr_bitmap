//
// Bareflank Hypervisor
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

#ifndef VMCS_INTEL_X64_MSR_BITMAP_H
#define VMCS_INTEL_X64_MSR_BITMAP_H

#include <vmcs/vmcs_intel_x64.h>
#include <memory_manager/memory_manager.h>

class vmcs_intel_x64_msr_bitmap : public vmcs_intel_x64
{
public:

    /// Default Constructor
    ///
    vmcs_intel_x64_msr_bitmap()
    {
        // Allocate the MSR bitmap. Note that we use the memory manager to
        // do this so that we can get aligned memory, as C++ does not have
        // aligned memory allocation
        m_msr_bitmap = std::unique_ptr<char[]>((char *)g_mm->malloc_aligned(4096, 4096));
    }

    /// Destructor
    ///
    virtual ~vmcs_intel_x64_msr_bitmap() {}

protected:

    void
    write_64bit_control_state(const std::shared_ptr<vmcs_intel_x64_state> &state) override
    {
        // Tell the VMCS were the MSR bitmap is located
        vmwrite(VMCS_ADDRESS_OF_MSR_BITMAPS_FULL, (uint64_t)g_mm->virt_to_phys(m_msr_bitmap.get()));

        bfdebug << "enabling msr bitmaps" << bfendl;

        // Call the base class to enable any other features that are needed.
        vmcs_intel_x64::write_64bit_control_state(state);
    }

    void
    primary_processor_based_vm_execution_controls() override
    {
        // Enable the MSR bitmaps
        auto controls = vmread(VMCS_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);
        controls |= VM_EXEC_P_PROC_BASED_USE_MSR_BITMAPS;
        vmwrite(VMCS_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, controls);

        // Call the base class to enable any other features that are needed.
        vmcs_intel_x64::primary_processor_based_vm_execution_controls();
    }

private:
    std::unique_ptr<char[]> m_msr_bitmap;
};

#endif
