#include "cardviplib.h"


CardVIPLib::CardVIPLib(QWidget *parent) : QWidget(parent)
{
    //The first interface of the search
    m_pWidgetSearchVIPCard = new QWidget();
    m_pLabel = new QLabel();
    m_pLineEditCardID = new QLineEdit();
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
    m_pLabelShowVIPCard->setText("Card ID");
    m_pPushButtonBalance = new QPushButton();
    m_pPushButtonCreditAmount = new QPushButton();
    m_pPushButtonTotal = new QPushButton();
    m_pPushButtonPoint = new QPushButton();
    m_pPushButtonBalance->setText("Balance : ");
    m_pPushButtonCreditAmount->setText("Credit Amount : ");
    m_pPushButtonTotal->setText("Total : ");
    m_pPushButtonPoint->setText("Point : ");
    QGridLayout *pGridLayoutShowVIPCard = new QGridLayout();
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowVIPCard,0,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowCustomerName,1,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowCustomerRef,2,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowCustomerTel,3,0,1,1);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonBalance,4,0);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonCreditAmount,4,1);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonPoint,5,0);
    pGridLayoutShowVIPCard->addWidget(m_pPushButtonTotal,5,1);
    pGridLayoutShowVIPCard->setHorizontalSpacing(10);
    pGridLayoutShowVIPCard->setVerticalSpacing(10);
    pGridLayoutShowVIPCard->setContentsMargins(10,10,10,10);
    m_pWidgetShowVIPCard->setLayout(pGridLayoutShowVIPCard);

    //The global interface
    m_pStackedWidget = new QStackedWidget(this);
    m_pStackedWidget->addWidget(m_pWidgetSearchVIPCard);
    m_pStackedWidget->addWidget(m_pWidgetShowVIPCard);
    m_pStackedWidget->adjustSize();

//    QDesktopWidget* desktop = QApplication::desktop();
//    int screenWidth = desktop->screenGeometry().width();
//    int screenHeight = desktop->screenGeometry().height();
//    this->resize(0.5*screenWidth,0.5*screenHeight);

    connect(m_pPushButtonConfirmedVIPCard,SIGNAL(clicked(bool)),this,SLOT(switchPageSlot()));
    connect(m_pPushButtonSearchVIPCard,SIGNAL(clicked(bool)),this,SLOT(searchButtonClickedSlot()));
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
        QMessageBox::about(NULL,"Info","You have to selected a customer!");
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

            //Change to the second page
            int nIndex = m_pStackedWidget->currentIndex();
            nIndex++;
            m_pStackedWidget->setCurrentIndex(nIndex);
            //Set the info
            m_pLabelShowVIPCard->setText(QStringLiteral("卡号 : ") + m_sCardID);
            m_pLabelShowCustomerName->setText(QStringLiteral("客户名称 : ") + m_sCustomerName);
            m_pLabelShowCustomerRef->setText(QStringLiteral("客户号 : ") + m_sCustomerRef);
            m_pLabelShowCustomerTel->setText(QStringLiteral("客户电话 : ") + m_sCustomerTel);
            m_pPushButtonBalance->setText(QStringLiteral("余额 : \n" ) + QString::number(m_dCardBalance,10,2));
            m_pPushButtonCreditAmount->setText(QStringLiteral("额度 : \n") + QString::number(m_dCardCreditAmount,10,2));
            m_pPushButtonTotal->setText(QStringLiteral("消费金额 : \n") + QString::number(m_dTotal,10,2));
            m_pPushButtonPoint->setText(QStringLiteral("积分 : \n"));
        }
    }
}

//Connect the 2 database
bool CardVIPLib::initConnectDatabase(QString dbDriverErp,QString dbFilePathErp,QString dbUserNameErp,QString dbPasswordErp,QString dbHostNameErp,int portErp,
                                     QString dbDriverVtp,QString dbFilePathVtp,QString dbUserNameVtp,QString dbPasswordVtp,QString dbHostNameVtp,int portVtp,
                                     double total)
{
    bool flag = false;
    m_dTotal = total;

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

//Search the customer
void CardVIPLib::searchButtonClickedSlot()
{
    QString str = m_pLineEditCardID->text();
    QString sql = "SELECT CARD.CARD_ID,CUSTOMER.CUSTOMER_NAME_1,CUSTOMER.CUSTOMER_REFERENCE,CUSTOMER.CUSTOMER_TEL_1,CARD.CARD_CREDIT_AMOUNT "
                  "FROM CUSTOMER "
                  "INNER JOIN CARD ON CARD.CUSTOMER_ID =CUSTOMER.CUSTOMER_ID ";
    sql = sql + "WHERE CUSTOMER.CUSTOMER_NAME_1 LIKE '%" + str + "%' "
                      "OR CUSTOMER.CUSTOMER_TEL_1 LIKE '%" + str + "%' "
                      "OR CUSTOMER.CUSTOMER_REFERENCE LIKE '%" + str + "%' "
                      "OR CARD.CARD_ID LIKE '%" + str + "%'";
    m_pSqlQueryModelVIPCard->setQuery(sql,m_DatabaseERP);
    m_pTableViewVIPCard->setModel(m_pSqlQueryModelVIPCard);
    m_pSqlQueryModelVIPCard->setHeaderData(0,Qt::Horizontal,"Card ID");
    m_pSqlQueryModelVIPCard->setHeaderData(1,Qt::Horizontal,"Name");
    m_pSqlQueryModelVIPCard->setHeaderData(2,Qt::Horizontal,"Ref");
    m_pSqlQueryModelVIPCard->setHeaderData(3,Qt::Horizontal,"Tel");
    m_pTableViewVIPCard->setColumnHidden(4,true);
    m_pTableViewVIPCard->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableViewVIPCard->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableViewVIPCard->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableViewVIPCard->verticalHeader()->hide();

    m_pPushButtonConfirmedVIPCard->setEnabled(true);
}

double CardVIPLib::getBalanceByCardID(QString CardID)
{
    double balance = 0.00;
    QSqlQuery query(m_DatabaseERP);
    if (!m_DatabaseERP.isOpen()) {
        QMessageBox::about(NULL,"ERROR","Database file cannot be opened!");
    } else {
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










