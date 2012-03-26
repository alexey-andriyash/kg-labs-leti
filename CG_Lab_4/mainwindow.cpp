//created by Alexey Andriyash
//KG, gr8304, SPEU(LETI), 2012

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setMenuWidget(createMenuBar(this));
    addDockWidget(Qt::TopDockWidgetArea, createDockWidget(this));
    setCentralWidget(createCentralWidget(this));
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

    return tabWidget;
}

void MainWindow::ps_aboutAction() {

    QMessageBox::about(this, tr("About"),
              tr("CG, Lab #4 <p>student: Andriyash Alexey <p>group: 8304<p>2012"));
}

void MainWindow::createConnections() {

    connect(m_aboutAction, SIGNAL(triggered()),
                                  this, SLOT(ps_aboutAction()));

}
