#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QCoreApplication>
#include <QComboBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create central OpenGL widget
    glWidget = new Renderer(this);
    setCentralWidget(glWidget);

    // Create UI components
    createToolBars();
    createDockWindows();
    createStatusBar();

    // Set initial window size
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createDockWindows()
{
    // Left dock widget
    leftDock = new QDockWidget(tr("Left Panel"), this);
    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    leftDock->setFeatures(QDockWidget::DockWidgetMovable |
                          QDockWidget::DockWidgetFloatable |
                          QDockWidget::DockWidgetClosable);

    // Create content for left dock
    QWidget* leftWidget = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(new QPushButton("Left Button 1"));
    leftLayout->addWidget(new QPushButton("Left Button 2"));
    leftLayout->addStretch();
    leftDock->setWidget(leftWidget);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    // Right dock widget
    rightDock = new QDockWidget(tr("Right Panel"), this);
    rightDock->setAllowedAreas(Qt::RightDockWidgetArea);
    rightDock->setFeatures(QDockWidget::DockWidgetMovable |
                           QDockWidget::DockWidgetFloatable |
                           QDockWidget::DockWidgetClosable);

    // Create content for right dock
    QWidget* rightWidget = new QWidget();
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(new QPushButton("Right Button 1"));
    rightLayout->addWidget(new QPushButton("Right Button 2"));
    rightLayout->addStretch();
    rightDock->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    // Set initial sizes (optional)
    resizeDocks({leftDock, rightDock}, {200, 200}, Qt::Horizontal);
}

void MainWindow::loadStyles()
{
    styleComboBox->clear();

    // Ajouter les styles depuis les ressources
    QDir resourceDir(":/style");
    if (resourceDir.exists()) {
        QStringList filters;
        filters << "*.qss";
        QStringList styleFiles = resourceDir.entryList(filters, QDir::Files);

        for (const QString &file : styleFiles) {
            QString styleName = file.left(file.length() - 4); // Enlever le .qss
            styleComboBox->addItem(styleName);
        }
    }
}

void MainWindow::changeStyle(const QString &styleName)
{
    QString styleFile = QString(":/style/%1.qss").arg(styleName);
    QFile file(styleFile);

    if (!file.exists()) {
        qDebug() << "Style file does not exist:" << styleFile;
        return;
    }

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream styleStream(&file);
        this->setStyleSheet(styleStream.readAll());
        file.close();
    } else {
        qDebug() << "Cannot open style file:" << styleFile;
    }
}

void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("Main Toolbar"));
    mainToolBar->setMovable(false);

    // Style selector
    mainToolBar->addWidget(new QLabel(" Style: "));
    styleComboBox = new QComboBox();
    loadStyles();
    connect(styleComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::changeStyle);
    mainToolBar->addWidget(styleComboBox);

    mainToolBar->addSeparator();

    QAction* resetView = mainToolBar->addAction("Reset View");
    QAction* wireframe = mainToolBar->addAction("Wireframe");
    QAction* solid = mainToolBar->addAction("Solid");

    // Add separators for organization
    mainToolBar->addSeparator();

    // Add some view manipulation tools
    QAction* pan = mainToolBar->addAction("Pan");
    QAction* rotate = mainToolBar->addAction("Rotate");
    QAction* zoom = mainToolBar->addAction("Zoom");
}
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

// In MainWindow.cpp:
void MainWindow::createMenus()
{
    QMenuBar *menuBar = new QMenuBar(this);
    viewMenu = menuBar->addMenu(tr("&View"));
    viewMenu->addAction(leftDock->toggleViewAction());
    viewMenu->addAction(rightDock->toggleViewAction());
    setMenuBar(menuBar);
}
