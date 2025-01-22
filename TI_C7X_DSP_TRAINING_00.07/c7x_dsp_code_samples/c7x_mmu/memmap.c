/*
* module name       : memmap
*
* module descripton : Setup C7x cache and MMU
*
* Copyright (C) 2015-2021 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef HOST_EMULATION

#include <stdbool.h>

#include <ti/sysbios/family/c7x/Mmu.h>
#include <ti/sysbios/family/c7x/Cache.h>

#include "memmap.h"

uint32_t g_app_tirtos_c7x_mmu_map_error = 0;

void appMmuMap(bool is_secure)
{
    bool retVal;
    Mmu_MapAttrs    attrs;

    uint32_t ns = 1;

    if(is_secure)
        ns = 0;
    else
        ns = 1;

    Mmu_initMapAttrs(&attrs);

    /* Start by marking all sections as non-cached and non-shared memories */
    attrs.attrIndx = Mmu_AttrIndx_MAIR0;
    attrs.ns = ns;

    retVal = Mmu_map(0x00000000, 0x00000000, 0x20000000, &attrs, is_secure);
    if(retVal==false)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x20000000, 0x20000000, 0x20000000, &attrs, is_secure);
    if(retVal==false)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x40000000, 0x40000000, 0x20000000, &attrs, is_secure);
    if(retVal==false)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x60000000, 0x60000000, 0x10000000, &attrs, is_secure);
    if(retVal==false)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x70000000, 0x70000000, 0x10000000, &attrs, is_secure);
    if(retVal==false)
    {
        goto mmu_exit;
    }

    Mmu_initMapAttrs(&attrs);

    /* Use MAIR4 attribute to mark non-cached sections */
    attrs.attrIndx = Mmu_AttrIndx_MAIR4;
    attrs.ns = ns;

    retVal = Mmu_map(DDR_C7x_1_IPC_ADDR, DDR_C7x_1_IPC_ADDR, DDR_C7x_1_IPC_SIZE, &attrs, is_secure); /* ddr            */
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    /* Mark the required sections to be cached using MAIR7 attribute */

    Mmu_initMapAttrs(&attrs);
    attrs.attrIndx = Mmu_AttrIndx_MAIR7;
    attrs.ns = ns;
    retVal = Mmu_map(0x70000000, 0x70000000, 0x00800000, &attrs, is_secure);
    if(retVal == false)
    {
        goto mmu_exit;
    }

    Mmu_initMapAttrs(&attrs);
    attrs.attrIndx = Mmu_AttrIndx_MAIR7;
    attrs.ns = ns;
    retVal = Mmu_map(0x64800000, 0x64800000, 0x00200000, &attrs, is_secure);
    if(retVal == false)
    {
        goto mmu_exit;
    }

    Mmu_initMapAttrs(&attrs);
    attrs.attrIndx = Mmu_AttrIndx_MAIR7;
    attrs.ns = ns;

    retVal = Mmu_map(DDR_C7x_1_DTS_ADDR, DDR_C7x_1_DTS_ADDR, DDR_C7x_1_DTS_SIZE, &attrs, is_secure); /* ddr            */
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_SHARED_MEM_ADDR, DDR_SHARED_MEM_ADDR, DDR_SHARED_MEM_SIZE, &attrs, is_secure); /* ddr */
    if(retVal == false)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7X_1_SCRATCH_ADDR, DDR_C7X_1_SCRATCH_ADDR, DDR_C7X_1_SCRATCH_SIZE, &attrs, is_secure); /* ddr  */
    if(retVal == false)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7X_1_LOCAL_HEAP_VADDR, DDR_C7X_1_LOCAL_HEAP_PADDR, DDR_C7X_1_LOCAL_HEAP_SIZE, &attrs, is_secure); /* ddr            */
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

mmu_exit:
    if(retVal == FALSE)
    {
        g_app_tirtos_c7x_mmu_map_error++;
    }
}

void appCacheInit()
{
    ti_sysbios_family_c7x_Cache_Size  cacheSize;
    
    /* Init cache size here, since this needs to be done in secure mode */
    cacheSize.l1pSize = ti_sysbios_family_c7x_Cache_L1Size_32K;
    cacheSize.l1dSize = ti_sysbios_family_c7x_Cache_L1Size_32K;
    cacheSize.l2Size  = ti_sysbios_family_c7x_Cache_L2Size_64K;
    Cache_setSize(&cacheSize);
}

void setupCacheMMU(void)
{
    g_app_tirtos_c7x_mmu_map_error = 0;
    
    /*Setup two MMU tables for secure and non-secure access */
    appMmuMap(FALSE);
    appMmuMap(TRUE);
    
    /* Initialize cache after setting up MMU tables */
    appCacheInit();
}

/* Offset to be added to convert virutal address to physical address */
#define VIRT_PHY_ADDR_OFFSET (DDR_C7X_1_LOCAL_HEAP_PADDR - DDR_C7X_1_LOCAL_HEAP_VADDR)

uint64_t appUdmaVirtToPhyAddrConversion(const void *virtAddr,
                                      uint32_t chNum,
                                      void *appData)
{
  uint64_t phyAddr = (uint64_t)virtAddr;

  if ((uint64_t)virtAddr >= DDR_C7X_1_LOCAL_HEAP_VADDR)
  {
    phyAddr = ((uint64_t)virtAddr + VIRT_PHY_ADDR_OFFSET);
  }

  return phyAddr;
}

#endif
