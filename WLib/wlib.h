#ifndef WLIB_H
#define WLIB_H


#ifdef WLIB_STATIC_DEFINE
    #ifndef WLIB_EXPORT
        #define WLIB_EXPORT
    #endif
#else
    #ifndef WLIB_EXPORT
        #if defined _WIN32 || defined __CYGWIN__
            #ifdef WLIB_EXPORTS
                #define WLIB_EXPORT __declspec(dllexport)
            #else
                #define WLIB_EXPORT __declspec(dllimport)
            #endif
        #elif __GNUC__ >= 4
            #define WLIB_EXPORT __attribute__((visibility("default")))
        #else
            #define WLIB_EXPORT
        #endif
    #endif
#endif

/**
 *  Function to add two integers
 * @param a First parameter
 * @param b Second parameter
 * @return Addition result
 */
WLIB_EXPORT int wlib_add(int a, int b);

#endif /* WLIB_H */

