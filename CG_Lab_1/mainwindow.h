//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"

#include <QMainWindow>
#include <QtGui>
#include <QtOpenGL>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

private slots:

    void ps_aboutAction();
    void sl_addVertex();
    void sl_setPointOrLineSize();
    void sl_setColour_R();
    void sl_setColour_B();
    void sl_setColour_G();

private:

    void setWidgetSettings();
    void createWidgetSettings();
    void createActions();
    void createConnections();

    float getSliderFloatPos(QSlider const* const);

    QMenuBar* createMenuBar(QWidget* parent = 0);
    QWidget* createCentralWidget(QWidget* parent = 0);

    QDockWidget* createDockWidget(QWidget* parent = 0);
    QWidget* createToolKitFrame(QWidget* parent = 0);
    QWidget* createVertexBox(QWidget* parent = 0);
    QWidget* createPoligonBox(QWidget* parent = 0);
    QComboBox* createBeginModeSwitcher(QWidget* parent = 0);
    QWidget* createDrowParameterBox(QWidget* parent = 0);
    QWidget* createScisorBox(QWidget* parent = 0);
    QWidget* createAlfaFunctBox(QWidget* parent = 0);
    QWidget* createBlendFunctBox(QWidget* parent = 0);

    QMenuBar* m_menuBar;
    QDockWidget* m_dockWidget;
    QFrame* m_toolKitWidget;
    GlWidget* m_glWidget;

    QAction* m_aboutAction;

    QDoubleSpinBox* m_xSpinBox;
    QDoubleSpinBox* m_ySpinBox;
    QPushButton* m_deleteVertexButtion;
    QPushButton* m_addVertexButtion;
    QComboBox* m_windingSwicher;
    QComboBox* m_poligoneModeSwicher;
    QComboBox* m_beginModeSwicher;
    QCheckBox* m_poligonPointCheckBox;
    QCheckBox* m_poligonLinesCheckBox;
    QSlider* m_pointOrLineSlider;
    QSlider* m_pointSlider; //!
    QSlider* m_lineSlider; //!
    QSlider* m_colour_R_Slider;
    QSlider* m_colour_B_Slider;
    QSlider* m_colour_G_Slider;
    QDoubleSpinBox* m_sclisorXSpinBox;
    QDoubleSpinBox* m_sclisorYSpinBox;
    QDoubleSpinBox* m_sclisorWSpinBox;
    QDoubleSpinBox* m_sclisorHSpinBox;
    QPushButton* m_sclisorSetButton;
    QComboBox* m_alfaFunctComboBox;
    QDoubleSpinBox* m_alfaRefSpinBox;
    QComboBox* m_blendSfactorComboBox;
    QComboBox* m_blendDfactorComboBox;
};

#endif // MAINWINDOW_H
