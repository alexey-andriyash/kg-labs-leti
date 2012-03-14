//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "glwidget.h"
#include <assert.h>
#include "math.h"

//const int GlWidget::M_2D = 2;
const GLfloat GlWidget::M_EPS = 0.001f;
const GLfloat GlWidget::M_DRAW_AREA_FROM = -100.0f;
const GLfloat GlWidget::M_DRAW_AREA_TO = 100.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_FROM = -1.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_TO = 1.0f;

GlWidget::GlWidget(QWidget* parent)
    : QGLWidget(parent)
{
     setMinimumSize(300, 300);
     m_xRot=-90;
     m_yRot=0;
     m_zRot=0;
     m_zTra=0;
     m_nSca=1;
}

void GlWidget::initializeGL() {

    drawOptionsInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LINE_STIPPLE);

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
//    glEnable(GL_SCISSOR_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(m_nSca, m_nSca, m_nSca);
    glTranslatef(0.0f, m_zTra, 0.0f);
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);


    glPointSize(m_pointSize);
    glLineWidth(m_lineSize);

    if(m_isDrowPointsOnPoligon) {
        glColor3f(1.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
        const float R = 60;
        const float PI = 3.14;
        const unsigned ANGLES_COUNTER = 8;
        float alfa = 0.0;
        glBegin(GL_POINTS);
            glVertex3d(0.0, 0.0, 50);
            alfa = 0.0;
            while(alfa < 2*PI) {
                float x = R*cos(alfa);
                float y = R*sin(alfa);
                float z = 0.0;
                glVertex3d(x, y, z);
                alfa += PI/ANGLES_COUNTER;
            }
        glEnd();
    }

    glColor3f(m_colourR, m_colourG, m_colourB);
    glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
    glBegin(GL_LINE_LOOP);
         const float R = 60;
         const float PI = 3.14;
         const unsigned ANGLES_COUNTER = 8;
         float alfa = 0.0;
        while(alfa < 2*PI) {
            float x = R*cos(alfa);
            float y = R*sin(alfa);
            float z = 0.0;
            glVertex3d(x, y, z);
            alfa += PI/ANGLES_COUNTER;
        }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(0.0, 0.0, 50);
        alfa = 0.0;
        while(alfa < 2*PI) {
            float x = R*cos(alfa);
            float y = R*sin(alfa);
            float z = 0.0;
            glVertex3d(x, y, z);
            alfa += PI/ANGLES_COUNTER;
        }
    glEnd();
}

void GlWidget::mousePressEvent(QMouseEvent* pe)
{
   m_ptrMousePosition = pe->pos();
}

void GlWidget::mouseReleaseEvent(QMouseEvent* pe)
{

}

void GlWidget::mouseMoveEvent(QMouseEvent* pe)
{
   m_xRot += 180/m_nSca*(GLfloat)(pe->y() - m_ptrMousePosition.y())/height();
   m_zRot += 180/m_nSca*(GLfloat)(pe->x() - m_ptrMousePosition.x())/width();

   m_ptrMousePosition = pe->pos();

   updateGL();
}

void GlWidget::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL();
}

void GlWidget::scale_plus()
{
   m_nSca = m_nSca*1.1;
}

void GlWidget::scale_minus()
{
   m_nSca = m_nSca/1.1;
}

void GlWidget::rotate_up()
{
   m_xRot += 1.0;
}

void GlWidget::rotate_down()
{
   m_xRot -= 1.0;
}

void GlWidget::rotate_left()
{
   m_zRot += 1.0;
}

void GlWidget::rotate_right()
{
   m_zRot -= 1.0;
}

void GlWidget::translate_down()
{
   m_zTra -= 0.05;
}

void GlWidget::translate_up()
{
   m_zTra += 0.05;
}

void GlWidget::defaultScene()
{
   m_xRot = -90;
   m_yRot = 0;
   m_zRot = 0;
   m_zTra = 0;
   m_nSca = 1;
}

void GlWidget::drawOptionsInit() {

    m_isDrowLinesOnPoligon = true;
    m_isDrowPointsOnPoligon = true;
    m_colourR = 0.0;
    m_colourB = 0.0;
    m_colourG = 1.0;
    glGetFloatv(GL_POINT_SIZE_RANGE, m_sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &m_step);
    m_pointSize = m_sizes[0] + 20*m_step;
    m_lineSize = m_sizes[0] + 20*m_step;
    m_polygonMode = GL_FILL;
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

void GlWidget::setLineSize(float size) {
/*
    assert((size >= (m_sizes[0] - m_step)) &&
           (size <= (m_sizes[1] + m_step)));
*/
    m_lineSize = size;
    updateGL();
}

void GlWidget::setPointSize(float size) {
/*
    assert((size >= (m_sizes[0] - m_step)) &&
           (size <= (m_sizes[1] + m_step)));
*/
    m_pointSize = size;
    updateGL();
}
