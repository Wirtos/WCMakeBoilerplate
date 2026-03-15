#include "wlib.h"

/**
 *  Implementation-specific docs
 * @param a Some specific a info
 * @param b Some specific b info
 * @return Some specific info about addition result, overflow is unchecked
 */
int wlib_add(int a, int b) {
#ifdef WLIB_OPTION
    return 42; /* for memes */
#else
    return a + b;
#endif
}