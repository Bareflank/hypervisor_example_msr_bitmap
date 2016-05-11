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

#include <debug.h>
#include <constants.h>
#include <vmcs_intel_x64_msr_bitmap.h>
#include <memory_manager/memory_manager.h>

vmcs_intel_x64_msr_bitmap::vmcs_intel_x64_msr_bitmap() :
    m_msr_bitmap()
{
    if (!m_intrinsics)
        m_intrinsics = std::make_shared<intrinsics_intel_x64>();
}

void
vmcs_intel_x64_msr_bitmap::write_64bit_control_state(const std::shared_ptr<vmcs_intel_x64_state> &state)
{
    (void) state;

    // unused: VMCS_ADDRESS_OF_IO_BITMAP_A_FULL
    // unused: VMCS_ADDRESS_OF_IO_BITMAP_B_FULL
    vmwrite(VMCS_ADDRESS_OF_MSR_BITMAPS_FULL, (uint64_t)m_msr_bitmap.phys_addr());
    // unused: VMCS_VM_EXIT_MSR_STORE_ADDRESS_FULL
    // unused: VMCS_VM_EXIT_MSR_LOAD_ADDRESS_FULL
    // unused: VMCS_VM_ENTRY_MSR_LOAD_ADDRESS_FULL
    // unused: VMCS_EXECUTIVE_VMCS_POINTER_FULL
    // unused: VMCS_TSC_OFFSET_FULL
    // unused: VMCS_VIRTUAL_APIC_ADDRESS_FULL
    // unused: VMCS_APIC_ACCESS_ADDRESS_FULL
    // unused: VMCS_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS_FULL
    // unused: VMCS_VM_FUNCTION_CONTROLS_FULL
    // unused: VMCS_EPT_POINTER_FULL
    // unused: VMCS_EOI_EXIT_BITMAP_0_FULL
    // unused: VMCS_EOI_EXIT_BITMAP_1_FULL
    // unused: VMCS_EOI_EXIT_BITMAP_2_FULL
    // unused: VMCS_EOI_EXIT_BITMAP_3_FULL
    // unused: VMCS_EPTP_LIST_ADDRESS_FULL
    // unused: VMCS_VMREAD_BITMAP_ADDRESS_FULL
    // unused: VMCS_VMWRITE_BITMAP_ADDRESS_FULL
    // unused: VMCS_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS_FULL
    // unused: VMCS_XSS_EXITING_BITMAP_FULL
}

void
vmcs_intel_x64_msr_bitmap::primary_processor_based_vm_execution_controls()
{
    auto controls = vmread(VMCS_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);

    // controls |= VM_EXEC_P_PROC_BASED_INTERRUPT_WINDOW_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_USE_TSC_OFFSETTING;
    // controls |= VM_EXEC_P_PROC_BASED_HLT_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_INVLPG_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_MWAIT_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_RDPMC_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_RDTSC_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_CR3_LOAD_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_CR3_STORE_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_CR8_LOAD_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_CR8_STORE_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_USE_TPR_SHADOW;
    // controls |= VM_EXEC_P_PROC_BASED_NMI_WINDOW_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_MOV_DR_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_UNCONDITIONAL_IO_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_USE_IO_BITMAPS;
    // controls |= VM_EXEC_P_PROC_BASED_MONITOR_TRAP_FLAG;
    controls |= VM_EXEC_P_PROC_BASED_USE_MSR_BITMAPS;
    // controls |= VM_EXEC_P_PROC_BASED_MONITOR_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_PAUSE_EXITING;
    // controls |= VM_EXEC_P_PROC_BASED_ACTIVATE_SECONDARY_CONTROLS;

    vmwrite(VMCS_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, controls);
}
