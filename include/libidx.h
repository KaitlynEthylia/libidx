/** @Header
 * idx file format parsing
 *
 * @description
 * This library defines a series of functions for parsing the IDX file format
 * for stroing multidimensional arrays. As the datatype and dimenisionality are
 * encoded in the file, it is possible, with some dark magic, to define
 * functions that work on arrays of any dimenisionality.
 *
 * @usage
 * The IDX file format is the format used by the *MNIST* dataset. The
 * format stores multidimensional arrays/matrices of varying types for usage
 * in training and testing neural networks.
 *
 * @future
 * In future this library may be expanded to contain more library
 * functions for manipulating N-dimensional arrays, including common operations
 * that one may want to perform on the arrays, particularly in the context of
 * training / testing neural networks.
 */

#include <stdio.h>

#pragma once

/** @defgroup
 * IDX Magic Types
 *
 * @description
 * The type of data stored in the IDX, identified by the magic number at the
 * start of the file
 */
#define IDX_MAGIC_BYTE_UNSIGNED 0x08
#define IDX_MAGIC_BYTE_SIGNED 0x09
#define IDX_MAGIC_SHORT 0x0B
#define IDX_MAGIC_INT 0x0C
#define IDX_MAGIC_FLOAT 0x0D
#define IDX_MAGIC_DOUBLE 0x0E

/** @Defgroup
 * IDX Error Values
 *
 * @description
 * Possible error values that may be thrown by __parseIDX__()
 */
#define IDX_ERROR_NO_MAGIC 1
#define IDX_ERROR_INCORRECT_MAGIC 2
#define IDX_ERROR_UNKNOWN_DATATYPE 3
#define IDX_ERROR_NOT_ENOUGH_DIMENSIONS 4
#define IDX_ERROR_FILE_LENGTH_UNEXPECTED 5
#define IDX_ERROR_NOT_ENOUGH_DATA 6

/** @Struct
 * Struct containing the data from an IDX file.
 *
 * @field data
 * The data cointained within the idx file. Must be cast to the correct type
 * before using. *see __parseIDX__(3)*
 *
 * @field datasize :: The size, in bytes, of a single datapoint in the structure
 *
 * @field type
 * The datatype of the data in the struct. *see __IDX Magic Types__*
 *
 * @field dims
 * The number of dimensions in the struct, this tells you how
 * many stars must go after the type when casting the __data__ field
 *
 * @field sizes
 * An array of length __dims__ containing the length of the data structure in
 * each dimenision
 */
typedef struct {
	void* data;
	int datasize;
	int type;
	int dims;
	int* sizes;
} RAW_IDX;

/** @Fun sourced
 * Calculates the size, in bytes, of each datapoint in the IDX based on the
 * magic type.
 *
 * @return size :: The size in bytes
 *
 * @param type
 * The magic number used to identify data types in the idx format.
 * *see __IDX Magic Types__*
 */
int dataSize(int type);

/** @Docfun
 * TODO
 *
 * @return error :: The error code returned by the function. 0 indicates
 * success.
 *
 * @param file :: The file containing the IDX data to parse
 *
 * @param idx :: A pointer to the memory that will be filled by the parsed IDX
 *
 * @returnvalue
 * TODO
 *
 * @description
 * TODO
 *
 * @errors
 * TODO
 *
 * @example
 * The following example opens the file at a path and attempts to parse it.
 * ```
 * #include <libidx.h>
 * #include <stdio.h>
 * ...
 * FILE* fdidx = fopen("path/to/idx", "rb");
 * RAW_IDX* idx;
 * int ret = parseIDX(rdidx, idx);
 * ...
 * ```
 * If the file is parsed successfully, __ret__ will be 0, otherwise it will be
 * some error value. *see __IDX Error Values__*.
 */
int parseIDX(FILE* file, RAW_IDX* idx);

/** @Docfun
 * Frees the memory stored in a RAW_IDX sruct.
 *
 * @param idx :: A pointer to the RAW_IDX struct that will be freed.
 *
 * @description
 * TODO
 *
 * @example
 * The following example expands on the example in __parseIDX__(). Once the
 * parsed IDX is no longer necessary, it becomes freed.
 * ```
 * #include <libidx.h>
 * #include <stdio.h>
 * ...
 * FILE* fdidx = fopen("path/to/idx", "rb");
 * RAW_IDX* idx;
 * int ret = parseIDX(rdidx, idx);
 * ...
 * freeIDX(idx);
 * ```
 */
void freeIDX(RAW_IDX* idx);
