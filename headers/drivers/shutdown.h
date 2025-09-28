//full credits to MalwareLab150 for this ACPI driver
//Link to his code: https://github.com/MalwareLab150/49.exe/blob/main/kernel/include/shutdown_ACPI/shutdown.h
//I adapted it to my OS, but he made it all

#include "../utils.h"
#include "../memory.h"

#define SCI_EN 0x0001
#define SLP_EN (1 << 13)
typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;

typedef struct {
    byte Signature[4];
    uint32_t Length;
    byte unneeded1[40 - 8];
    uint32_t DSDT;
    byte unneeded2[48 - 44];
    uint32_t SMI_CMD;
    byte ACPI_ENABLE;
    byte ACPI_DISABLE;
    byte unneeded3[64 - 54];
    uint32_t PM1a_CNT_BLK;
    uint32_t PM1b_CNT_BLK;
    byte unneeded4[89 - 72];
    byte PM1_CNT_LEN;
} __attribute__((packed)) FADT;

void acpi_shutdown() { //turns off using ACPI driver


    for (uint32_t addr = 0x000E0000; addr < 0x00100000; addr += 16) {
        if (memcmp((char *)addr, "RSD PTR ", 8) == 0) {
            uint32_t *rsdt_addr = *(uint32_t *)(addr + 16); 
            char *rsdt = (char *)rsdt_addr;

            int entries = *((uint32_t *)(rsdt + 4)) - 36;
            entries /= 4;
            uint32_t *table_ptrs = (uint32_t *)(rsdt + 36);
            for (int i = 0; i < entries; i++) {
                char *sig = (char *)table_ptrs[i];
                if (memcmp(sig, "FACP", 4) == 0) {
                    FADT *fadt = (FADT *)sig;

                    if (!(inw(fadt->PM1a_CNT_BLK) & SCI_EN)) {
                        if (fadt->SMI_CMD != 0 && fadt->ACPI_ENABLE != 0) {
                            outb(fadt->SMI_CMD, fadt->ACPI_ENABLE);
                            for (int i = 0; i < 300; i++) {
                                if (inw(fadt->PM1a_CNT_BLK) & SCI_EN)
                                    break;
                            }
                        }
                    }

                    char *dsdt = (char *)fadt->DSDT;
                    int len = *((uint32_t *)(dsdt + 4));
                    for (int i = 0; i < len - 4; i++) {
                        if (memcmp(dsdt + i, "_S5_", 4) == 0) {

                            uint8_t *pkg = (uint8_t *)(dsdt + i + 5);
                            pkg += ((*pkg & 0xC0) >> 6) + 2;

                            uint8_t typa = 0, typb = 0;

                            if (*pkg == 0x0A) pkg++;
                            typa = *pkg++; // SLP_TYPa

                            if (*pkg == 0x0A) pkg++;
                            typb = *pkg++; // SLP_TYPb

                            uint16_t slp_typa = typa << 10;
                            uint16_t slp_typb = typb << 10;

                            outw(fadt->PM1a_CNT_BLK, slp_typa | SLP_EN);
                            if (fadt->PM1b_CNT_BLK)
                                outw(fadt->PM1b_CNT_BLK, slp_typb | SLP_EN);

                            return;
                        }
                    }
                }
            }
        }
    }

}
void shutdown() {
    acpi_shutdown();

    while (1) {
        acpi_shutdown();
        acpi_shutdown();
    }
}
