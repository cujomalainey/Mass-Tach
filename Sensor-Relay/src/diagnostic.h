#ifndef DIAGNOSTIC_h
#define DIAGNOSTIC_h

#define __ASSERT_USE_STDERR // trick arduino into using our assert handler
#include <assert.h>

void diagnostic_init(void);

void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp);

#endif // DIAGNOSTIC_h
