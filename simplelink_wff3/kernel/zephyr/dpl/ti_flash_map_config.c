#include <stdint.h>

/*
 * PG2 RTM, 4MB flash, NO OTA layout.
 * Derived from board config: boards/ti/lp_em_cc35x1/config/flash_disc_param_ext_mem.json
 *
 * Region 1 (boot): 0x00000000 - 0x00104FFF
 *   WiFi FW slot 1: GPE at 0x00068FFC
 *   WiFi FW slot 2: GPE at 0x000DAFFC
 *   NVS:            0x000DA000, size 0x2B000
 * Region 0 (code): 0x00105000 - 0x003FFFFF
 *   Vendor image:   GPE at 0x00105FFC
 */

/* WiFi Connectivity Slot 1 memory configuration
 * JSON: nvs_region_primary_wsoc_start_phy_address = 0x68FFC (GPE header)
 * Slot base = 0x68FFC - 0xFFC = 0x68000
 * Slot size = slot2_base - slot1_base = 0xDA000 - 0x68000 = 0x72000
 */
uint32_t wifi_connectivity_physical_slot_1_address = 0x00068000;
uint32_t wifi_connectivity_logical_slot_1_address = 0xA0068000;
uint32_t wifi_connectivity_slot_1_region_size = 0x00072000;

/* WiFi Connectivity Slot 2 memory configuration
 * JSON: nvs_region_sec_wsoc_start_phy_address = 0xDAFFC (GPE header)
 * Slot base = 0xDAFFC - 0xFFC = 0xDA000
 * Slot size = NVS_end - slot2_base = 0x105000 - 0xDA000 = 0x2B000
 */
uint32_t wifi_connectivity_physical_slot_2_address = 0x000DA000;
uint32_t wifi_connectivity_logical_slot_2_address = 0xA00DA000;
uint32_t wifi_connectivity_slot_2_region_size = 0x0002B000;

/* Vendor Image Slot 1 memory configuration
 * JSON: main_code_region_vendor_image_start_phy_address = 0x105FFC
 * Slot base = 0x105FFC - 0xFFC = 0x105000
 * Region 0 end = 0x3FFFFF, size = 0x400000 - 0x105000 = 0x2FB000
 */
uint32_t vendor_image_physical_slot_1_address = 0x00105000;
uint32_t vendor_image_logical_slot_1_address = 0x14000000;
uint32_t vendor_image_slot_1_region_size = 0x002FB000;

/* Vendor Image Slot 2 (not used in NO OTA) */
uint32_t vendor_image_physical_slot_2_address = 0;
uint32_t vendor_image_logical_slot_2_address = 0;
uint32_t vendor_image_slot_2_region_size = 0;

/* BL2 Slot 1 memory configuration
 * JSON: boot_region_primary_ti_bl_start_phy_address = 0x2FFC
 * Slot base = 0x2FFC - 0xFFC = 0x2000
 */
uint32_t bl2_physical_slot_1_address = 0x00002000;
uint32_t bl2_logical_slot_1_address = 0xA0002000;
uint32_t bl2_slot_1_region_size = 0x00066000;

/* BL2 Slot 2
 * JSON: boot_region_sec_ti_bl_start_phy_address = 0x68FFC
 * Overlaps with WiFi slot 1 — not used in NO OTA
 */
uint32_t bl2_physical_slot_2_address = 0;
uint32_t bl2_logical_slot_2_address = 0;
uint32_t bl2_slot_2_region_size = 0;

/* NVOCMP memory configuration
 * JSON: nvs_start_phy_address = 0xDA000, nvs_region_size = 0x2B000
 */
uint32_t nvocmp_physical_slot_address = 0x000DA000;
uint32_t nvocmp_logical_slot_address = 0xA00DA000;
uint32_t nvocmp_region_size = 0x0002B000;

/* Key Storage (not separately defined in 4M NO OTA layout) */
uint32_t key_storage_physical_slot_address = 0;
uint32_t key_storage_logical_slot_address = 0;
uint32_t key_storage_region_size = 0;
