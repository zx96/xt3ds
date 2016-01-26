#include "minlib.h"

inline void swap_u16(u16 *n1, u16 *n2) {
	*n1 ^= *n2;
	*n2 ^= *n1;
	*n1 ^= *n2;
}

inline u16 absVal(s16 n) {
	if (n < 0) return -n;
	return n;
}
