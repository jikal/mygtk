#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QFileInfo>
#include <QMessageBox>
#include "mainDlg.h"

#if	defined(_WIN32)||defined(_WIN64)
#include <Windows.h>
#else
#endif

QStringList g_sPortList;
int EnumAllComPort(QStringList &port) 
{ 
	int nCommSum = 0;//´®¿Ú¸öÊý 
#if	defined(_WIN32)||defined(_WIN64)	
	HANDLE hCom; 
	char str[32]; 
	port.clear();
	WCHAR wszClassName[64];   
	memset(wszClassName,0,sizeof(wszClassName));  

	for(int i=1;i<=100;i++) 
	{ 
		memset(wszClassName,0,sizeof(wszClassName));  
		sprintf(str,"COM%d",i); 
		MultiByteToWideChar(CP_ACP,0,str,strlen(str)+1,wszClassName,  
			sizeof(wszClassName)/sizeof(wszClassName[0]));  
		hCom = CreateFile(wszClassName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); 

		if (hCom == INVALID_HANDLE_VALUE) 
		{ 
			continue; 
		} 
		else 
		{ 
			port.push_back(str);
		} 

		CloseHandle(hCom); 
		nCommSum++; 
	} 
#else
	port.push_back("/dev/ttyS0");
	nCommSum++; 
	port.push_back("/dev/ttyS1");
	nCommSum++; 
	port.push_back("/dev/ttyS2");
	nCommSum++; 
	port.push_back("/dev/ttyS3");
	nCommSum++; 
	port.push_back("/dev/ttyS4");
	nCommSum++; 
	port.push_back("/dev/ttyS5");
	nCommSum++; 
#endif
	return nCommSum; 
}

int main( int argc , char* argv[] )
{
	
	QApplication app( argc , argv );

	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

	QString  sTranPath = "activecard_zh_cn.qm";
	QTranslator translator( 0 );
	QFileInfo fi( sTranPath );

	//getcwd(buf,256);
	if ( fi.exists() ) 
	{
		translator.load( sTranPath, "." );
		app.installTranslator( &translator );
	}	
	else
	{
	}

	if (0 == EnumAllComPort(g_sPortList))
	{
		QMessageBox::warning(NULL,"",QObject::tr("No Useable COM Port!"));
		//return 0;
	}

	//curl_global_init(CURL_GLOBAL_DEFAULT);

	//loginDlg w;
	mainDlg w;
	w.show();
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit())); 
	return app.exec();
}