#ifndef CARDVIPLIB_GLOBAL_H
#define CARDVIPLIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QWidget>

#if defined(CARDVIPLIB_LIBRARY)
#  define CARDVIPLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CARDVIPLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

CARDVIPLIBSHARED_EXPORT QWidget* initCardVIP(QString dbDriverErp,QString dbFilePathErp,QString dbUserNameErp,QString dbPasswordErp,QString dbHostNameErp,int portErp,
                                        QString dbDriverVtp,QString dbFilePathVtp,QString dbUserNameVtp,QString dbPasswordVtp,QString dbHostNameVtp,int portVtp,
                                         QString orderID,QWidget *parent);


#endif // CARDVIPLIB_GLOBAL_H
