#ifndef CARDVIPLIB_H
#define CARDVIPLIB_H

#include "cardviplib_global.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSizePolicy>
#include <QHeaderView>
#include <QModelIndexList>
#include <QModelIndex>
#include <QSqlError>

#include <QDebug>

class CARDVIPLIBSHARED_EXPORT CardVIPLib : public QWidget
{
    Q_OBJECT
public:
    explicit CardVIPLib(QWidget *parent = nullptr);
    bool initConnectDatabase(QString dbDriverErp,QString dbFilePathErp,QString dbUserNameErp,QString dbPasswordErp,QString dbHostNameErp,int portErp,
                             QString dbDriverVtp,QString dbFilePathVtp,QString dbUserNameVtp,QString dbPasswordVtp,QString dbHostNameVtp,int portVtp,
                             double total);

    double getBalanceByCardID(QString CardID);
    ~CardVIPLib();

private slots:
    void switchPageSlot();
    void searchButtonClickedSlot();

private:
    //The widget of the search of the VIP card
    QWidget *m_pWidgetSearchVIPCard;
    QLineEdit *m_pLineEditCardID;
    QLabel *m_pLabel;
    QTableView *m_pTableViewVIPCard;
    QSqlQueryModel *m_pSqlQueryModelVIPCard;
    QPushButton *m_pPushButtonSearchVIPCard;
    QPushButton *m_pPushButtonConfirmedVIPCard;

    //The widget of showing the VIP card, second page
    QWidget *m_pWidgetShowVIPCard;
    QLabel *m_pLabelShowVIPCard;
    QLabel *m_pLabelShowCustomerName;
    QLabel *m_pLabelShowCustomerRef;
    QLabel *m_pLabelShowCustomerTel;
    QPushButton *m_pPushButtonBalance;
    QPushButton *m_pPushButtonCreditAmount;
    QPushButton *m_pPushButtonTotal;
    QPushButton *m_pPushButtonPoint;

    //Layout
    QStackedWidget *m_pStackedWidget;

    //Database
    QSqlDatabase m_DatabaseERP;
    QSqlDatabase m_DatabaseVentap;

    //The infos of the VIP card
    QString m_sCardID;
    QString m_sCustomerName;
    QString m_sCustomerRef;
    QString m_sCustomerTel;
    double m_dCardBalance;
    double m_dCardCreditAmount;
    double m_dTotal;

    QString m_sOrderID;

};

#endif // CARDVIPLIB_H
