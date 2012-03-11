//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "glwidget.h"
#include <assert.h>

//const int GlWidget::M_2D = 2;
const GLfloat GlWidget::M_EPS = 0.001f;
const GLfloat GlWidget::M_DRAW_AREA_FROM = -1.0f;
const GLfloat GlWidget::M_DRAW_AREA_TO = 1.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_FROM = -1.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_TO = 1.0f;

GlWidget::GlWidget(QWidget* parent)
    : QGLWidget(parent)
{
     setMinimumSize(300, 300);
}

void GlWidget::initializeGL() {

    vertexArrayInit();
    drawOptionsInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LINE_STIPPLE);

    glVertexPointer(2, GL_FLOAT, 0, &m_vertexArray[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(m_colourR, m_colourB, m_colourG);

    glShadeModel(GL_FLAT);

}

void GlWidget::resizeGL(int nWidth, int nHeight) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    if (nWidth>=nHeight)
       glOrtho(M_DRAW_AREA_FROM/ratio, M_DRAW_AREA_TO/ratio, M_DRAW_AREA_FROM, M_DRAW_AREA_TO, 10.0*M_DRAW_AREA_FROM, M_DRAW_AREA_TO);
    else
       glOrtho(M_DRAW_AREA_FROM, M_DRAW_AREA_TO, M_DRAW_AREA_FROM*ratio, M_DRAW_AREA_TO*ratio, 10.0*M_DRAW_AREA_FROM, M_DRAW_AREA_TO);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void GlWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFrontFace(m_winding);
    glPointSize(m_pointOrLineSize);
    glLineWidth(m_pointOrLineSize);
    glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
/*
    glColor3f(m_colourR, m_colourG, m_colourB);
    glBegin(m_beginMode);
        for(unsigned i = 0; i < m_vertex_counter*M_2D; i = i + M_2D) {
           glVertex2f(m_vertexArray[i], m_vertexArray[i+1]);
        }
    glEnd();
*/
   if(m_beginMode == GL_POINTS) {
        glColor3f(m_colourR, m_colourG, m_colourB);
        glBegin(m_beginMode);
            for(unsigned i = 0; i < m_vertex_counter*M_2D; i = i + M_2D) {
               glVertex2f(m_vertexArray[i], m_vertexArray[i+1]);
            }
        glEnd();
   } else {
        if((m_isDrowPointsOnPoligon) && (m_polygonMode != GL_POINT)) {
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POINTS);
                for(unsigned i = 0; i < m_vertex_counter*M_2D; i = i + M_2D) {
                    glVertex2f(m_vertexArray[i], m_vertexArray[i+1]);
                }
            glEnd();
        }
        if((m_isDrowLinesOnPoligon)  && (m_polygonMode == GL_FILL)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(0.0, 0.0, 1.0);
            glBegin(m_beginMode);
                for(unsigned i = 0; i < m_vertex_counter*M_2D; i = i + M_2D) {
                    glVertex2f(m_vertexArray[i], m_vertexArray[i+1]);
                }
            glEnd();
        }

        glColor3f(m_colourR, m_colourG, m_colourB);
//        glColor3f(0.0, 1.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
        glBegin(m_beginMode);
            for(unsigned i = 0; i < m_vertex_counter*M_2D; i = i + M_2D) {
               glVertex2f(m_vertexArray[i], m_vertexArray[i+1]);
            }
        glEnd();
    }

}

void GlWidget::vertexArrayInit() {

    m_vertex_counter = 0;
    addPoint(0.0f, 0.0f);
    addPoint(0.5f, 0.5f);
    addPoint(0.5f, -0.5f);
    addPoint(-0.5f, 0.5f);
    addPoint(-0.5f, -0.5f);
}

