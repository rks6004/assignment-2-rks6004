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

int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {
  //Complete your code here
  return 0;
}

