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
#include <bitmap.h>

class vmcs_intel_x64_msr_bitmap : public vmcs_intel_x64
{
public:

    /// Default Constructor
    ///
    vmcs_intel_x64_msr_bitmap();

    /// Destructor
    ///
    virtual ~vmcs_intel_x64_msr_bitmap() {}

protected:
	virtual void write_64bit_control_state(const std::shared_ptr<vmcs_intel_x64_state> &state);
	virtual void primary_processor_based_vm_execution_controls();

private:
    bitmap m_msr_bitmap;
};

#endif
