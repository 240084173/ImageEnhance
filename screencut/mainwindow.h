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

	void createMenus();				//�����˵�
	void createActions();			//��������
	void createToolBars();			//����������

public slots:
	void slotOpenPicture();
	void slotSavePicture();
	void slotCutPicture();
	void cancelSelectedRect(); //ȡ��ѡ������
	void savePixmap(); //��ѡȡ��Ϊ�ķ���
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

	QAction *savePixmapAction; //����ͼƬ��Ϊ
	QAction *cancelAction; //ȡ��ѡȡ��Ϊ
	QAction *quitAction; //�˳�ѡȡ��Ϊ
	QMenu *contextMenu; //ѡ�������Ҽ��˵�


	void initSelectedMenu();
	void contextMenuEvent(QContextMenuEvent *event);
};

#endif // MAINWINDOW_H
