#ifndef ENDIAN_H

#if defined(__BYTE_ORDER) && ( __BYTE_ORDER == __BIG_ENDIAN ) || \
    defined(__BYTE_ORDER__) && ( __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ ) || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
#define ENDIAN_BIG
// It's a big-endian target architecture
#elif defined(__BYTE_ORDER) && ( __BYTE_ORDER == __LITTLE_ENDIAN ) || \
    defined(__BYTE_ORDER__) && ( __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ) || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
#define ENDIAN_LITTLE
// It's a little-endian target architecture
#else
#error "Unknown endianness!"
#error "I don't know what architecture this is!"
#endif

#define ENDIAN_H
#endif


