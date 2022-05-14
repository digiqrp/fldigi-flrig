/* src/config.h.  Generated from config.h.in by configure.  */
/* src/config.h.in.  Generated from configure.ac by autoheader.  */

/* Build platform */
#define BUILD_BUILD_PLATFORM "x86_64-pc-linux-gnu"

/* Compiler */
#define BUILD_COMPILER "gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) "

/* Configure arguments */
#define BUILD_CONFIGURE_ARGS ""

/* Build date */
#define BUILD_DATE "Sat May 14 12:47:42 BST 2022"

/* Build host */
#define BUILD_HOST "mark-MacBookPro-linux"

/* Host platform */
#define BUILD_HOST_PLATFORM "x86_64-pc-linux-gnu"

/* Target platform */
#define BUILD_TARGET_PLATFORM "x86_64-pc-linux-gnu"

/* Build user */
#define BUILD_USER "mag"

/* FLRIG compiler flags */
#define FLRIG_BUILD_CXXFLAGS "-I$(srcdir) -I$(srcdir)/include -I$(srcdir)/xmlrpcpp -I$(srcdir)/xmlrpcpp -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I$(srcdir) -I$(srcdir)/include -pipe -Wall -fexceptions -O2 -DNDEBUG"

/* FLRIG linker flags */
#define FLRIG_BUILD_LDFLAGS "-lfltk_images -lfltk -lX11 -lX11 -ldl -lpthread"

/* FLTK API major version */
#define FLRIG_FLTK_API_MAJOR 1

/* FLTK API minor version */
#define FLRIG_FLTK_API_MINOR 3

/* version string */
#define FLRIG_VERSION "1.3.54"

/* major version number */
#define FLRIG_VERSION_MAJOR 1

/* minor version number */
#define FLRIG_VERSION_MINOR 3

/* patch/alpha version string */
#define FLRIG_VERSION_PATCH ".54"

/* FLTK version */
#define FLTK_BUILD_VERSION "1.3.4"

/* flxmlrpc version */
#define FLXMLRPC_BUILD_VERSION ""

/* Define to 1 if we have clock_gettime */
#define HAVE_CLOCK_GETTIME 1

/* Define to 0 if not using dbg::stack */
/* #undef HAVE_DBG_STACK */

/* Define to 1 if we have dlopen */
#define HAVE_DLOPEN 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `gmtime_r' function. */
#define HAVE_GMTIME_R 1

/* Define to 1 if you have the `hstrerror' function. */
#define HAVE_HSTRERROR 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if we have sem_timedwait */
#define HAVE_SEM_TIMEDWAIT 1

/* Define to 1 if we have sem_unlink */
#define HAVE_SEM_UNLINK 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the `socketpair' function. */
#define HAVE_SOCKETPAIR 1

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strcasestr' function. */
#define HAVE_STRCASESTR 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcpy' function. */
/* #undef HAVE_STRLCPY */

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unsetenv' function. */
#define HAVE_UNSETENV 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Name of package */
#define PACKAGE "flrig"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "w1hkj AT w1hkj DOT com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "FLRIG"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "FLRIG 1.3.54"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "flrig"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.3.54"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if we are using flxmlrpc */
#define USE_FLXMLRPC 0

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define to 1 if we are using x */
#define USE_X 1

/* Version number of package */
#define VERSION "1.3.54"

/* x version */
#define X_BUILD_VERSION "1.6.9"

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to 1 if we are building on cygwin or mingw */
/* #undef _WINDOWS */

/* Define to 1 if we are building on cygwin or mingw */
/* #undef __MINGW32__ */

/* Define to 1 if we are building on mingw */
/* #undef __WOE32__ */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
