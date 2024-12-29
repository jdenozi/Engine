#pragma once

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include "renderer.h"
#include "QComboBox"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createDockWindows();
    void createToolBars();
    void createStatusBar();
    void createMenus();
    void loadStyles();
    void changeStyle(const QString &styleName);

    Renderer *glWidget;
    QDockWidget *leftDock;
    QDockWidget *rightDock;
    QToolBar *mainToolBar;
    QMenu *viewMenu;
    QComboBox *styleComboBox;
};

