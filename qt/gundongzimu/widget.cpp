#include"widget.h"
#include<QPainter>
#include<qcoreevent.h>
widget::widget(QWidget* parent):QWidget(parent)
{   
     qDebug() << QObject::tr("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
     offset=0;//时间间隔
     myTimerId=0;//定时器ID
}
void widget::setText(const QString &newText)//设置文本
{
     qDebug() << QObject::tr("gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg");
     myText=newText;
     update();//用于对widget进行强制型的重绘
      updateGeometry();//updateGeometry()用于告知包含该widget的layout：该widget的size hint已发生变化，layout会自动进行调整。
}
QSize widget::sizeHint() const//设置widget大小
{
    qDebug() << QObject::tr("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    return fontMetrics().size(0,text());
}

//绘制事件
void widget::paintEvent(QPaintEvent* event)
{
     qDebug() << QObject::tr("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
     QPainter painter(this);
     int textWidth=fontMetrics().width(text());
     if(textWidth<1)
       return;
      int x=-offset;
     while(x<width())
     {
           painter.drawText(x,0,textWidth,height(),Qt::AlignLeft|Qt::AlignVCenter,text());//绘制文本
           x+=textWidth;
      }
}
//定时器事件
void widget::timerEvent(QTimerEvent*event)
{
      if(event->timerId()==myTimerId)
      {
          qDebug() << QObject::tr("ccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
          ++offset;
          if(offset>=fontMetrics().width(text()))
              offset=0;
               scroll(-1,0);//向左滚动一个像素
      }
      else
       {
          QWidget::timerEvent(event);
       }
}
//显示事件
void widget::showEvent(QShowEvent*event)
{
        qDebug() << QObject::tr("dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
        myTimerId=startTimer(40);
}

//隐藏事件
void widget::hideEvent(QHideEvent*event)
{
         qDebug() << QObject::tr("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
         killTimer(myTimerId);
         myTimerId=0;
}
