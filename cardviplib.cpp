#include "cardviplib.h"


CardVIPLib::CardVIPLib(QWidget *parent) : QWidget(parent)
{
    //Initialization Parameter
    m_sCardID = "";
    m_sCustomerName = "";
    m_sCustomerRef = "";
    m_sCustomerTel = "";
    m_sOrderID = "";
    m_sCardPromoType = "";
    m_dCardBalance = 0.00;
    m_dCardCreditAmount = 0.00;
    m_dTotal = 0.00;
    m_dCardPoint = 0.00;
    m_dTotalAfterDiscount = 0.00;
    m_dAmountPayCard = 0.00;
    m_dCardAmount = 0.00;

    //The first interface of the search
    m_pWidgetSearchVIPCard = new QWidget();
    m_pLabel = new QLabel();
    m_pLineEditCardID = new QLineEdit();
    m_pLineEditCardID->setFocus();
    m_pPushButtonSearchVIPCard = new QPushButton();
    m_pPushButtonSearchVIPCard->setText(QStringLiteral("查找"));
    m_pTableViewVIPCard = new QTableView();
    m_pSqlQueryModelVIPCard = new QSqlQueryModel(m_pTableViewVIPCard);
    m_pPushButtonConfirmedVIPCard = new QPushButton();
    m_pPushButtonConfirmedVIPCard->setText(QStringLiteral("确定"));
    m_pPushButtonConfirmedVIPCard->setEnabled(false);

    //The layout of the search
    QGridLayout *pGridLayoutSearchVIPCard = new QGridLayout();
    m_pLabel->setText(QStringLiteral("请输入卡号或者客户信息 : "));
    pGridLayoutSearchVIPCard->addWidget(m_pLabel,0,0);
    pGridLayoutSearchVIPCard->addWidget(m_pLineEditCardID,1,0);
    pGridLayoutSearchVIPCard->addWidget(m_pPushButtonSearchVIPCard,1,1);
    pGridLayoutSearchVIPCard->addWidget(m_pTableViewVIPCard,2,0);
    pGridLayoutSearchVIPCard->addWidget(m_pPushButtonConfirmedVIPCard,3,0);
    pGridLayoutSearchVIPCard->setHorizontalSpacing(10);
    pGridLayoutSearchVIPCard->setVerticalSpacing(10);
    m_pWidgetSearchVIPCard->setLayout(pGridLayoutSearchVIPCard);

    //The page to show the VIP Card
    //The page to show the infos of the card and the customer
    m_pWidgetShowVIPCard = new QWidget();
    m_pLabelShowVIPCard = new QLabel();
    m_pLabelShowCustomerName = new QLabel();
    m_pLabelShowCustomerRef = new QLabel();
    m_pLabelShowCustomerTel = new QLabel();
    m_pPushButtonBalance = new QPushButton();
    m_pPushButtonCreditAmount = new QPushButton();
    m_pPushButtonTotal = new QPushButton();
    m_pPushButtonPoint = new QPushButton();
    QGridLayout *pGridLayoutShowVIPCard = new QGridLayout();
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowVIPCard,0,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowCustomerName,1,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowCustomerRef,2,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowCustomerTel,3,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonTotal,4,0,1,2);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonBalance,5,0);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonCreditAmount,5,1);

    m_pLabelPromoTitle = new QLabel();
    m_pLabelPromoTitle->setText(QStringLiteral("折扣类型 : 无"));
    m_pFrame = new QFrame();
    QVBoxLayout *pVBoxLayout = new QVBoxLayout();
    pVBoxLayout->addWidget(m_pLabelPromoTitle);
    pVBoxLayout->addWidget(m_pPushButtonPoint);
    m_pFrame->setLayout(pVBoxLayout);
    m_pFrame->setFrameShape(QFrame::Box);
    m_pFrame->setObjectName("frame");
    m_pFrame->setStyleSheet("#frame {border:1px solid rgb(255,0,0)}");
    pGridLayoutShowVIPCard->addWidget(m_pFrame,6,0,2,2);

    m_pPushButtonUseBalance = new QPushButton();
    m_pPushButtonUseBalance->setText(QStringLiteral("使用会员卡积分"));
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonUseBalance,8,0);
    m_pPushButtonNotUseBalance = new QPushButton();
    m_pPushButtonNotUseBalance->setText(QStringLiteral("直接支付"));
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonNotUseBalance,8,1);
    m_pPushButtonCancel = new QPushButton();
    m_pPushButtonCancel->setText(QStringLiteral("取消"));
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonCancel,8,2);
    m_pWidgetShowVIPCard->setLayout(pGridLayoutShowVIPCard);

    m_pWidgetMain = new QWidget(this);
    m_pWidgetMain->resize(parent->size());
    QGridLayout *pGridLayoutWidgetMain = new QGridLayout();

    //The global interface
    m_pStackedWidget = new QStackedWidget(m_pWidgetMain);
    m_pStackedWidget->addWidget(m_pWidgetSearchVIPCard);
    m_pStackedWidget->addWidget(m_pWidgetShowVIPCard);

    pGridLayoutWidgetMain->addWidget(m_pStackedWidget);
    m_pWidgetMain->setLayout(pGridLayoutWidgetMain);

    //The page to verify the user
    m_pWidgetVerifyUser = new QWidget();
    m_pFormLayout = new QFormLayout();
    m_pLineEditUserCardID = new QLineEdit();
    m_pLineEditUserPassword = new QLineEdit();
    m_pPushButtonUserConfirm = new QPushButton();
    m_pPushButtonUserCancel = new QPushButton();
    m_pFormLayout->addRow(QStringLiteral("卡号 :"),m_pLineEditUserCardID);
    m_pFormLayout->addRow(QStringLiteral("密码 :"),m_pLineEditUserPassword);
    m_pFormLayout->addRow(m_pPushButtonUserConfirm,m_pPushButtonUserCancel);
    m_pFormLayout->setSpacing(10);
    m_pFormLayout->setMargin(10);

    connect(m_pPushButtonConfirmedVIPCard,SIGNAL(clicked(bool)),this,SLOT(switchPageSlot()));
    connect(m_pPushButtonSearchVIPCard,SIGNAL(clicked(bool)),this,SLOT(searchButtonClickedSlot()));
    connect(m_pPushButtonUseBalance,SIGNAL(clicked(bool)),this,SLOT(useBalanceButtonClickedSlot()));
    connect(m_pPushButtonNotUseBalance,SIGNAL(clicked(bool)),this,SLOT(notUseBalanceButtonClickedSlot()));
    connect(m_pPushButtonCancel,SIGNAL(clicked(bool)),this,SLOT(cancelButtonButtonClickedSlot()));
    connect(m_pPushButtonUserConfirm,SIGNAL(clicked(bool)),this,SLOT(verifyUserSlot()));
    connect(m_pPushButtonUserCancel,SIGNAL(clicked(bool)),m_pWidgetVerifyUser,SLOT(close()));
    connect(this,SIGNAL(verifyUserResultSignal(bool)),this,SLOT(verifyUserResultSlot(bool)));
}

