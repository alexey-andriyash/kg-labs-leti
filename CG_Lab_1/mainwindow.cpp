//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setMenuWidget(createMenuBar(this));
    addDockWidget(Qt::LeftDockWidgetArea, createDockWidget(this));
    setCentralWidget(createCentralWidget(this));
    createWidgetSettings();
    createConnections();
}

void MainWindow::createActions() {

    m_aboutAction = new QAction(tr("&About"), this);
}

QMenuBar* MainWindow::createMenuBar(QWidget* parent) {

    createActions();
    m_menuBar = new QMenuBar(parent);
    m_menuBar->addAction(m_aboutAction);

    return m_menuBar;
}

QWidget* MainWindow::createCentralWidget(QWidget* parent) {

    m_glWidget = new GlWidget(parent);

    return m_glWidget;
}

QDockWidget* MainWindow::createDockWidget(QWidget * parent) {

    m_dockWidget = new QDockWidget(parent);
    m_dockWidget->setWidget(createToolKitFrame(m_dockWidget));
    m_dockWidget->setFloating(false);

    return m_dockWidget;
}

QWidget* MainWindow::createToolKitFrame(QWidget * parent) {

    QTabWidget* tabWidget = new QTabWidget(parent);
    tabWidget->addTab(createPoligonBox(parent), tr("PoligonOptions"));
    tabWidget->addTab(createVertexBox(parent), tr("VertexnOptions"));
    tabWidget->addTab(createDrowParameterBox(parent), tr("DrowOptions"));
    tabWidget->addTab(createScisorBox(parent), tr("ScisorOptions"));
    tabWidget->addTab(createAlfaFunctBox(parent), tr("AlfaFunctOptions"));
    tabWidget->addTab(createBlendFunctBox(parent), tr("BlendFunctOptions"));

    return tabWidget;
}

QWidget* MainWindow::createPoligonBox(QWidget* parent) {

    QGroupBox* poligonBox = new QGroupBox(tr(" POLIGON OPTIONS "), parent);
    QBoxLayout* poligonBoxLayout = new QHBoxLayout(poligonBox);

    QGroupBox*  beginModeBox = new QGroupBox(tr(" begin mode "), parent);
    QBoxLayout* beginModeLayout = new QVBoxLayout(beginModeBox);
    beginModeLayout->addWidget(createBeginModeSwitcher(beginModeBox));

    QGroupBox* modeBox = new QGroupBox(tr(" poligon mode "), poligonBox);
    QBoxLayout* modeLayout = new QVBoxLayout(modeBox);
    m_poligoneModeSwicher = new QComboBox(modeBox);
    modeLayout->addWidget(m_poligoneModeSwicher);

    QGroupBox* optionsBox = new QGroupBox(tr(" more options "), parent);
    QBoxLayout* optionsLayout = new QVBoxLayout(optionsBox);
    m_poligonPointCheckBox = new QCheckBox(tr("draw points on poligon"), optionsBox);
    m_poligonLinesCheckBox = new QCheckBox( tr("drow lines on poligon"), optionsBox);
    optionsLayout->addWidget(m_poligonPointCheckBox);
    optionsLayout->addWidget(m_poligonLinesCheckBox);

    poligonBoxLayout->addWidget(beginModeBox);
    poligonBoxLayout->addWidget(modeBox);
    poligonBoxLayout->addWidget(optionsBox);

    return poligonBox;
}

QWidget* MainWindow::createVertexBox(QWidget* parent) {

    QGroupBox* vertexBox = new QGroupBox(tr(" VERTEX OPTIONS "), parent);
    QBoxLayout* vertexBoxLayout = new QHBoxLayout(vertexBox);

    QGroupBox* vertexManagmentBox = new QGroupBox(tr(" add / delete "), parent);
    QBoxLayout* addingVertexLayout = new QVBoxLayout(vertexManagmentBox);
    m_deleteVertexButtion = new QPushButton(tr("delete all"), vertexManagmentBox);
    m_addVertexButtion = new QPushButton(tr("add"), vertexManagmentBox);
    m_xSpinBox = new QDoubleSpinBox(vertexManagmentBox);
    m_ySpinBox = new QDoubleSpinBox(vertexManagmentBox);
    addingVertexLayout->addWidget(m_xSpinBox);
    addingVertexLayout->addWidget(m_ySpinBox);
    addingVertexLayout->addWidget(m_addVertexButtion);
    addingVertexLayout->addWidget(m_deleteVertexButtion);

    QGroupBox* windingManagmentBox = new QGroupBox(tr(" winding"), parent);
    QVBoxLayout* windingVertexLayout = new QVBoxLayout(windingManagmentBox);
    m_windingSwicher = new QComboBox(windingManagmentBox);
    windingVertexLayout->addWidget(m_windingSwicher);

    vertexBoxLayout->addWidget(windingManagmentBox);
    vertexBoxLayout->addWidget(vertexManagmentBox);

    return vertexBox;
}

