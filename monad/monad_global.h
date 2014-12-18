#ifndef MONAD_GLOBAL_H
#define MONAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MONAD_LIBRARY)
#  define MONADSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MONADSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MONAD_GLOBAL_H
