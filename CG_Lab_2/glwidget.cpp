//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "glwidget.h"
#include <assert.h>
#include "math.h"

//const int GlWidget::M_2D = 2;
const GLfloat GlWidget::M_EPS = 0.001f;
const GLfloat GlWidget::M_DRAW_AREA_FROM = -300.0f;
const GLfloat GlWidget::M_DRAW_AREA_TO = 300.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_FROM = -1.0f;
const GLfloat GlWidget::M_COLOUR_BORDER_TO = 1.0f;

const GLfloat GlWidget::Cone::R = 60.0f;
const GLfloat GlWidget::Cone::H = 60.0f;
const GLfloat GlWidget::Cone::PI = 3.14f;
const unsigned GlWidget::Cone::DIVIDER = 16;

GlWidget::GlWidget(QWidget* parent)
    :  m_Cone(), QGLWidget(parent)
{
     setMinimumSize(300, 300);
     defaultScene();
}


GlWidget::Cone::Cone() {

    vertex[0] = 0.0f;
    vertex[1] = 0.0f;
    vertex[2] = H;
    baseCenter[0] = 0.0f;
    baseCenter[1] = 0.0f;
    baseCenter[2] = 0.0f;

    alfa = 0.0f;
    for(unsigned i = 0; i < DIVIDER; i++) {
        float x = R*cos(alfa);
        float y = R*sin(alfa);
        float z = 0.0f;
        glVertex3d(x, y, z);
        base[i][0] = x;
        base[i][1] = y;
        base[i][2] = z;
        alfa += 2*PI/DIVIDER;
    }
}

void GlWidget::Cone::Drow() {

    glFrontFace(GL_CCW);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3fv(vertex);
        for(unsigned i=0; i < DIVIDER; i++) {
             glVertex3fv(base[i]);
         }
        glVertex3fv(base[0]);
    glEnd();

    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_FAN);
         glVertex3fv(baseCenter);
         for(unsigned i=0; i < DIVIDER; i++) {
             glVertex3fv(base[i]);
         }
         glVertex3fv(base[0]);
    glEnd();
}

void GlWidget::Cone::DrowPoints() {

    glBegin(GL_POINTS);
        glVertex3fv(baseCenter);
        glVertex3fv(vertex);
        for(unsigned i=0; i < DIVIDER; i++) {
            glVertex3fv(base[i]);
        }
    glEnd();
}

void GlWidget::initializeGL() {

    drawOptionsInit();

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glColor3f(0.5f, 1.0f, 0.5f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_ALPHA_TEST);
//    glEnable(GL_BLEND);


    glShadeModel(GL_FLAT);
    GLfloat ambientLight[] =  { 1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat specular[] =  { 1.0f, 1.0f, 1.0f, 1.0f};
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = { 100.0f, 30.0f, 100.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 64);
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
}

void GlWidget::paintGL() {

    glPointSize(m_pointSize);
    glLineWidth(m_lineSize);
    glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(m_nSca, m_nSca, m_nSca);
    glTranslatef(0.0f, m_zTra, 0.0f);
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);

    glDisable(GL_ALPHA_TEST);
    glColor3f(1.0, 0.0, 0.0);
    if(m_isDrowPointsOnPoligon) {
        m_Cone.DrowPoints();
    }
    glEnable(GL_ALPHA_TEST);

    glColor4f(m_colourR, m_colourG, m_colourB, m_colourAlfa);
    glAlphaFunc(m_alfaFunc, m_alfaRef);

    m_Cone.Drow();
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

    m_isDrowLinesOnPoligon = true;
    m_isDrowPointsOnPoligon = true;
    m_colourR = 0.5f;
    m_colourB = 0.5f;
    m_colourG = 0.5f;
    m_colourAlfa = 0.5f;
    glGetFloatv(GL_POINT_SIZE_RANGE, m_sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &m_step);
    m_pointSize = m_sizes[0] + 20*m_step;
    m_lineSize = m_sizes[0] + 20*m_step;
    m_polygonMode = GL_FILL;
    m_alfaFunc = GL_ALWAYS;
    m_alfaRef = 0.50;
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
    updateGL();
}

void GlWidget::setColourG(float colour) {

    assert((colour >= (M_COLOUR_BORDER_FROM - M_EPS)) &&
           (colour <= (M_COLOUR_BORDER_TO + M_EPS)));

    m_colourG = colour;
    updateGL();
}

void GlWidget::setColourAlfa(float colour) {

    assert((colour >= (M_COLOUR_BORDER_FROM - M_EPS)) &&
           (colour <= (M_COLOUR_BORDER_TO + M_EPS)));

    m_colourAlfa = colour;
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


void GlWidget::setAlfaFunc(int param) {

    assert((param >= 0) && (param <= 7) && "alfaFunc");

    switch(param) {
    case 0:
        m_alfaFunc = GL_NEVER;
        break;

    case 1:
        m_alfaFunc = GL_LESS;
        break;

    case 2:
        m_alfaFunc = GL_EQUAL;
        break;

    case 3:
        m_alfaFunc = GL_LEQUAL;
        break;

    case 4:
        m_alfaFunc = GL_GREATER;
        break;

    case 5:
        m_alfaFunc = GL_NOTEQUAL;
        break;

    case 6:
        m_alfaFunc = GL_GEQUAL;
        break;

    case 7:
        m_alfaFunc = GL_ALWAYS;
        break;
    }
}

void GlWidget::setAlfaRef(double param) {

    assert((param >= 0.0 - M_EPS) && (param <= 1.0 + M_EPS) && "alpha ref");

    m_alfaRef = (GLclampf)param;
}

GLfloat* GlWidget::getNormalVector(GLfloat p1[3], GLfloat p2[3], GLfloat p3[3]) {

    GLfloat* v1 = new GLfloat[3]();
    v1[0] = p1[0] - p2[0];
    v1[1] = p1[1] - p2[1];
    v1[2] = p1[2] - p2[2];

    GLfloat* v2 = new GLfloat[3]();
    v2[0] = p1[0] - p3[0];
    v2[1] = p1[1] - p3[1];
    v2[2] = p1[2] - p3[2];

    GLfloat* nornal = new GLfloat[3]();
    nornal[0] = v1[1]*v2[2] - v1[2]*v2[1];
    nornal[1] = v1[2]*v2[0] - v1[0]*v2[2];
    nornal[2] = v1[0]*v2[1] - v1[1]*v2[0];

    delete[] v1;
    delete[] v2;

    return nornal;
}

