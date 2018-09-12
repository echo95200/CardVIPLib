#ifndef CARDVIPLIB_GLOBAL_H
#define CARDVIPLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CARDVIPLIB_LIBRARY)
#  define CARDVIPLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CARDVIPLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CARDVIPLIB_GLOBAL_H