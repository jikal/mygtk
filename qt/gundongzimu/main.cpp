#include<QtGui/QApplication>
#include<widget.h>
#include<QTextCodec>
int main(int argc,char* argv[])
{
      QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));  

      QApplication app(argc,argv);
      widget w;
       w.setWindowTitle(QObject::tr("Ticker"));//设置标题
       qDebug() << QObject::tr("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
         w.setText(QObject::tr("我爱你，亲爱哒"));//设置滚动的文字
         w.show();
       return app.exec();
}
