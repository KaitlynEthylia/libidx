#include "libidx.h"
#include <endian.h>
#include <stdio.h>
#include <stdlib.h>

int dataSize(int type) {
	int size;
	switch (type) {
	case 0x08:
	case 0x09:
		size = 1;
		break;
	case 0x0B:
		size = 2;
		break;
	case 0x0C:
	case 0x0D:
		size = 4;
		break;
	case 0x0E:
		size = 8;
		break;
	default:
		size = 0;
		break;
	}
	return size;
}

void* incDim(void* data, int dims, int* sizes, int datasize) {
	if (dims == 1) {
		return data;
	}
	dims -= 1;
	long datacount = 1;
	for (int i = 0; i < dims; i++) {
		datacount *= sizes[i];
	}
	void** arr = calloc(datacount, sizeof(void*));
	for (int i = 0; i < datacount; i++) {
		arr[i] = data + sizes[dims] * i * datasize;
	}
	return incDim(arr, dims, sizes, sizeof(void*));
}

void internalFree(void** data, int dims, int* sizes) {
	if (dims == 1) {
		free(data);
		return;
	}
	internalFree(*data, dims - 1, sizes);
	free(data);
}

void freeIDX(RAW_IDX* idx) { internalFree(idx->data, idx->dims, idx->sizes); }

int parseIDX(FILE* file, RAW_IDX* idx) {
	fseek(file, 0, SEEK_END);
	long filelen = ftell(file);
	rewind(file);

	int ret;
	unsigned char magic[4];

	ret = fread(magic, sizeof(char), 4, file);
	if (ret != 4) {
		return IDX_ERROR_NO_MAGIC;
	}

	if (magic[0] != 0 || magic[1] != 0) {
		return IDX_ERROR_INCORRECT_MAGIC;
	}

	int type = magic[2];

	int datasize = dataSize(type);
	if (datasize == 0) {
		return IDX_ERROR_UNKNOWN_DATATYPE;
	}

	int dims = magic[3];
	int* sizes = calloc(dims, 4);
	ret = fread(sizes, 4, dims, file);
	if (ret != dims) {
		return IDX_ERROR_NOT_ENOUGH_DIMENSIONS;
	}
	//
	for (int i = 0; i < dims; i++) {
		sizes[i] = be32toh(sizes[i]);
	}

	long datacount = 1;
	for (int i = 0; i < dims; i++) {
		datacount *= sizes[i];
	}

	if (filelen != 4 + dims * 4 + datacount * datasize) {
		return IDX_ERROR_FILE_LENGTH_UNEXPECTED;
	}

	unsigned char* data = calloc(datacount, datasize);
	ret = fread(data, datasize, datacount, file);
	if (ret != datacount) {
		return IDX_ERROR_NOT_ENOUGH_DATA;
	}

	idx->data = incDim(data, dims, sizes, datasize);
	idx->datasize = datasize;
	idx->type = type;
	idx->dims = dims;
	idx->sizes = sizes;
	return 0;
}