QWidget* initCardVIP(QString dbDriverErp, QString dbFilePathErp, QString dbUserNameErp,
                QString dbPasswordErp, QString dbHostNameErp, int portErp,
                QString dbDriverVtp, QString dbFilePathVtp, QString dbUserNameVtp,
                QString dbPasswordVtp, QString dbHostNameVtp, int portVtp,QString orderID, QWidget *parent)
{
    CardVIPLib *lib = new CardVIPLib(parent);
    if (lib->initConnectDatabase(dbDriverErp, dbFilePathErp, dbUserNameErp, dbPasswordErp, dbHostNameErp, portErp,
                                 dbDriverVtp, dbFilePathVtp, dbUserNameVtp, dbPasswordVtp, dbHostNameVtp, portVtp,
                                 orderID)) {
        lib->show();
    } else {
        return NULL;
    }
    return lib;
}

CardVIPLib::~CardVIPLib()
{
    m_DatabaseERP.close();
    m_DatabaseVentap.close();
}

//Change the widget
void CardVIPLib::switchPageSlot()
{
    //Check the client selected
    QModelIndexList listSelected = m_pTableViewVIPCard->selectionModel()->selectedIndexes();
    if (listSelected.count() == 0) {
        QMessageBox::about(NULL,QStringLiteral("警告"),QStringLiteral("请选择一个客户!"));
    } else {
        foreach (QModelIndex index, listSelected) {
            //Get the info of the customer
            int row = index.row();
            m_sCardID = m_pSqlQueryModelVIPCard->data(m_pSqlQueryModelVIPCard->index(row,0)).toString();
            m_sCustomerName = m_pSqlQueryModelVIPCard->data(m_pSqlQueryModelVIPCard->index(row,1)).toString();
            m_sCustomerRef = m_pSqlQueryModelVIPCard->data(m_pSqlQueryModelVIPCard->index(row,2)).toString();
            m_sCustomerTel = m_pSqlQueryModelVIPCard->data(m_pSqlQueryModelVIPCard->index(row,3)).toString();
            m_dCardCreditAmount = m_pSqlQueryModelVIPCard->data(m_pSqlQueryModelVIPCard->index(row,4)).toDouble();

            m_dCardBalance = getBalanceByCardID(m_sCardID);
            getCardPromoTypeByCardID(m_sCardID);
            m_dCardPoint = getCreditAmountByOrderID(m_sOrderID);

            //Change to the second page
            int nIndex = m_pStackedWidget->currentIndex();
            nIndex++;
            m_pStackedWidget->setCurrentIndex(nIndex);
            //Set the info
            m_pLabelShowVIPCard->setText(QStringLiteral("卡号 : ") + m_sCardID);
            m_pLabelShowCustomerName->setText(QStringLiteral("客户名称 : ") + m_sCustomerName);
            m_pLabelShowCustomerRef->setText(QStringLiteral("客户号 : ") + m_sCustomerRef);
            m_pLabelShowCustomerTel->setText(QStringLiteral("客户电话 : ") + m_sCustomerTel);
            m_pPushButtonTotal->setText(QStringLiteral("此次消费金额 : ") + QString::number(m_dTotal,10,2));
            m_pPushButtonBalance->setText(QStringLiteral("卡余额 : " ) + QString::number(m_dCardBalance,10,2));
            m_pPushButtonCreditAmount->setText(QStringLiteral("额度 : ") + QString::number(m_dCardCreditAmount,10,2));
            }

        if (m_sCardPromoType == "D") {
            m_pLabelPromoTitle->setText(QStringLiteral("折扣类型 : 直接打折"));
            emit myDiscountCardVIPSignal(m_dTotal,m_dCardAmount,m_sCardID,m_sOrderID);
            m_pPushButtonPoint->setText(QStringLiteral("此次消费折扣 : ") + QString::number(m_dCardAmount,10,0) + "%");
            m_dCardPoint = 0.00;
        }
        if (m_sCardPromoType == "P") {
            m_pLabelPromoTitle->setText(QStringLiteral("折扣类型 : 折扣储值"));
            m_pPushButtonPoint->setText(QStringLiteral("此次消费积分 : ") + QString::number(m_dCardPoint,10,2));
            m_dTotalAfterDiscount = m_dTotal;
        }
    }
}