QWidget* MainWindow::createDrowParameterBox(QWidget* parent) {

    QGroupBox* parameterBox = new QGroupBox(tr(" ADDITION OPTIONS "), parent);
    QBoxLayout* parameterBoxLayout = new QHBoxLayout(parameterBox);

    QGroupBox* pointOrLineSizeBox = new QGroupBox(tr(" point/line size"),
                                                            parameterBox);
    QBoxLayout* sizeLayout = new QVBoxLayout(pointOrLineSizeBox);
    m_pointOrLineSlider = new QSlider(Qt::Horizontal, pointOrLineSizeBox);
    sizeLayout->addWidget(m_pointOrLineSlider);

    QGroupBox* colourBox = new QGroupBox(tr(" colour "), parameterBox);
    QBoxLayout* colourLayout = new QVBoxLayout(colourBox);
    m_colour_R_Slider = new QSlider(Qt::Horizontal, colourBox);
    m_colour_B_Slider = new QSlider(Qt::Horizontal, colourBox);
    m_colour_G_Slider = new QSlider(Qt::Horizontal, colourBox);
    QBoxLayout* colour_R_Layout = new QHBoxLayout(colourBox);
    QBoxLayout* colour_B_Layout = new QHBoxLayout(colourBox);
    QBoxLayout* colour_G_Layout = new QHBoxLayout(colourBox);
    colour_R_Layout->addWidget(new QLabel(tr("R: "), colourBox));
    colour_R_Layout->addWidget(m_colour_R_Slider);
    colour_B_Layout->addWidget(new QLabel(tr("B: "), colourBox));
    colour_B_Layout->addWidget(m_colour_B_Slider);
    colour_G_Layout->addWidget(new QLabel(tr("G: "), colourBox));
    colour_G_Layout->addWidget(m_colour_G_Slider);
    colourLayout->addLayout(colour_R_Layout);
    colourLayout->addLayout(colour_B_Layout);
    colourLayout->addLayout(colour_G_Layout);

    parameterBoxLayout->addWidget(pointOrLineSizeBox);
    parameterBoxLayout->addWidget(colourBox);

    return parameterBox;
}

QWidget* MainWindow::createScisorBox(QWidget* parent) {

    QGroupBox* scisorBox = new QGroupBox(tr(" SCISOR AREA"), parent);

    m_sclisorXSpinBox = new QDoubleSpinBox(scisorBox);
    m_sclisorYSpinBox = new QDoubleSpinBox(scisorBox);
    m_sclisorWSpinBox = new QDoubleSpinBox(scisorBox);
    m_sclisorHSpinBox = new QDoubleSpinBox(scisorBox);
    m_sclisorSetButton = new QPushButton(tr("Set"), scisorBox);

    QBoxLayout* mainLayout = new QVBoxLayout(scisorBox);

    QBoxLayout* vLayoutXY = new QHBoxLayout(scisorBox);
    vLayoutXY->addWidget (new QLabel(tr("X: "), scisorBox));
    vLayoutXY->addWidget (m_sclisorXSpinBox);
    vLayoutXY->addWidget (new QLabel(tr("  Y: "), scisorBox));
    vLayoutXY->addWidget (m_sclisorYSpinBox);

    QBoxLayout* vLayoutHW = new QHBoxLayout(scisorBox);
    vLayoutHW->addWidget (new QLabel(tr("Width: "), scisorBox));
    vLayoutHW->addWidget (m_sclisorHSpinBox);
    vLayoutHW->addWidget (new QLabel(tr("Height: "), scisorBox));
    vLayoutHW->addWidget (m_sclisorWSpinBox);

    mainLayout->addLayout(vLayoutXY);
    mainLayout->addLayout(vLayoutHW);
    mainLayout->addWidget(m_sclisorSetButton);

    return scisorBox;
}

QWidget* MainWindow::createAlfaFunctBox(QWidget* parent) {

    QGroupBox* alfaFunctBox = new QGroupBox(tr(" ALFA FUNC"), parent);

    return alfaFunctBox;
}

QWidget* MainWindow::createBlendFunctBox(QWidget* parent) {

    QGroupBox* blendFunctBox = new QGroupBox(tr(" BLEND FUNC"), parent);

    return blendFunctBox;
}

