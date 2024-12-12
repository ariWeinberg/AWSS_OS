#ifndef STDDEF_H
#define STDDEF_H

// Null pointer constant
#ifndef NULL
#define NULL ((void*)0)
#endif

// Define size_t as an unsigned integer type
typedef unsigned long size_t;

// Define ptrdiff_t as a signed integer type for pointer differences
typedef long ptrdiff_t;

// Define offsetof macro to compute the offset of a member in a struct
#define offsetof(type, member) ((size_t)&(((type*)0)->member))

#endif // STDDEF_H
