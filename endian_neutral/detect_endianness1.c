/*
  実行システムのエンディアンを判定
 */

#include <stdio.h>
#include <stdint.h>

enum endian {
    BIG_ENDIAN,
    LITTLE_ENDIAN,
    UNKNOWN_ENDIAN
};

int detect_endian1() {
    uint64_t value;
    uint8_t *buf = (uint8_t *)&value;

    buf[0] = 0x00;
    buf[1] = 0x01;
    buf[2] = 0x02;
    buf[3] = 0x03;
    buf[4] = 0x04;
    buf[5] = 0x05;
    buf[6] = 0x06;
    buf[7] = 0x07;

    switch(value) {
    case UINT64_C(0x0001020304050607):
	return BIG_ENDIAN;
    case UINT64_C(0x0706050403020100):
	return LITTLE_ENDIAN;
    default:
	return UNKNOWN_ENDIAN;
    }
}


int detect_endian2() {
    char magic[8];
    magic[0] = 0x00;
    magic[1] = 0x01;
    magic[2] = 0x02;
    magic[3] = 0x03;
    magic[4] = 0x04;
    magic[5] = 0x05;
    magic[6] = 0x06;
    magic[7] = 0x07;
    uint64_t *value = (uint64_t *)&magic[0];

    switch(*value) {
    case UINT64_C(0x0001020304050607):
	return BIG_ENDIAN;
    case UINT64_C(0x0706050403020100):
	return LITTLE_ENDIAN;
    default:
	return UNKNOWN_ENDIAN;
    }
}


int
main(int argc, char **argv)
{
//    int val = detect_endian1();
    int val = detect_endian2();

    switch(val) {
    case BIG_ENDIAN:
	printf("Big endian\n");
	break;
    case LITTLE_ENDIAN:
	printf("Little endian\n");
	break;
    default:
	printf("unknown endian\n");
    }

    return 0;
}
