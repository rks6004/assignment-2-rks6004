#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mdadm.h"
#include "jbod.h"

int mdadm_mount(void) {
  // Complete your code here
  if (jbod_error == JBOD_ALREADY_MOUNTED 
  || jbod_operation((uint32_t)(JBOD_MOUNT << RESERVED_WIDTH), NULL) == -1) {
    //only need to fill out "op" field since all other fields ignored for mounting
    return -1;
  }
  // for (int diskId = 0; diskId < JBOD_NUM_DISKS; diskId++) {
  //   for (int blockId = 0; blockId < JBOD_NUM_BLOCKS_PER_DISK; blockId++) {
  //     uint32_t op = (diskId << ((sizeof(op)*8) - DISK_ID_WIDTH)) 
  //     + (blockId << ((sizeof(op)*8) - DISK_ID_WIDTH - BLOCK_ID_WIDTH))
  //     + (JBOD_MOUNT << ((sizeof(op)*8) - DISK_ID_WIDTH - BLOCK_ID_WIDTH - CMD_ID_WIDTH));
  //     if (jbod_operation(op, NULL) == -1) {
  //       return -1;
  //     } 
  //   }
  // }
  return 1;
}

int mdadm_unmount(void) {
  //Complete your code here
   if (jbod_error == JBOD_ALREADY_UNMOUNTED 
  || jbod_operation((uint32_t)(JBOD_UNMOUNT << RESERVED_WIDTH), NULL) == -1) {
    //only need to fill out "op" field since all other fields ignored for unmounting
    return -1;
  }
  return 1;
}

uint32_t mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {
  //Complete your code here
  if (read_len > 1024) {
    return EXCESS_BYTES;
  }
  if (read_len < 0 || *read_buf == NULL) {
    return BAD_ARGS;
  }
  if (jbod_error == JBOD_ALREADY_UNMOUNTED) {
    return ARRAY_UNMOUNTED;
  }
  uint32_t end_addr = start_addr + read_len - 1;
  int start_disk = disk_locator(start_addr);
  int end_disk = disk_locator(end_addr);
  
  int start_block = block_locator(start_addr);
  int end_block = block_locator(end_addr);

  uint8_t buffer_tracker = read_buf;
  uint32_t addr_tracker = start_addr;
  
  for (int d = start_disk; d <= end_disk; d++) {
      //only filling out necessary aspects of opcode
      uint32_t seek_code = d << (sizeof(seek_code) - DISK_ID_WIDTH) 
      + JBOD_SEEK_TO_DISK << (CMD_ID_WIDTH + RESERVED_WIDTH); 
      jbod_operation(seek_code, NULL);
      
      for (int b = block_locator(addr_tracker))
  }

  return read_len; 
}
//disk locator to use in opcode population
int disk_locator(uint32_t addr) {
  return (addr / JBOD_DISK_SIZE);
}
//block locator to use in opcode population
int block_locator(uint32_t addr) {
  int relative_addr = addr - (disk_locator(addr) * JBOD_DISK_SIZE);
  return (relative_addr / JBOD_BLOCK_SIZE);
}
