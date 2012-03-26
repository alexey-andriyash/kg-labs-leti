//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "glwidget.h"
#include "gl/GLU.h"
#include <assert.h>
#include "math.h"

//const int GlWidget::M_2D = 2;
const GLfloat GlWidget::M_EPS = 0.001f;
const GLfloat GlWidget::M_DRAW_AREA_FROM = -300.0f;
const GLfloat GlWidget::M_DRAW_AREA_TO = 300.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_FROM = -1.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_TO = 1.0f;

GlWidget::GlWidget(QWidget* parent)
    : QGLWidget(parent)
{
     setMinimumSize(300, 300);
     defaultScene();
}

void GlWidget::initializeGL() {

    drawOptionsInit();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glColor3f(0.5f, 1.0f, 0.5f);


}

void GlWidget::resizeGL(int nWidth, int nHeight) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = ((GLfloat)nHeight)/((GLfloat)nWidth);

    if (nWidth>=nHeight) {
       glOrtho( M_DRAW_AREA_FROM / ratio,
                M_DRAW_AREA_TO / ratio,
                M_DRAW_AREA_FROM,
                M_DRAW_AREA_TO,
                10.0 * M_DRAW_AREA_FROM,
                M_DRAW_AREA_TO
               );
    } else {
       glOrtho( M_DRAW_AREA_FROM,
                M_DRAW_AREA_TO,
                M_DRAW_AREA_FROM * ratio,
                M_DRAW_AREA_TO * ratio,
                10.0 * M_DRAW_AREA_FROM,
                M_DRAW_AREA_TO
               );
    }
    glViewport(0, 0, ((GLint)nWidth), ((GLint)nHeight));

//    GLfloat fAspect;
//    fAspect = (GLfloat)nWidth/(GLfloat)nHeight;
//    gluPerspective(45.0f, fAspect, 1.0f, 425.0f);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
}

void GlWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GlWidget::mousePressEvent(QMouseEvent* pe) {

    m_ptrMousePosition = pe->pos();
}

void GlWidget::mouseReleaseEvent(QMouseEvent* /*pe*/) { }

void GlWidget::mouseMoveEvent(QMouseEvent* pe) {

   m_xRot += 180/m_nSca*(GLfloat)(pe->y() - m_ptrMousePosition.y())/height();
   m_zRot += 180/m_nSca*(GLfloat)(pe->x() - m_ptrMousePosition.x())/width();
   m_ptrMousePosition = pe->pos();

   updateGL();
}

void GlWidget::wheelEvent(QWheelEvent* pe) {

   if ( pe->delta() > 0) {
       scale_plus();
   } else if ( pe->delta() < 0 ) {
       scale_minus();
    }
   updateGL();
}

void GlWidget::scale_plus() {

   m_nSca = m_nSca*1.1;
}

void GlWidget::scale_minus() {

   m_nSca = m_nSca/1.1;
}

void GlWidget::rotate_up() {

   m_xRot += 1.0f;
}

void GlWidget::rotate_down() {

   m_xRot -= 1.0f;
}

void GlWidget::rotate_left() {

   m_zRot += 1.0f;
}

void GlWidget::rotate_right() {

   m_zRot -= 1.0f;
}

void GlWidget::translate_down() {

   m_zTra -= 0.05f;
}

void GlWidget::translate_up() {

   m_zTra += 0.05f;
}

void GlWidget::defaultScene() {

   m_xRot = -90.0f;
   m_yRot = 0.0f;
   m_zRot = 0.0f;
   m_zTra = 0.0f;
   m_nSca = 1.0f;
}

void GlWidget::drawOptionsInit() {

}
