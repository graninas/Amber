#ifndef SHADOWS_GLOBAL_H
#define SHADOWS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHADOWS_LIBRARY)
#  define SHADOWSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHADOWSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SHADOWS_GLOBAL_H
