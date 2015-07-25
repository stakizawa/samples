/*
  Test for an endian neutral code

  detect_endianness2.cをベースにしている。

  カレントディレクトリに"ENDIAN_TEST"ファイルが存在する場合、そのファイルを
  読み込み、データを表示。存在しない場合、ネットワークバイトオーダーにて
  データを"ENDIAN_TEST"ファイルに保存。
 */

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define MAGIC   0x0001020304050607
#define FILENAME "./ENDIAN_TEST"

enum endian {
    BIG,
    LITTLE,
    UNKNOWN
};

struct data {
    char   magic[8];
    int    ival;
    long   lval;
};

void init_data(struct data *data)
{
    uint64_t *value = (uint64_t *)&(data->magic[0]);
    *value = MAGIC;
}

void save_data(struct data *data)
{
    FILE *fp = fopen(FILENAME, "w");
    assert(fp != NULL);
    size_t wsiz = fwrite(data, sizeof(struct data), 1, fp);
    assert(wsiz == 1);
    fclose(fp);
}

void load_data(struct data *data)
{
    FILE *fp = fopen(FILENAME, "r");
    assert(fp != NULL);
    size_t rsiz = fread(data, sizeof(struct data), 1, fp);
    assert(rsiz == 1);
    fclose(fp);
}

int detect_endian_of_system() {
    char magic[8];
    uint64_t *value = (uint64_t *)&magic[0];
    *value = MAGIC;
    if (magic[0] == 0x00) {
	return BIG;
    } else if(magic[7] == 0x00) {
	return LITTLE;
    } else {
	return UNKNOWN;
    }
}

int detect_endian_of_file(struct data *data)
{
    if (data->magic[0] == 0x00) {
	return BIG;
    } else if(data->magic[7] == 0x00) {
	return LITTLE;
    } else {
	return UNKNOWN;
    }
}

void print_endian(int val)
{
    switch(val) {
    case BIG:
	printf("Big endian\n");
	break;
    case LITTLE:
	printf("Little endian\n");
	break;
    default:
	printf("unknown endian\n");
    }
}

int
endian_native_int(int net_number)
{
    int result = 0;
    for (int i = 0; i < (int)sizeof(result); i++) {
	result <<= CHAR_BIT;
	result += (((unsigned char *)&net_number)[i] & UCHAR_MAX);
    }
    return result;
}

int
endian_net_int(int native_number)
{
    int result = 0;
    for (int i = (int)sizeof(result) - 1; i >= 0; i--) {
	((unsigned char *)&result)[i] = native_number & UCHAR_MAX;
	native_number >>= CHAR_BIT;
    }
    return result;
}

long
endian_native_long(long net_number)
{
    long result = 0;
    for (int i = 0; i < (int)sizeof(result); i++) {
	result <<= CHAR_BIT;
	result += (((unsigned char *)&net_number)[i] & UCHAR_MAX);
    }
    return result;
}

long
endian_net_long(long native_number)
{
    long result = 0;
    for (int i = (int)sizeof(result) - 1; i >= 0; i--) {
	((unsigned char *)&result)[i] = native_number & UCHAR_MAX;
	native_number >>= CHAR_BIT;
    }
    return result;
}

void hton_data(struct data *from, struct data *to)
{
    memcpy(to, from, sizeof(struct data));
    to->ival = endian_net_int(to->ival);
    to->lval = endian_net_long(to->lval);
}

void ntoh_data(struct data *from, struct data *to)
{
    memcpy(to, from, sizeof(struct data));
    to->ival = endian_native_int(to->ival);
    to->lval = endian_native_long(to->lval);
}


int
main(int argc, char **argv)
{
    int this_endian = detect_endian_of_system();
    printf("Endian of this system: ");
    print_endian(this_endian);

    struct stat sb;
    int ret = stat(FILENAME, &sb);
    if (ret == 0) {
	// assume that file exists
	// detect endian
	struct data data;
	load_data(&data);
	int file_endian = detect_endian_of_file(&data);
	printf("Endian of file: ");
	print_endian(file_endian);
	if (this_endian != file_endian) {
	    printf("Endian is not same.\n");
	}
	struct data data2;
	ntoh_data(&data, &data2);
	printf("data.val: %d\n", data2.ival);
	printf("data.val: %ld\n", data2.lval);
    } else {
	// assume that file doesn't exist
	// write file
	struct data data;
	init_data(&data);
	data.ival = 10;
	data.lval = 1000;
	struct data data2;
	hton_data(&data, &data2);
	save_data(&data2);
	printf("Endian file " FILENAME " is saved.\n");
    }

    return 0;
}
