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
#include <QVBoxLayout>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSizePolicy>
#include <QHeaderView>
#include <QModelIndexList>
#include <QModelIndex>
#include <QSqlError>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QDateTime>
#include <QFormLayout>
#include <QDebug>

class CARDVIPLIBSHARED_EXPORT CardVIPLib : public QWidget
{
    Q_OBJECT
public:
    explicit CardVIPLib(QWidget *parent = nullptr);
    bool initConnectDatabase(QString dbDriverErp,QString dbFilePathErp,QString dbUserNameErp,QString dbPasswordErp,QString dbHostNameErp,int portErp,
                             QString dbDriverVtp,QString dbFilePathVtp,QString dbUserNameVtp,QString dbPasswordVtp,QString dbHostNameVtp,int portVtp,
                             QString orderID);

    double getBalanceByCardID(QString CardID);
    double getCreditAmountByOrderID(QString orderID);
    void getCardPromoTypeByCardID(QString CardID);
    ~CardVIPLib();
    bool updateDatabaseERP(QString orderType,double cardLogAmount);
    void verifyUser();

signals:
    void myDiscountCardVIPSignal(double total,double cardAmount,QString cardID,QString orderID);
    void myPaymentByCardVIPSignal(int paymentType,QString cardID,QString orderID,
                                  double total,double totalAfterDiscount,QString promoType,
                                  double cardAmount,double amountPayCard);
    void myNotPaymentByCardVIPSignal(int paymentType,QString cardID,QString orderID,
                                     double total,double totalAfterDiscount,QString promoType,
                                     double cardAmount,double amountPayCard);
    void verifyUserResultSignal(bool flag);


private slots:
    void switchPageSlot();
    void searchButtonClickedSlot();
    void myAfterDiscountSlot(double total);
    void useBalanceButtonClickedSlot();
    void notUseBalanceButtonClickedSlot();
    void cancelButtonButtonClickedSlot();
    void verifyUserSlot();
    void verifyUserResultSlot(bool flag);

private:

    //The main widget
    QWidget *m_pWidgetMain;

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

    QFrame *m_pFrame;
    QLabel *m_pLabelPromoTitle;
    QPushButton *m_pPushButtonUseBalance;
    QPushButton *m_pPushButtonNotUseBalance;
    QPushButton *m_pPushButtonCancel;
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
    QString m_sOrderID;
    double m_dCardBalance;
    double m_dCardCreditAmount;
    double m_dTotal;
    double m_dCardPoint;
    double m_dTotalAfterDiscount;
    double m_dAmountPayCard;
    QString m_sCardPromoType;
    double m_dCardAmount;

    //The page to insert the password of user
    QWidget *m_pWidgetVerifyUser;
    QFormLayout *m_pFormLayout;
    QLineEdit *m_pLineEditUserCardID;
    QLineEdit *m_pLineEditUserPassword;
    QPushButton *m_pPushButtonUserConfirm;
    QPushButton *m_pPushButtonUserCancel;

};

#endif // CARDVIPLIB_H
