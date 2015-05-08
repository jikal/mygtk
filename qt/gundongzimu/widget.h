#include<QtGui>
#include<QWidget>
class widget:public QWidget
{
    Q_OBJECT Q_PROPERTY(QString text READ text WRITE setText)
public:
    explicit widget(QWidget*parent=0);//explicit主要用于 "修饰 "构造函数. 指明构造函数只能显示使用,目的是为了防止不必要的隐式转化.
   void setText(const QString &newText);
   QString text() const//获取文本内容
   {
        return myText;
   }
   QSize sizeHint() const;//设置widget大小
protected:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);
private:
    QString myText;
    int offset;//时间间隔
    int myTimerId;//定时器ID
};
