#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "qgraphicsitem.h"
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QPoint>
#include "qgraphicssceneimageenhance.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void createMenus();				//创建菜单
	void createActions();			//创建动作
	void createToolBars();			//创建工具栏

public slots:
	void slotOpenPicture();
	void slotSavePicture();
	void slotCutPicture();
	void cancelSelectedRect(); //取消选择区域
	void savePixmap(); //保选取行为的方法
	void quitCutScreen();
	void slotSetArrowCursor();
	void slotSetOpenHandCursor();
	void slotSetCrossCursor();

private:
	Ui::MainWindowClass ui;
	QMenu *pictureMenu;
	QMenu *cutScreenMenu;
	QToolBar *pictureTool;
	QToolBar *cutScreenTool;
	QAction *pictureOpenAction;
	QAction *pictureSaveAction;
	QAction *cutScreenAction;

	QGraphicsView *view;
	QGraphicsSceneImageEnhance *scene;
	QGraphicsPixmapItem *item;

	QString fileName;
	QImage *image;

	QAction *savePixmapAction; //保存图片行为
	QAction *cancelAction; //取消选取行为
	QAction *quitAction; //退出选取行为
	QMenu *contextMenu; //选中区域右键菜单


	void initSelectedMenu();
	void contextMenuEvent(QContextMenuEvent *event);
};

#endif // MAINWINDOW_H
