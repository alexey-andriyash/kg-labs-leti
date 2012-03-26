//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QtOpenGL>
#include "gl/GLU.h"
#include <QGLWidget>
#include "qevent.h"

class GlWidget : public QGLWidget {

    Q_OBJECT

public:

    GlWidget(QWidget* parent = 0);

    static const int M_2D = 2;
    static const GLfloat M_EPS;
    static const GLfloat M_DRAW_AREA_FROM;
    static const GLfloat M_DRAW_AREA_TO;
    static const GLfloat M_COLOUR_BORDER_FROM;
    static const GLfloat M_COLOUR_BORDER_TO;

public slots:


protected:

    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* );
    void wheelEvent(QWheelEvent* pe);

private:

    void drawOptionsInit();

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();
    void defaultScene();

    GLfloat m_xRot;
    GLfloat m_yRot;
    GLfloat m_zRot;
    GLfloat m_zTra;
    GLfloat m_nSca;
    QPoint m_ptrMousePosition;
};



#endif // GLWIDGET_H
