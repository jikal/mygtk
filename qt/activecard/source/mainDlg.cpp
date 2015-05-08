#include "mainDlg.h"
#include <QUrl>
#include <QWebElement>
#include <QWebFrame>
#include <QWebSettings>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QRect>
#include <QKeyEvent>
#include <QGridLayout>
#include "comParse.h"

#define GETACTACRD_URL "http://terminal.vingoojuice.com/card/get_card_url"
#define  URL_ZD_ADDR ""
#define  URL_YYS_ADDR ""

extern QStringList g_sPortList;

mainDlg::mainDlg(QWidget *parent):
QWidget(parent)
{
	char buf[256];
	int tag = 1;

	ui.setupUi(this);
	setWindowIcon(QIcon("images/vingoo.png"));
	setWindowTitle(tr("Active Card"));
	connect(ui.webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
		this, SLOT(populateJavaScriptWindowObject()));

	connect(ui.webView->page()->mainFrame(), SIGNAL(loadFinished(bool)),
		this, SLOT(onFinised(bool)));

	connect(ui.webView->page()->mainFrame(), SIGNAL(back()),
		this, SLOT(onKey()));

	m_ntManager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象  
	connect(m_ntManager,SIGNAL(finished(QNetworkReply*)),  //关联信号和槽  
		this,SLOT(replyFinished(QNetworkReply*)));  


#ifdef ZBCARD
	tag = 1;
#else
	tag = 2;
#endif
	sprintf(buf,"%s?tag=%d",GETACTACRD_URL,tag);
	m_ntManager->get(QNetworkRequest(QUrl(buf))); //发送请求
	//connect(ui.videoPlayer,SIGNAL(finished()),this,SLOT(onVideoFinished()));
	//connect(ui.pushButton_act,SIGNAL(clicked()),this,SLOT(onOk()));
	

	// For WebView  
	//ui.webView->installEventFilter(this);  
	// For WebPage  
	//ui.webView->page()->installEventFilter(this);  
	// For WebFrame   
	//ui.webView->page()->mainFrame()->installEventFilter(this);  


	setWindowFlags(Qt::WindowMinimizeButtonHint);
	//showMaximized();
	setAutoFillBackground(true);

	QWebSettings *pWebSettings = ui.webView->page()->settings();       

	pWebSettings->setAttribute(QWebSettings::JavascriptEnabled,true);

	ui.webView->hide();

	

	QRect applicationRect = QApplication::desktop()->screenGeometry();

	int a = applicationRect.width();
	int b = applicationRect.height();

	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	//gridLayout->addWidget(ui.videoPlayer, 0, 0, 1, 1);
	gridLayout->addWidget(ui.webView, 0, 1, 1, 1);

	gridLayout->setHorizontalSpacing(0);
	gridLayout->setVerticalSpacing(0);
	gridLayout->setContentsMargins(0,0,0,0);

    ui.webView->show();

}

void mainDlg::replyFinished(QNetworkReply * nr)
{
	QString st =  QString(nr->readAll());
	if (st.isNull() || st.isEmpty() || !st.startsWith("http") || st.length() > 50)
	{
		QMessageBox::information(this,"",tr("Load Failed!!!"));
		return;
	}
	//QMessageBox::information(this,"",st);
	ui.webView->setUrl(QUrl(st));
}

void mainDlg::onVideoFinished()
{
}

mainDlg::~mainDlg(void)
{
}


void mainDlg::onFinised(bool f)
{
     if (f)
     {
		 char buf[256];
		 memset(buf,0,sizeof(buf));

		 strcpy(buf,"set_com('");
		 for (int i=0; i<g_sPortList.size(); i++)
		 {
			 strcat(buf,g_sPortList[i].toLocal8Bit().data());
			 if (i != g_sPortList.size()-1)
			 {
				 strcat(buf,"|");
			 }
		 }
		 strcat(buf,"')");
		 ui.webView->page()->mainFrame()->evaluateJavaScript(buf);
     }
	 else
	 {
		 QMessageBox::information(this,"",tr("Load Failed!!!"));
	 }

}

void mainDlg::populateJavaScriptWindowObject()
{
	ui.webView->page()->mainFrame()->addToJavaScriptWindowObject("mainDlg", this);
}

void mainDlg::onOk()
{
	char buf[256];
	//ui.webView->page()->mainFrame()->evaluateJavaScript("set_name('uuuu')");

	QWebFrame *frame = ui.webView->page()->mainFrame();

	QWebElement firstName = frame->findFirstElement("#submit");

	firstName.setAttribute("value", "zhouhuanhuan");

	strcpy(buf,firstName.evaluateJavaScript("this.value").toString().toAscii());
	QMessageBox::information(NULL,"",buf);
}

void mainDlg::onSBClicked()
{
	char buf[512];
	char rfid[64];

    comParse cp; //slt_com

	QWebFrame *frame = ui.webView->page()->mainFrame();
	QWebElement com = frame->findFirstElement("#slt_com");

	if (g_sPortList.size() == 0)
	{
		sprintf(buf,"show_msg('%s')",tr("Please  check com setting!!!").toLocal8Bit().data());
		ui.webView->page()->mainFrame()->evaluateJavaScript(buf);
		return;
	}

	if (com.isNull())
	{
		sprintf(buf,"show_msg('%s')",tr("Please  check com setting!!!").toLocal8Bit().data());
		ui.webView->page()->mainFrame()->evaluateJavaScript(buf);
		return;
	}
	strcpy(buf,com.evaluateJavaScript("this.value").toString().toAscii());

	bool ret = cp.getRFID(rfid,buf,5);
	if (!ret)
	{
		sprintf(buf,"show_msg('%s')",tr("Get rfid Failed!!!").toLocal8Bit().data());
		ui.webView->page()->mainFrame()->evaluateJavaScript(buf);
		return;
	}

	QWebElement idin = frame->findFirstElement("#txt_id_in");
	idin.setAttribute("value",rfid);
	idin.setFocus();

	//ui.webView->page()->mainFrame()->evaluateJavaScript("show_msg('gggggggggggggggggggg')");
}

void mainDlg::onKey()
{

}

void mainDlg::keyPressEvent(QKeyEvent  *event) 
{
	if(event->key()==Qt::Key_Backspace || event->key() == Qt::Key_Backtab) 
	{ 
		return;
	}
}

bool mainDlg::eventFilter(QObject *obj, QEvent *ev)
{
	if (ev->type() == QEvent::MouseButtonPress ||  
		ev->type() == QEvent::MouseButtonRelease ||  
		ev->type() == QEvent::MouseButtonDblClick){  
			QMouseEvent *mouseev = static_cast<QMouseEvent *>(ev);  
			if (mouseev->button() == Qt::RightButton) {  
				//QMessageBox::information(this,"","Eat right button!");  
				//printf("ggg");
				return true;  
			}  
	}  

	if (ev->type() == QEvent::KeyPress ||  
		ev->type() == QEvent::KeyRelease) {  
			QKeyEvent *keyev = static_cast<QKeyEvent *>(ev);  
			//qDebug("Eat key  %d", keyev->key());  
			if (keyev->key() == Qt::Key_Escape) {  
				//reload();  
			}  
			return true;  
	}  
	return false;  
}

