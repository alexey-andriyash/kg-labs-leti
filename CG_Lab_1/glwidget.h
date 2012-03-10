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

    GLenum getBeginMode() const { return m_beginMode; }
    GLfloat getColourR() const { return m_colourR; }
    GLfloat getColourB() const { return m_colourB; }
    GLfloat getColourG() const { return m_colourG; }
    GLfloat const*const getSizes() const { return m_sizes; }
    GLfloat getStep() const { return m_step;}
    GLfloat getPointOrLineSize() const { return m_pointOrLineSize; }
    GLushort getLinepattern() const { return m_linepattern; }
    GLint getLineFactor() const { return m_lineFactor; }
    GLenum getWinding() const { return m_winding; }
    GLenum getPolygonMode() const { return m_polygonMode;}
    GLenum getPolygonModeFace() const { return  m_polygonModeFace;}

    static const int M_2D = 2;
    static const GLfloat M_EPS;
    static const GLfloat M_DRAW_AREA_FROM;
    static const GLfloat M_DRAW_AREA_TO;
    static const GLfloat M_COLOUR_BORDER_FROM;
    static const GLfloat M_COLOUR_BORDER_TO;

public slots:
    void setBeginMode(int);
    void setPoligonMode(int);
    void setDrawPointsOnPoligon(int);
    void setDrawLinesOnPoligon(int);
    void setWinding(int);
    void addVertex(float, float);
    void deleteAllPoints();
    void setColourR(float);
    void setColourB(float);
    void setColourG(float);
    void setPointOrLineSize(float);

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);

private:
    std::vector<GLfloat> m_vertexArray;
    unsigned m_vertex_counter;

    void vertexArrayInit();
    void drawOptionsInit();

    int m_isDrowLinesOnPoligon;
    int m_isDrowPointsOnPoligon;
    GLenum m_beginMode;
    GLfloat m_colourR;
    GLfloat m_colourB;
    GLfloat m_colourG;
    GLfloat m_sizes[2];
    GLfloat m_step;
    GLfloat m_pointOrLineSize;
    GLushort m_linepattern; //1-255
    GLint m_lineFactor;     //16,bn
    GLenum m_winding;
    GLenum m_polygonMode;
    GLenum m_polygonModeFace;



    void addPoint(float, float);
};



#endif // GLWIDGET_H
