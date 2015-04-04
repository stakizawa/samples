/*
  バイト列を保存しているファイルのエンディアンを判定

  カレントディレクトリに"ENDIAN_TEST"ファイルが存在する場合、そのファイルの
  エンディアンを判定。存在しない場合、実行システムのエンディアンにて
  "ENDIAN_TEST"ファイルを生成。
 */

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#define MAGIC   0x0001020304050607
#define FILENAME "./ENDIAN_TEST"

enum endian {
    BIG,
    LITTLE,
    UNKNOWN
};

struct data {
    char magic[8];
    int  val;
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
	printf("data.val: %d\n", data.val);
    } else {
	// assume that file doesn't exist
	// write file
	struct data data;
	init_data(&data);
	data.val = 10;
	save_data(&data);
	printf("Endian file " FILENAME " is saved.\n");
    }

    return 0;
}
