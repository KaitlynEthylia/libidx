#include <stdio.h>

#pragma once

#define IDX_BYTE_UNSIGNED_MAGIC 0x08
#define IDX_BYTE_SIGNED_MAGIC 0x09
#define IDX_SHORT_MAGIC 0x0B
#define IDX_INT_MAGIC 0x0C
#define IDX_FLOAT_MAGIC 0x0D
#define IDX_DOUBLE_MAGIC 0x0E

#define IDX_ERROR_NO_MAGIC 1
#define IDX_ERROR_INCORRECT_MAGIC 2
#define IDX_ERROR_UNKNOWN_DATATYPE 3
#define IDX_ERROR_NOT_ENOUGH_DIMENSIONS 4
#define IDX_ERROR_FILE_LENGTH_UNEXPECTED 5
#define IDX_ERROR_NOT_ENOUGH_DATA 6

typedef struct {
	void* data;
	int datasize;
	int type;
	int dims;
	int* sizes;
} RAW_IDX;

int dataSize(int type);

void freeIDX(RAW_IDX* idx);

int parseIDX(FILE* file, RAW_IDX* idx);
