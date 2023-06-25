#include "libidxdisplay.h"
#include "libidx.h"
#include <stdio.h>
#include <string.h>

void displayIDXinternal(RAW_IDX idx, int depth) {
	void* data = idx.data;
	int dims = idx.dims;
	int* sizes = idx.sizes;
	char padding[depth + 1];
	for (int i = 0; i < depth; i++) {
		padding[i] = '\t';
	}
	padding[depth] = '\00';

	if (dims != 1) {
		printf("%s[\n", padding);
		for (int i = 0; i < sizes[0]; i++) {
			RAW_IDX new_idx;
			new_idx.data = ((void**)data)[i];
			new_idx.datasize = idx.datasize;
			new_idx.type = idx.type;
			new_idx.dims = dims - 1;
			new_idx.sizes = sizes + 1;
			displayIDXinternal(new_idx, depth + 1);
		}
		printf("%s],\n", padding);
		return;
	}

	printf("%s[ ", padding);
	switch (idx.datasize) {
	case 1:
		for (int i = 0; i < sizes[0] - 1; i++) {
			printf("%02X ", ((unsigned char*)data)[i]);
		}
		printf("%02X", ((unsigned char*)data)[sizes[0]]);
		break;
	case 2:
		for (int i = 0; i < sizes[0] - 1; i++) {
			printf("%04X ", ((unsigned short*)data)[i]);
		}
		printf("%04X", ((unsigned short*)data)[sizes[0]]);
		break;

	case 4:
		for (int i = 0; i < sizes[0] - 1; i++) {
			printf("%08X ", ((unsigned int*)data)[i]);
		}
		printf("%08X", ((unsigned int*)data)[sizes[0]]);
		break;
	case 8:
		for (int i = 0; i < sizes[0] - 1; i++) {
			printf("%02lX ", ((unsigned long*)data)[i]);
		}
		printf("%02lX", ((unsigned long*)data)[sizes[0]]);
		break;
	}
	printf("],\n");
}

void displayIDX(RAW_IDX idx) { displayIDXinternal(idx, 0); }