//Connect the 2 database
bool CardVIPLib::initConnectDatabase(QString dbDriverErp,QString dbFilePathErp,QString dbUserNameErp,QString dbPasswordErp,QString dbHostNameErp,int portErp,
                                     QString dbDriverVtp,QString dbFilePathVtp,QString dbUserNameVtp,QString dbPasswordVtp,QString dbHostNameVtp,int portVtp,
                                     QString orderID)
{
    bool flag = false;
    m_sOrderID = orderID;

    //Connect the database erp and ventap
    QString databaseERPFilePath = dbFilePathErp;
    QString databaseVentapFilePath = dbFilePathVtp;
    QFile dbERPFile(databaseERPFilePath);
    QFile dbVentapFile(databaseVentapFilePath);
    if (dbERPFile.exists() && dbVentapFile.exists()) {
        if (QSqlDatabase::contains("ERP")) {
            m_DatabaseERP = QSqlDatabase::database("ERP");
        } else {
            m_DatabaseERP = QSqlDatabase::addDatabase(dbDriverErp,"ERP");
        }
        m_DatabaseERP.setDatabaseName(dbERPFile.fileName());
        m_DatabaseERP.setUserName(dbUserNameErp);
        m_DatabaseERP.setPassword(dbPasswordErp);
        m_DatabaseERP.setHostName(dbHostNameErp);
        m_DatabaseERP.setPort(portErp);

        if (QSqlDatabase::contains("Ventap")) {
            m_DatabaseVentap = QSqlDatabase::database("Ventap");
        } else {
            m_DatabaseVentap = QSqlDatabase::addDatabase(dbDriverVtp,"Ventap");
        }
        m_DatabaseVentap.setDatabaseName(dbVentapFile.fileName());
        m_DatabaseVentap.setUserName(dbUserNameVtp);
        m_DatabaseVentap.setPassword(dbPasswordVtp);
        m_DatabaseVentap.setHostName(dbHostNameVtp);
        m_DatabaseVentap.setPort(portVtp);

        if (m_DatabaseERP.open() && m_DatabaseVentap.open()) {
            flag = true;
        } else {
            QMessageBox::about(NULL,"Info","Database file cannot be opened!");
        }
    } else {
        QMessageBox::about(NULL,"Info","Database file does not exist!");
    }
    return flag;
}