void GlWidget::drawOptionsInit() {

    m_isDrowLinesOnPoligon = true;
    m_isDrowPointsOnPoligon = true;
    m_beginMode = GL_POINTS;
    m_colourR = 0.0;
    m_colourB = 0.0;
    m_colourG = 0.0;
    glGetFloatv(GL_POINT_SIZE_RANGE, m_sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &m_step);
    m_pointOrLineSize = m_sizes[0] + 20*m_step;
    m_winding = GL_CW;
    m_polygonMode = GL_FILL;
}

void GlWidget::setBeginMode(int mode) {

    assert((mode >= GL_POINTS) && (mode <= GL_POLYGON));

    m_beginMode = mode;
    updateGL();
}

void GlWidget::addVertex(float x, float y) {

    addPoint(x, y);
    updateGL();
}

void GlWidget::addPoint(float x, float y) {

    assert((x >= (M_DRAW_AREA_FROM - M_EPS)) &&
           (x <= (M_DRAW_AREA_TO + M_EPS)) &&
           (y >= (M_DRAW_AREA_FROM - M_EPS)) &&
           (y <= (M_DRAW_AREA_TO + M_EPS)));

    unsigned xPosition = (m_vertex_counter) ? (m_vertex_counter*2 - 2) : 0;
    unsigned yPosition = (m_vertex_counter) ? (m_vertex_counter*2 - 1) : 1;

    if( (m_vertexArray.size()) < (m_vertex_counter*M_2D + M_2D) ) {
        m_vertexArray.resize(m_vertexArray.size() + M_2D);
    }
    m_vertexArray[xPosition] = (GLfloat)x;
    m_vertexArray[yPosition] = (GLfloat)y;
    m_vertex_counter++;
}

void GlWidget::deleteAllPoints() {

    m_vertexArray.clear();
    m_vertex_counter = 0;
    updateGL();
}

void GlWidget::setPoligonMode(int mode) {

    assert((mode >= 0 ) || (mode <= 3));

    m_polygonMode = ((mode ==0) ? (GL_FILL)
                  : ((mode == 1) ? (GL_LINE)
                  : (GL_POINT)));
    updateGL();
}

void GlWidget::setDrawPointsOnPoligon(int isTrue) {

    m_isDrowPointsOnPoligon = isTrue;
    updateGL();
}

void GlWidget::setDrawLinesOnPoligon(int isTrue) {

    m_isDrowLinesOnPoligon = isTrue;
    updateGL();
}

void GlWidget::setWinding(int winding) {

    assert((winding ==  0) || (winding == 1));

    m_winding = winding ? GL_CCW : GL_CW;
    updateGL();
}

void GlWidget::setColourR(float colour) {

    assert(((colour >= M_COLOUR_BORDER_FROM - M_EPS)) &&
           ((colour <= M_COLOUR_BORDER_TO + M_EPS)));

    m_colourR = colour;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateGL();
}

void GlWidget::setColourB(float colour) {

    assert((colour >= (M_COLOUR_BORDER_FROM - M_EPS)) &&
           (colour <= (M_COLOUR_BORDER_TO + M_EPS)));

    m_colourB = colour;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateGL();
}

void GlWidget::setColourG(float colour) {

    assert((colour >= (M_COLOUR_BORDER_FROM - M_EPS)) &&
           (colour <= (M_COLOUR_BORDER_TO + M_EPS)));

    m_colourG = colour;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateGL();
}

void GlWidget::setPointOrLineSize(float size) {
/*
    assert((size >= (m_sizes[0] - m_step)) &&
           (size <= (m_sizes[1] + m_step)));
*/
    m_pointOrLineSize = size;
    updateGL();
}

void GlWidget::mousePressEvent(QMouseEvent* event)
{
    float xNorm = ((GLfloat)event->x())/width(); //0  1
    float yNorm = ((GLfloat)event->y())/height();

    GLfloat xGL = 2*xNorm - 1.0;
    GLfloat yGL = -(2*yNorm - 1.0);

    addVertex(xGL, yGL);
}

