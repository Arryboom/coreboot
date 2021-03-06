/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/cpu.h>
#include <assert.h>
#include <baseboard/variants.h>
#include <cbfs.h>
#include <chip.h>
#include <commonlib/cbfs_serialized.h>
#include <compiler.h>
#include <device/device.h>
#include <ec/google/chromeec/ec.h>
#include <smbios.h>
#include <soc/ramstage.h>
#include <string.h>
#include <variant/sku.h>

uint32_t variant_board_sku(void)
{
	static uint32_t sku_id = SKU_UNKNOWN;
	uint32_t id;

	if (sku_id != SKU_UNKNOWN)
		return sku_id;
	if (google_chromeec_cbi_get_sku_id(&id))
		return SKU_UNKNOWN;
	sku_id = id;

	return sku_id;
}

void variant_devtree_update(void)
{
	/* Override dev tree settings per board */
	uint32_t sku_id = variant_board_sku();
	struct device *root = SA_DEV_ROOT;
	config_t *cfg = root->chip_info;
	switch (sku_id) {
	case SKU_1_VAYNE:
	case SKU_2_VAYNE:
		cfg->usb2_ports[5].enable = 0;//rear camera
		break;
	default:
		break;
	}
}

const char *smbios_mainboard_sku(void)
{
	static char sku_str[14]; /* sku{0..4294967295} */

	snprintf(sku_str, sizeof(sku_str), "sku%u", variant_board_sku());

	return sku_str;
}

#define OEM_UNKNOWN	0xff

/*
 * Read OEM ID from EC using cbi commands.
 * Return value:
 * Success = OEM ID read from EC
 * Failure = OEM_UNKNOWN (0xff)
 */
static uint8_t read_oem_id(void)
{
	static uint8_t oem_id = OEM_UNKNOWN;
	uint32_t id;

	if (oem_id != OEM_UNKNOWN)
		return oem_id;

	if (google_chromeec_cbi_get_oem_id(&id))
		return OEM_UNKNOWN;

	if (id > OEM_UNKNOWN) {
		printk(BIOS_ERR, "%s: OEM ID too big %u!\n", __func__, id);
		return OEM_UNKNOWN;
	}

	oem_id = id;
	printk(BIOS_DEBUG, "%s: OEM ID=%d\n", __func__, oem_id);

	return oem_id;
}

/* "oem.bin" in cbfs contains array of records using the following structure. */
struct oem_mapping {
	uint8_t oem_id;
	char oem_name[10];
} __packed;

/* Local buffer to read "oem.bin" */
static char oem_bin_data[200];

const char *smbios_mainboard_manufacturer(void)
{
	uint8_t oem_id = read_oem_id();
	const struct oem_mapping *oem_entry = (void *)&oem_bin_data;
	size_t oem_data_size;
	size_t curr = 0;
	static const char *manuf;

	if (manuf)
		return manuf;

	/* If OEM ID cannot be determined, return default manuf string. */
	if (oem_id == OEM_UNKNOWN)
		return CONFIG_MAINBOARD_SMBIOS_MANUFACTURER;

	oem_data_size = cbfs_boot_load_file("oem.bin", oem_bin_data,
					    sizeof(oem_bin_data),
					    CBFS_TYPE_RAW);

	while ((curr < oem_data_size) &&
	       ((oem_data_size - curr) >= sizeof(*oem_entry))) {
		if (oem_id == oem_entry->oem_id) {
			manuf = oem_entry->oem_name;
			break;
		}
		curr += sizeof(*oem_entry);
		oem_entry++;
	}

	if (manuf == NULL)
		manuf = CONFIG_MAINBOARD_SMBIOS_MANUFACTURER;

	return manuf;
}
