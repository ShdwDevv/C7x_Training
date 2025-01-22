#ifndef _HOST_EMULATION

#include <stdbool.h>

/* All the addresses and sizes are obtained from PSDKRA 7.3 memmap */

/* L2 for C7x_1 [ size 480.00 KB ] */
#define L2RAM_C7x_1_ADDR (0x64800000u)
#define L2RAM_C7x_1_SIZE (0x00078000u)

/* L1 for C7x_1 [ size 16.00 KB ] */
#define L1RAM_C7x_1_ADDR (0x64E00000u)
#define L1RAM_C7x_1_SIZE (0x00004000u)

/* MSMC for C7x_1 [ size  7.78 MB ] */
#define MSMC_C7x_1_ADDR (0x70020000u)
#define MSMC_C7x_1_SIZE (0x007C8000u)

/* DDR for C7x_1 for Linux IPC [ size 1024.00 KB ] */
#define DDR_C7x_1_IPC_ADDR (0xAA000000u)
#define DDR_C7x_1_IPC_SIZE (0x00100000u)

/* DDR for C7x_1 for all sections, used for reserving memory in DTS file [ size 79.00 MB ] */
#define DDR_C7x_1_DTS_ADDR (0xAA100000u)
#define DDR_C7x_1_DTS_SIZE (0x04F00000u)

/* Memory for shared memory buffers in DDR [ size 480.00 MB ] */
#define DDR_SHARED_MEM_ADDR (0xDC000000u)
#define DDR_SHARED_MEM_SIZE (0x1E000000u)

/* DDR for c7x_1 for Scratch Memory [ size 512.00 MB ] */
#define DDR_C7X_1_SCRATCH_ADDR (0xAE000000u)
#define DDR_C7X_1_SCRATCH_SIZE (0x20000000u)

/* DDR for c7x_1 for Local Heap Memory [ size 1024.00 MB ] */
#define DDR_C7X_1_LOCAL_HEAP_ADDR (0x100000000u)
#define DDR_C7X_1_LOCAL_HEAP_SIZE (0x40000000u)

/* For J7ES/J721E/TDA4VM the upper 2GB DDR starts from 0x0008_8000_0000 */
/* This address is mapped to a virtual address of 0x0001_0000_0000 */
#define DDR_C7X_1_LOCAL_HEAP_VADDR (DDR_C7X_1_LOCAL_HEAP_ADDR)
#define DDR_C7X_1_LOCAL_HEAP_PADDR (0x880000000u)

/* This function performs both cache and MMU setup */
void setupCacheMMU(void);

/* This function is requried to manually translate address for programming DRU */
uint64_t appUdmaVirtToPhyAddrConversion(const void *virtAddr,
                                      uint32_t chNum,
                                      void *appData);

#endif
