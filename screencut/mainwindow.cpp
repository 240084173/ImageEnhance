#include "mainwindow.h"
#include "qgraphicsview.h"
#include "qfiledialog.h"
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QPoint>
#include "QContextMenuEvent"
#include "qgraphicssceneimageenhance.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("ImageEnhance"));
	view=new QGraphicsView(this);
	view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	scene=new QGraphicsSceneImageEnhance();
	scene->setParent(view);
	scene->setPixelItem();
	scene->initScreenState();
	setCentralWidget(view);

	image=new QImage();

	createActions();
	createMenus();
	createToolBars();

	connect(scene,SIGNAL(signalSetArrowCursor()),this,SLOT(slotSetArrowCursor()));
	connect(scene,SIGNAL(signalSetOpenHandCursor()),this,SLOT(slotSetOpenHandCursor()));
	connect(scene,SIGNAL(signalSetCrossCursor()),this,SLOT(slotSetCrossCursor()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
	/*QAction *pictureOpenAction;
	QAction *pictureSaveAction;
	QAction *cutScreenAction;*/

	pictureOpenAction=new QAction(QIcon(":/PNG/open.png"),tr("open"),this);
	pictureOpenAction->setShortcut(tr("Ctrl+O"));
	pictureOpenAction->setStatusTip(tr("open a picture"));
	connect(pictureOpenAction,SIGNAL(triggered()),this,SLOT(slotOpenPicture()));

	pictureSaveAction=new QAction(QIcon(":/PNG/save.png"),tr("save"),this);
	pictureSaveAction->setShortcut(tr("Ctrl+S"));
	pictureSaveAction->setStatusTip(tr("save a picture"));
	connect(pictureSaveAction,SIGNAL(triggered()),this,SLOT(slotSavePicture()));

	cutScreenAction=new QAction(QIcon(":/PNG/puzzle.png"),tr("cut"),this);
	cutScreenAction->setShortcut(tr("Ctrl+X"));
	cutScreenAction->setStatusTip(tr("cut Screen"));
	connect(cutScreenAction,SIGNAL(triggered()),this,SLOT(slotCutPicture()));
	
}

void MainWindow::createMenus()
{
	pictureMenu=menuBar()->addMenu(tr("picture"));
	pictureMenu->addAction(pictureOpenAction);
	pictureMenu->addAction(pictureSaveAction);

	cutScreenMenu=menuBar()->addMenu(tr("cutScreen"));
	cutScreenMenu->addAction(cutScreenAction);

}

void MainWindow::createToolBars()
{
	pictureTool=addToolBar("picture");
	pictureTool->addAction(pictureOpenAction);
	pictureTool->addAction(pictureSaveAction);

	cutScreenTool=addToolBar("cut Screen");
	cutScreenTool->addAction(cutScreenAction);

	pictureTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);		//!!!!!!!
	pictureTool->setMovable(false);
	

}

void MainWindow::slotOpenPicture()
{
	fileName=QFileDialog::getOpenFileName(this,
										  tr("open picture dialog"),
										  tr("F:\\Project03-imageenhance\\image"),
										  //tr("E:\\QT-imageenhance\\image"),
										  tr("all files;;png(*.png);;jpg(*.jpg);;jpeg(*.jpeg);;bmp(*.bmp)"));
	image->load(fileName);
	scene->update();
	scene->clear();
	scene->item=new QGraphicsPixmapItem();
	scene->item->setPixmap(QPixmap::fromImage(*image));
	scene->orginalpixmap=QPixmap::fromImage(*image);
	scene->setSceneRect(QRect(0,0,image->width(),image->height()));		//设定场景的边界，可以使得在中央
	scene->addItem(scene->item);
	view->setScene(scene);		
	view->show();
	
}

void MainWindow::slotSavePicture()
{

}

void MainWindow::slotCutPicture()
{
	//setCursor(Qt::CrossCursor);
	QPixmap pixmap=scene->orginalpixmap;
	QPainter painter(&pixmap);
	painter.setPen(QPen(QColor(10,10,100)));
	painter.drawPixmap(image->width(),image->height(),pixmap);
	painter.fillRect(0,0,image->width(),image->height(),QColor(0,0,0,100));
	scene->backgroundpixmap=pixmap;
	scene->sceneUpdate(scene->backgroundpixmap);
	scene->initScreenState();
	scene->setParent(view);
	scene->currentShotState=scene->beginShot;
	//scene->item->setCursor(Qt::CrossCursor);
	//cutScreenMenu->setEnabled(false);
	cutScreenAction->setEnabled(false);
	//scene->item->setCursor(Qt::CrossCursor);
	//view->setCursor(Qt::CrossCursor);
	//scene->update();
}

void MainWindow::slotSetArrowCursor()
{
	view->setCursor(Qt::ArrowCursor);
}

void MainWindow::slotSetOpenHandCursor()
{
	view->setCursor(Qt::OpenHandCursor);
}

void MainWindow::slotSetCrossCursor()
{
	view->setCursor(Qt::CrossCursor);
}

void MainWindow::initSelectedMenu()
{
	savePixmapAction = new QAction(tr("save"),this);
	cancelAction =new QAction(QStringLiteral("reselect"),this);
	quitAction = new QAction(QStringLiteral("quit"),this);
	contextMenu = new QMenu(this);

	connect(savePixmapAction,SIGNAL(triggered()),this,SLOT(savePixmap()));
	connect(cancelAction,SIGNAL(triggered()),this,SLOT(cancelSelectedRect()));
	connect(quitAction,SIGNAL(triggered()),this,SLOT(quitCutScreen()));	  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void MainWindow::savePixmap()
{
	QString fileName;
	fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存图片"),QDir::currentPath(),tr("Images (*.jpg *.png *.bmp)"));
	if(fileName.isNull())
		return;

	scene->shotpixmap.save(fileName);
	scene->sceneUpdate(scene->shotpixmap);
	scene->orginalpixmap=scene->shotpixmap;
	scene->initScreenState();
	scene->setParent(view);
	scene->currentShotState=scene->initShot;
	cutScreenAction->setEnabled(true);
}

void MainWindow::cancelSelectedRect()
{
	QPixmap tempbg=scene->backgroundpixmap;
	scene->sceneUpdate(tempbg);
	scene->initScreenState();
	scene->setParent(view);
	scene->currentShotState=scene->beginShot;
	scene->updateCursor();
	view->setCursor(Qt::ArrowCursor);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	if (scene->currentShotState!=scene->initShot)
	{
		initSelectedMenu();	
		contextMenu->addAction(savePixmapAction);
		contextMenu->addAction(cancelAction);
		contextMenu->addAction(quitAction);	   
		contextMenu->exec(event->globalPos()) ;
	}
	
}

void MainWindow::quitCutScreen()
{  
	QPixmap tempbg=scene->orginalpixmap;
	scene->sceneUpdate(tempbg);
	scene->initScreenState();
	//scene->currentShotState=scene->initShot;
	cutScreenAction->setEnabled(true);
	scene->setParent(view);
	
	scene->currentShotState=scene->initShot;
	scene->updateCursor();
	view->setCursor(Qt::ArrowCursor);
}
