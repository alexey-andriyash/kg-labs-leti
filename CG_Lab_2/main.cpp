//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "mainwindow.h"
#include <QtOpenGL>
#include <iostream>

 int main(int argc, char *argv[]) {

     QApplication app(argc, argv);
     if (!QGLFormat::hasOpenGL()) {
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
     }
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    // GlWidget* m_glWidget = new GlWidget();
    // m_glWidget->show();
     return app.exec();
 }

/*
  TODO:
  АЛЬФА
  + добавить альфа компонент к цвету фигуры+
  - поддключить альфа тест

 СМЕШИВАНИЕ
    - нарисовать стекло и рамку
    - установить параметры смешивания цвета
    - подключить виджеты

*/
