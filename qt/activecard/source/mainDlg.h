#pragma once
#include "ui_maindlg.h"
#include <QtNetwork>

class mainDlg : public QWidget
{
	Q_OBJECT
public:
	mainDlg(QWidget *parent = NULL);
	~mainDlg(void);

private:
	Ui::maindlg ui;
	void keyPressEvent(QKeyEvent  *event);

	QNetworkAccessManager *m_ntManager;

public slots:
	void populateJavaScriptWindowObject();
	void onOk();

	void onFinised(bool f);
	void onVideoFinished();

	void onSBClicked();

	void onKey();

	void replyFinished(QNetworkReply * nr);

protected:
	bool eventFilter(QObject *obj, QEvent *ev);  
};
