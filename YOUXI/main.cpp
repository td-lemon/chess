#include "mainwindow.h"
#include <QApplication>
//#include<QSplashScreen>
#include<windows.h>
#include<start.h>
#include<QDesktopWidget>
//#include<QSqlDatabase>
//#include<QSqlQuery>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
  //  QSplashScreen *splash = new QSplashScreen;
  //  splash->setPixmap(QPixmap("E:/QT/test/YOUXI/start.jpg"));
  // splash->show();
  //  a.processEvents();
  //  Sleep(500); //显示启动图片
  //  MainWindow w;
  //  w.show();
    Start s;
    s.show();
    s.move((QApplication::desktop()->width() - s.width())/2,
             (QApplication::desktop()->height() - s.height())/2);










   /* QSqlDatabase db=QSqlDatabase::addDatabase("QST");
   // delete splash;

         db.setHostName("liujie");
         db.setDatabaseName("Mydb");
         db.setUserName("test");
         db.setPassword("123456");
         db.open("test","123456");

         QSqlQuery db_query(db);
         create table score_table(score int primary_key,name)
         */

    return a.exec();
}
