#ifndef MDADM_H_
#define MDADM_H_

#include <stdint.h>
#include "jbod.h"

enum mdadm_rear_error_codes {
    OUT_OF_BOUNDS = -1, 
    EXCESS_BYTES = -2,
    ARRAY_UNMOUNTED = -3,
    BAD_ARGS = -4
};

/* Return 1 on success and -1 on failure */
int mdadm_mount(void);

/* Return 1 on success and -1 on failure */
int mdadm_unmount(void);

/* Return the number of bytes read on success, -1 on failure. */
int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf);

#endif