QComboBox* MainWindow::createBeginModeSwitcher(QWidget * parent) {

    m_beginModeSwicher = new QComboBox(parent);
    m_beginModeSwicher->addItem("GL_POINT", GL_POINT);
    m_beginModeSwicher->addItem("GL_LINES", GL_LINES);
    m_beginModeSwicher->addItem("GL_LINE_LOOP", GL_LINE_LOOP);
    m_beginModeSwicher->addItem("GL_LINE_STRIP", GL_LINE_STRIP);
    m_beginModeSwicher->addItem("GL_TRIANGLES", GL_TRIANGLES);
    m_beginModeSwicher->addItem("GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP);
    m_beginModeSwicher->addItem("GL_TRIANGLE_FAN" , GL_TRIANGLE_FAN);
    m_beginModeSwicher->addItem("GL_QUADS", GL_QUADS);
    m_beginModeSwicher->addItem("GL_QUAD_STRIP", GL_QUAD_STRIP);
    m_beginModeSwicher->addItem("GL_POLYGON", GL_POLYGON);
    m_beginModeSwicher->setEditable(false);

    return m_beginModeSwicher;
}

void MainWindow::ps_aboutAction() {

    QMessageBox::about(this, tr("About"),
              tr("CG, Lab #1 <p>student: Andriyash Alexey <p>group: 8304<p>2012"));
}

void MainWindow::createConnections() {

    connect(m_aboutAction, SIGNAL(triggered()),
                        this, SLOT(ps_aboutAction()));
    connect(m_beginModeSwicher, SIGNAL(activated(int)),
                    m_glWidget, SLOT(setBeginMode(int)));

    connect(m_poligoneModeSwicher, SIGNAL(activated(int)),
                    m_glWidget, SLOT(setPoligonMode(int)));

    connect(m_poligonPointCheckBox, SIGNAL(stateChanged(int)),
                    m_glWidget, SLOT(setDrawPointsOnPoligon(int)));
    connect(m_poligonLinesCheckBox, SIGNAL(stateChanged(int)),
                    m_glWidget, SLOT(setDrawLinesOnPoligon(int)));

    connect(m_windingSwicher, SIGNAL(activated(int)),
                    m_glWidget, SLOT(setWinding(int)));
    connect(m_windingSwicher, SIGNAL(activated(int)),
                    m_glWidget, SLOT(setWinding(int)));

    connect(m_deleteVertexButtion, SIGNAL(pressed()),
                    m_glWidget, SLOT(deleteAllPoints()));

    connect(m_addVertexButtion, SIGNAL(pressed()),
                    this, SLOT(sl_addVertex()));


    connect(m_pointOrLineSlider, SIGNAL(sliderMoved(int)),
                    this, SLOT(sl_setPointOrLineSize()));

    connect(m_colour_R_Slider, SIGNAL(sliderMoved(int)),
                    this, SLOT(sl_setColour_R()));

    connect(m_colour_G_Slider, SIGNAL(sliderMoved(int)),
                    this, SLOT(sl_setColour_B()));

    connect(m_colour_B_Slider, SIGNAL(sliderMoved(int)),
                    this, SLOT(sl_setColour_G()));

}

void MainWindow::createWidgetSettings() {

    m_poligoneModeSwicher->addItem("GL_FILL", 0);
    m_poligoneModeSwicher->addItem("GL_LINE", 1);
    m_poligoneModeSwicher->addItem("GL_POINT", 2);

    m_poligonPointCheckBox->setCheckState(Qt::Checked);
    m_poligonLinesCheckBox->setCheckState(Qt::Checked);

    m_windingSwicher->addItem("GL_CCW", 0);
    m_windingSwicher->addItem("GL_CW", 1);

    m_xSpinBox->setRange(GlWidget::M_DRAW_AREA_FROM,
                                GlWidget::M_DRAW_AREA_TO);
    m_ySpinBox->setRange(GlWidget::M_DRAW_AREA_FROM,
                                GlWidget::M_DRAW_AREA_TO);
    m_xSpinBox->setSingleStep(0.01);
    m_ySpinBox->setSingleStep(0.01);

    m_pointOrLineSlider->setRange(0, 100);
    m_colour_R_Slider->setRange(0, 100);
    m_colour_B_Slider->setRange(0, 100);
    m_colour_G_Slider->setRange(0, 100);
    m_pointOrLineSlider->setSingleStep(1);
    m_colour_R_Slider->setSingleStep(1);
    m_colour_B_Slider->setSingleStep(1);
    m_colour_G_Slider->setSingleStep(1);
    m_pointOrLineSlider->setValue(0);
    m_colour_R_Slider->setValue(50);
    m_colour_B_Slider->setValue(50);
    m_colour_G_Slider->setValue(50);
}

void MainWindow::sl_addVertex() {

    double x = m_xSpinBox->value();
    double y = m_ySpinBox->value();
    m_glWidget->addVertex(x, y);
}

void MainWindow::sl_setPointOrLineSize() {

    float value = (float)((m_pointOrLineSlider->value())*
                          (m_glWidget->getSizes()[1] - m_glWidget->getSizes()[2]))/100;
    m_glWidget->setPointOrLineSize(value);
}

void MainWindow::sl_setColour_R() {

    float value = ((float)m_colour_R_Slider->value())/100;
    m_glWidget->setColourR(value);
}

void MainWindow::sl_setColour_B() {

    float value = ((float)m_colour_B_Slider->value())/100;
    m_glWidget->setColourB(value);
}

void MainWindow::sl_setColour_G() {

    float value = ((float)m_colour_G_Slider->value())/100;
    m_glWidget->setColourG(value);
}

float MainWindow::getSliderFloatPos(const QSlider *const slider) {

    return ((float)( (slider->value()*
                     (m_glWidget->getSizes()[1] - m_glWidget->getSizes()[0]))/100));
}
