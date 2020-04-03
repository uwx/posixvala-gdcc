/* LGPL3 - posixvala glib replacement - 2013 - pancake@nopcode.org */

#ifndef _GLIB_H_
#define _GLIB_H_

#ifdef __cplusplus
 #define G_BEGIN_DECLS	extern "C" {
 #define G_END_DECLS	}
#else
 #define G_BEGIN_DECLS
 #define G_END_DECLS
#endif /* __cplusplus */

#define emscripten_eval(x) eval(x)

G_BEGIN_DECLS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef ZD_PRINT_FUNCTION
#define ZD_PRINT_FUNCTION fprintf
#endif

#define G_LIKELY(expr) (expr)
#define G_UNLIKELY(expr) (expr)
#define G_LOG_DOMAIN "ERROR"
#define G_STRFUNC __func__
#define g_assertion_message_expr(domain,file,line,func,expr) \
do {									                     \
	if (!expr) {							                 \
		ZD_PRINT_FUNCTION(stderr, "**\n%s:%s:%d:%s: %s\n",	 \
			domain, file, line, func,			             \
			"code should not be reached");			         \
	} else {							                     \
		ZD_PRINT_FUNCTION(stderr, "**\n%s:%s:%d:%s: "		 \
				"assertion failed: (%s)\n",		             \
				domain, file, line, func, expr);	         \
	}								                         \
	abort();							                     \
} while (0);

typedef void* GTypeInterface;
typedef uintptr_t GQuark;
#define g_quark_from_static_string(x) ((GQuark)(size_t)(x))
typedef float gfloat;
typedef double gdouble;
typedef char gchar;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned short gushort;
typedef unsigned long ulong;
typedef unsigned long gulong;
typedef void* gpointer;
typedef const void* gconstpointer; // is a pointer to constant void
typedef void const* gpointerconst; // is a constant pointer to void
typedef int gboolean;
typedef char gint8;
typedef unsigned char guint8;
typedef int gint;
typedef short gint16;
typedef unsigned short guint16;
typedef unsigned int guint;
typedef int gint32;
typedef unsigned int guint32;
typedef long long gint64;
typedef unsigned long long guint64;
typedef guint32 gunichar;
typedef long glong;
typedef size_t gsize;
typedef ssize_t gssize;
#define g_new0(x,y) (x*)calloc (y, sizeof(x));
#define g_slice_new0(x) (x*)calloc (1, sizeof(x));
#define g_return_if_fail(x) if(!(x)) return;
#define g_return_val_if_fail(x,y) if (!(x)) return y;
#define g_slice_free(x,y) free(y)
//#define g_enum_register_static(x,y) (int)(size_t)(y),0
#define g_enum_register_static(x,y) 0

#define g_critical printf
#define TRUE 1
#define FALSE 0
#define G_GNUC_CONST
typedef int GType;

#define g_print printf
#define g_strdup strdup
#define g_free free
typedef struct {
	int x;
	const char *n;
	const char *m;
} GEnumValue;

#define g_once_init_enter(x) ((*(x) == 0) ? TRUE : FALSE)
#define g_once_init_leave(x,y) (*(x) = y)

static inline void g_type_init() {}
static inline void g_boxed() {}
//typedef gpointer (*GBoxedCopyFunc)(const gpointer s);
typedef gpointer (*GBoxedCopyFunc)(gpointer s);
typedef void (*GBoxedFreeFunc)(gpointer s);
typedef void (*GFunc)(gpointer data, gpointer user_data);
typedef void (*GDestroyNotify)(gpointer data);

#ifdef __GDCC__
static inline guint g_str_hash(const gpointer v); // fwd declaration for glib-string

// gdcc wants strings to be 'char const*' not 'const char*'
static inline guint g_boxed_type_register_static(gpointerconst v, const GBoxedCopyFunc dup, const GBoxedFreeFunc free) {
    return g_str_hash((const gpointer) v);
}
#else
#define g_boxed_type_register_static(x, y, z) g_str_hash(x)
#endif

#define GLIB_CHECK_VERSION(m,n,o) TRUE

#include "_glib-gdcc.h"

#include "_glib-defs.h"
#include "_glib-floats.h"

#include "glib-string.h"
#include "glib-list.h"
#include "glib-error.h"

G_END_DECLS

#endif /* _GLIB_H_ */