//refresh the page after the receive the signal discount
void CardVIPLib::myAfterDiscountSlot(double total)
{
    m_dTotalAfterDiscount = total;
    m_pPushButtonTotal->setText(QStringLiteral("此次消费金额 : ") + QString::number(m_dTotalAfterDiscount,10,2));
}

//Search the customer
void CardVIPLib::searchButtonClickedSlot()
{
    QString str = m_pLineEditCardID->text();
    if (str.count() > 2) {
        QString sql = "SELECT CARD.CARD_ID,CUSTOMER.CUSTOMER_NAME_1,CUSTOMER.CUSTOMER_REFERENCE,CUSTOMER.CUSTOMER_TEL_1,CARD.CARD_CREDIT_AMOUNT "
                      "FROM CUSTOMER "
                      "INNER JOIN CARD ON CARD.CUSTOMER_ID =CUSTOMER.CUSTOMER_ID ";
        sql = sql + "WHERE CUSTOMER.CUSTOMER_NAME_1 LIKE '%" + str + "%' "
                          "OR CUSTOMER.CUSTOMER_TEL_1 LIKE '%" + str + "%' "
                          "OR CUSTOMER.CUSTOMER_REFERENCE LIKE '%" + str + "%' "
                          "OR CARD.CARD_ID LIKE '%" + str + "%'";
        m_pSqlQueryModelVIPCard->setQuery(sql,m_DatabaseERP);
        m_pTableViewVIPCard->setModel(m_pSqlQueryModelVIPCard);
        m_pSqlQueryModelVIPCard->setHeaderData(0,Qt::Horizontal,QStringLiteral("客户号 : "));
        m_pSqlQueryModelVIPCard->setHeaderData(1,Qt::Horizontal,QStringLiteral("客户名称 : "));
        m_pSqlQueryModelVIPCard->setHeaderData(2,Qt::Horizontal,QStringLiteral("客户编号 : "));
        m_pSqlQueryModelVIPCard->setHeaderData(3,Qt::Horizontal,QStringLiteral("电话 : "));
        m_pTableViewVIPCard->setColumnHidden(4,true);
        m_pTableViewVIPCard->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_pTableViewVIPCard->setSelectionMode(QAbstractItemView::SingleSelection);
        m_pTableViewVIPCard->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_pTableViewVIPCard->verticalHeader()->hide();

        m_pPushButtonConfirmedVIPCard->setEnabled(true);
    } else {
        QMessageBox::about(NULL,QStringLiteral("警告"),QStringLiteral("请至少输入三位字符!"));
        m_pLineEditCardID->setFocus();
    }

}

