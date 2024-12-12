#include "stdint.h"
#include "stddef.h" // For NULL

// Define the LBA type based on required width
typedef uint32_t LBA_22; // 22-bit LBA
typedef uint32_t LBA_28; // 28-bit LBA
typedef uint64_t LBA_48; // 48-bit LBA

int HPC; // Heads per Cylinder
int SPT; // Sectors per Track

// Define the CHS structure as packed to prevent padding
typedef struct __attribute__((packed)) chs
{
    int C; // Cylinder
    int H; // Head
    int S; // Sector
} CHS;

// 22-bit functions

int is_valid_lba_22(LBA_22 lba)
{
    return lba < (1U << 22); // Max value for 22-bit is 2^22 - 1
}

LBA_22 chs_to_lba_22(CHS address)
{
    LBA_22 lba = (LBA_22)((address.C * HPC + address.H) * SPT + (address.S - 1));
    return is_valid_lba_22(lba) ? lba : 0;
}

CHS* lba_22_to_chs(LBA_22 lba)
{
    if (!is_valid_lba_22(lba))
        return NULL;

    static CHS result;
    result.C = lba / (HPC * SPT);
    result.H = (lba / SPT) % HPC;
    result.S = (lba % SPT) + 1;

    return &result;
}

// 28-bit functions

int is_valid_lba_28(LBA_28 lba)
{
    return lba < (1U << 28); // Max value for 28-bit is 2^28 - 1
}

LBA_28 chs_to_lba_28(CHS address)
{
    LBA_28 lba = (LBA_28)((address.C * HPC + address.H) * SPT + (address.S - 1));
    return is_valid_lba_28(lba) ? lba : 0;
}

CHS* lba_28_to_chs(LBA_28 lba)
{
    if (!is_valid_lba_28(lba))
        return NULL;

    static CHS result;
    result.C = lba / (HPC * SPT);
    result.H = (lba / SPT) % HPC;
    result.S = (lba % SPT) + 1;

    return &result;
}

// 48-bit functions

int is_valid_lba_48(LBA_48 lba)
{
    return lba < (1ULL << 48); // Max value for 48-bit is 2^48 - 1
}

LBA_48 chs_to_lba_48(CHS address)
{
    LBA_48 lba = (LBA_48)((address.C * HPC + address.H) * SPT + (address.S - 1));
    return is_valid_lba_48(lba) ? lba : 0;
}

CHS* lba_48_to_chs(LBA_48 lba)
{
    if (!is_valid_lba_48(lba))
        return NULL;

    static CHS result;
    result.C = lba / (HPC * SPT);
    result.H = (lba / SPT) % HPC;
    result.S = (lba % SPT) + 1;

    return &result;
}
