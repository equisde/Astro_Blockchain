#include "marketbrowser.h"
#include "ui_marketbrowser.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <QDesktopServices>

#include <sstream>
#include <string>

using namespace json_spirit;

const QString kBaseUrl = "http://astro.io/ASTROusd.php";
const QString kBaseUrl1 = "http://blockchain.info/tobtc?currency=USD&value=1";
const QString kBaseUrl2 = "http://astro.io/ASTROmc.php";
const QString kBaseUrl3 = "http://astro.io/ASTRObtc.php";

QString bitcoinp = "";
QString astrop = "";
QString ASTROmcp = "";
QString ASTRObtcp = "";
double bitcoin2;
double astro2;
double ASTROmc2;
double ASTRObtc2;
QString bitcoing;
QString ASTROmarket;
QString dollarg;
int mode=1;
int o = 0;


MarketBrowser::MarketBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketBrowser)
{
    ui->setupUi(this);
    setFixedSize(400, 420);


requests();
QObject::connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
connect(ui->startButton, SIGNAL(pressed()), this, SLOT( requests()));
connect(ui->egal, SIGNAL(pressed()), this, SLOT( update()));

}

void MarketBrowser::update()
{
    QString temps = ui->egals->text();
    double totald = dollarg.toDouble() * temps.toDouble();
    double totaldq = bitcoing.toDouble() * temps.toDouble();
    ui->egald->setText("$ "+QString::number(totald)+" USD or "+QString::number(totaldq)+" BTC");

}

void MarketBrowser::requests()
{
	getRequest(kBaseUrl);
    getRequest(kBaseUrl1);
	getRequest(kBaseUrl2);
	getRequest(kBaseUrl3);
}

void MarketBrowser::getRequest( const QString &urlString )
{
    QUrl url ( urlString );
    QNetworkRequest req ( url );
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    m_nam.get(req);
}

void MarketBrowser::parseNetworkResponse(QNetworkReply *finished )
{

    QUrl what = finished->url();

    if ( finished->error() != QNetworkReply::NoError )
    {
        // A communication error has occurred
        emit networkError( finished->error() );
        return;
    }
	
if (what == kBaseUrl) // Astro Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString astro = finished->readAll();
    astro2 = (astro.toDouble());
    astro = QString::number(astro2, 'f', 2);
	
    if(astro > astrop)
    {
        ui->astro->setText("<font color=\"yellow\">$" + astro + "</font>");
    } else if (astro < astrop) {
        ui->astro->setText("<font color=\"red\">$" + astro + "</font>");
        } else {
    ui->astro->setText("$"+astro+" USD");
    }

    astrop = astro;
	dollarg = astro;
}

if (what == kBaseUrl1) // Bitcoin Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString bitcoin = finished->readAll();
    bitcoin2 = (1 / bitcoin.toDouble());
    bitcoin = QString::number(bitcoin2, 'f', 2);
    if(bitcoin > bitcoinp)
    {
        ui->bitcoin->setText("<font color=\"yellow\">$" + bitcoin + " USD</font>");
    } else if (bitcoin < bitcoinp) {
        ui->bitcoin->setText("<font color=\"red\">$" + bitcoin + " USD</font>");
        } else {
    ui->bitcoin->setText("$"+bitcoin+" USD");
    }

    bitcoinp = bitcoin;
}

if (what == kBaseUrl2) // Astro Market Cap
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString ASTROmc = finished->readAll();
    ASTROmc2 = (ASTROmc.toDouble());
    ASTROmc = QString::number(ASTROmc2, 'f', 2);
	
    if(ASTROmc > ASTROmcp)
    {
        ui->ASTROmc->setText("<font color=\"yellow\">$" + ASTROmc + "</font>");
    } else if (ASTROmc < ASTROmcp) {
        ui->ASTROmc->setText("<font color=\"red\">$" + ASTROmc + "</font>");
        } else {
    ui->ASTROmc->setText("$"+ASTROmc+" USD");
    }

    ASTROmcp = ASTROmc;
	ASTROmarket = ASTROmc;
}

if (what == kBaseUrl3) // Astro BTC Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString ASTRObtc = finished->readAll();
    ASTRObtc2 = (ASTRObtc.toDouble());
    ASTRObtc = QString::number(ASTRObtc2, 'f', 8);
	
    if(ASTRObtc > ASTRObtcp)
    {
        ui->ASTRObtc->setText("<font color=\"yellow\">" + ASTRObtc + " BTC</font>");
    } else if (ASTRObtc < ASTRObtcp) {
        ui->ASTRObtc->setText("<font color=\"red\">" + ASTRObtc + " BTC</font>");
        } else {
    ui->ASTRObtc->setText(ASTRObtc+" BTC");
    }

    ASTRObtcp = ASTRObtc;
	bitcoing = ASTRObtc;
}

finished->deleteLater();
}


void MarketBrowser::setModel(ClientModel *model)
{
    this->model = model;
}

MarketBrowser::~MarketBrowser()
{
    delete ui;
}