//Get the balance in the database erp
double CardVIPLib::getBalanceByCardID(QString CardID)
{
    double balance = 0.00;
    QSqlQuery query(m_DatabaseERP);
    if (!m_DatabaseERP.isOpen()) {
        QMessageBox::about(NULL,"ERROR","Database file cannot be opened!");
    } else {

        //Get the balance
        QString sql = "SELECT SUM(CARD_LOG_AMOUNT) FROM CARD_LOG WHERE CARD_ID = ?";
        query.prepare(sql);
        query.bindValue(0,CardID);
        if (!query.exec()) {
            QMessageBox::about(NULL,"ERROR",query.lastError().text());
        } else {
            if (query.next()) {
                balance = query.value(0).toDouble();
            }
        }
    }
    return balance;
}

//Get the type of the promo and the card amount
void CardVIPLib::getCardPromoTypeByCardID(QString cardID)
{
    QSqlQuery query(m_DatabaseERP);
    if (!m_DatabaseERP.isOpen()) {
        QMessageBox::about(NULL,"ERROR","Database file cannot be opened!");
    } else {

        //Get the type of the promo and the card amount
        QString sql = "SELECT CARD_PROMO.CARD_PROMO_TYPE,CARD_PROMO.CARD_AMOUNT "
                      "FROM CARD_PROMO "
                      "INNER JOIN CARD ON CARD.CARD_TYPE_ID = CARD_PROMO.CARD_TYPE_ID "
                      "WHERE CARD_ID = ?";
        query.prepare(sql);
        query.bindValue(0,cardID);
        if (!query.exec()) {
            QMessageBox::about(NULL,"ERROR",query.lastError().text());
        } else {
            if (query.next()) {
                m_sCardPromoType = query.value(0).toString();
                m_dCardAmount = query.value(1).toDouble();
            }
        }
    }
}

//Get the Credit amount in the database ventap
double CardVIPLib::getCreditAmountByOrderID(QString orderID)
{
    double creditAmount = 0.00;
    QSqlQuery query(m_DatabaseVentap);
    if (!m_DatabaseVentap.isOpen()) {
        QMessageBox::about(NULL,"ERROR","Database file cannot be opened!");
    } else {

        //Get the Credit Amount
        QString sql = "SELECT T_ORDER.TOTAL FROM T_ORDER WHERE ID = ?";
        query.prepare(sql);
        query.bindValue(0,orderID);
        if (!query.exec()) {
            QMessageBox::about(NULL,"ERROR",query.lastError().text());
        } else {
            if (query.next()) {
                m_dTotal = query.value(0).toDouble();
            }
        }
    }
    creditAmount = m_dTotal * m_dCardAmount /100;
    return creditAmount;
}

//When the button useTheBalance is clicked
void CardVIPLib::useBalanceButtonClickedSlot()
{
    double limit = m_dCardBalance + m_dCardCreditAmount;;
    if (m_dTotalAfterDiscount > limit) {
        QMessageBox::about(NULL,QStringLiteral("错误"),QStringLiteral("余额不足"));
    } else {
        verifyUser();
    }
}

//When the button notUseBalance is clicked
void CardVIPLib::notUseBalanceButtonClickedSlot()
{
    m_dAmountPayCard = 0.00;
    if (updateDatabaseERP("+",m_dCardPoint)) {
        emit myNotPaymentByCardVIPSignal(2,m_sCardID,m_sOrderID,m_dTotal,m_dTotalAfterDiscount,m_sCardPromoType,m_dCardAmount,m_dAmountPayCard);
        m_pPushButtonNotUseBalance->setEnabled(false);
        m_pPushButtonUseBalance->setEnabled(false);
    } else {
        QMessageBox::about(NULL,QStringLiteral("错误"),QStringLiteral("数据库更新失败!"));
    }
}

