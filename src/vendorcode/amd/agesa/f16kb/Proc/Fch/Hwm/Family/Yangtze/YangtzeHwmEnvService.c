/* $NoKeywords:$ */
/**
 * @file
 *
 * Config FCH Hwm controller
 *
 * Init Hwm Controller features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 84150 $   @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
 *
 */
/*
*****************************************************************************
*
 * Copyright (c) 2008 - 2013, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************
*/
#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE PROC_FCH_HWM_FAMILY_YANGTZE_YANGTZEHWMENVSERVICE_FILECODE


/**
 * HwmInitRegister - Init Hardware Monitor Register.
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
HwmInitRegister (
  IN  VOID     *FchDataPtr
  )
{
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xB2, AccessWidth8, 0, 0x55);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xB3, AccessWidth8, 0, 0x55);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x91, AccessWidth8, 0, 0x55);

  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x00, AccessWidth8, 0, 0x06);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x10, AccessWidth8, 0, 0x06);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x20, AccessWidth8, 0, 0x06);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x30, AccessWidth8, 0, 0x06);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x40, AccessWidth8, 0, 0x06);

  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x66, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x6B, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x70, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x75, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0x7A, AccessWidth8, 0, 0x01);

  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xE6, AccessWidth8, 0xff, 0x02);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xF8, AccessWidth8, 0, 0x05);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xF9, AccessWidth8, 0, 0x06);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xFF, AccessWidth8, 0, 0x42);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xE9, AccessWidth8, 0, 0xFF);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xEB, AccessWidth8, 0, 0x1F);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xEF, AccessWidth8, 0, 0x04);
  RwMem (ACPI_MMIO_BASE + PMIO2_BASE + 0xFB, AccessWidth8, 0, 0x00);
  RwMem (ACPI_MMIO_BASE + PMIO_BASE + 0xB6, AccessWidth8, 0x0F, 0x00);
}

