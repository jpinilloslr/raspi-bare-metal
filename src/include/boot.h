#ifndef BOOT_H
#define BOOT_H

#define PAGE_SHIFT    12
#define TABLE_SHIFT   9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define PAGE_SIZE     (1 << PAGE_SHIFT)
#define SECTION_SIZE  (1 << SECTION_SHIFT)
#define STACK0        (2 * SECTION_SIZE)          // 2Mb

#endif
