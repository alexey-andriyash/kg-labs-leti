//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "qevent.h"

class GlWidget : public QGLWidget {

    Q_OBJECT

public:

    GlWidget(QWidget* parent = 0);

    GLfloat getColourR() const { return m_colourR; }
    GLfloat getColourB() const { return m_colourB; }
    GLfloat getColourG() const { return m_colourG; }
    GLfloat const*const getSizes() const { return m_sizes; }
    GLfloat getStep() const { return m_step;}
    GLfloat getPointSize() const { return m_pointSize; }
    GLfloat getLineSize() const { return m_lineSize; }
    GLenum getPolygonMode() const { return m_polygonMode;}
    GLenum getPolygonModeFace() const { return  m_polygonModeFace;}


    static const int M_2D = 2;
    static const GLfloat M_EPS;
    static const GLfloat M_DRAW_AREA_FROM;
    static const GLfloat M_DRAW_AREA_TO;
    static const GLfloat M_COLOUR_BORDER_FROM;
    static const GLfloat M_COLOUR_BORDER_TO;

public slots:

    void setPoligonMode(int);
    void setDrawPointsOnPoligon(int);
    void setDrawLinesOnPoligon(int);
    void setColourR(float);
    void setColourB(float);
    void setColourG(float);
    void setLineSize(float);
    void setPointSize(float);

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent* pe);

private:

    void drawOptionsInit();

    int m_isDrowLinesOnPoligon;
    int m_isDrowPointsOnPoligon;
    GLfloat m_colourR;
    GLfloat m_colourB;
    GLfloat m_colourG;
    GLfloat m_sizes[2];
    GLfloat m_step;
    GLfloat m_pointSize;
    GLfloat m_lineSize;
    GLenum m_polygonMode;
    GLenum m_polygonModeFace;

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