//When the button calcel is clicked
void CardVIPLib::cancelButtonButtonClickedSlot()
{
    this->close();
}

//Update the database
bool CardVIPLib::updateDatabaseERP(QString orderType,double cardLogAmount)
{
    bool flag = false;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.toString("yyyy-MM-dd");
    QString strTime = dateTime.toString("hh:mm:ss.dddd");
    QSqlQuery query(m_DatabaseERP);
    if (!m_DatabaseERP.isOpen()) {
        QMessageBox::about(NULL,"ERROR","Database file cannot be opened!");
    } else {

        QString sql = "INSERT INTO CARD_LOG "
                      "(CARD_LOG_ID, CARD_ID, CARD_LOG_DATE, ORDER_TYPE, ORDER_ID, "
                      "CARD_LOG_AMOUNT, CARD_LOG_NOTE, OPERATOR_ID, CARD_LOG_TIME, "
                      "CARD_LOG_POINT, CARD_LOG_MEMO) "
                      "VALUES(NULL, ?, ?, ?, ?, ?, NULL, NULL, ?, NULL, NULL)";
        query.prepare(sql);
        query.bindValue(0,m_sCardID);
        query.bindValue(1,strDate);
        query.bindValue(2,orderType);
        query.bindValue(3,m_sOrderID);
        query.bindValue(4,cardLogAmount);
        query.bindValue(5,strTime);

        if (!query.exec()) {
            QMessageBox::about(NULL,"ERROR",query.lastError().text());
        } else {
            flag = true;
        }
    }
    return flag;

}

void CardVIPLib::verifyUser()
{
    m_pLineEditUserCardID->setText(m_sCardID);
    m_pLineEditUserCardID->setEnabled(false);
    m_pLineEditUserPassword->setEchoMode(QLineEdit::Password);
    m_pLineEditUserPassword->setFocus();
    m_pPushButtonUserConfirm->setText(QStringLiteral("确定"));
    m_pPushButtonUserCancel->setText(QStringLiteral("取消"));
    m_pWidgetVerifyUser->setLayout(m_pFormLayout);
    m_pWidgetVerifyUser->show();
}

void CardVIPLib::verifyUserSlot()
{
    QString cardID = m_pLineEditUserCardID->text();
    QString password = m_pLineEditUserPassword->text();
    QSqlQuery query(m_DatabaseERP);
    QString sql = "";
    if (!m_DatabaseVentap.isOpen()) {
        QMessageBox::about(NULL,"ERROR","Database file cannot be opened!");
    } else {

        sql = "SELECT CARD_ID FROM CARD WHERE CARD_ID = ? AND (CARD_PASSWORD IS NULL OR CARD_PASSWORD = ?)";
        query.prepare(sql);
        query.bindValue(0,cardID);
        query.bindValue(1,password);
        if (!query.exec()) {
            QMessageBox::about(NULL,"ERROR",query.lastError().text());
        } else {
            if (query.next()) {
                emit verifyUserResultSignal(true);
            } else {
                emit verifyUserResultSignal(false);
            }
        }
    }

}

void CardVIPLib::verifyUserResultSlot(bool flag)
{
    if (flag) {
        m_dAmountPayCard = m_dTotalAfterDiscount;
        if (updateDatabaseERP("R",-m_dAmountPayCard) && updateDatabaseERP("+",m_dCardPoint)) {
            emit myPaymentByCardVIPSignal(1,m_sCardID,m_sOrderID,m_dTotal,m_dTotalAfterDiscount,m_sCardPromoType,m_dCardAmount,m_dAmountPayCard);
            m_pPushButtonNotUseBalance->setEnabled(false);
            m_pPushButtonUseBalance->setEnabled(false);
            m_pWidgetVerifyUser->close();
         } else {
            QMessageBox::about(NULL,QStringLiteral("错误"),QStringLiteral("余额付款失败!"));
         }
    } else {
        QMessageBox::about(NULL,QStringLiteral("错误"),QStringLiteral("密码错误!"));
        m_pLineEditUserPassword->clear();
        m_pLineEditUserPassword->setFocus();
    }
}







