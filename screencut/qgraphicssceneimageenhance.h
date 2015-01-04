#ifndef QGRAPHICSSCENEIMAGEENHANCE_H
#define QGRAPHICSSCENEIMAGEENHANCE_H

#include "qgraphicsscene.h"
#include "qgraphicsrectitemimageenhance.h"
#include <QAction>
#include "QMenu"


class QGraphicsSceneImageEnhance : public QGraphicsScene // ,public QWidget
{
	Q_OBJECT
public:
	QGraphicsSceneImageEnhance();
	void setPixelItem();
	void setPixmap(QPixmap pixmap);
	void sceneUpdate(QPixmap pixmap);
	void selectShotPixmap();
	void selectShotPixmapMousePress();
	void selectShotPixmapMouseRelease();
	void selectShotPixmapMouseMoveEvent();
	void initScreenState();
	void updateCursor();

	//成员变量
	QGraphicsPixmapItem *item;//声明item
	QGraphicsPixmapItem *itemTemp;
	QPixmap backgroundpixmap;//有阴影的背景图片
	QPixmap orginalpixmap;//原图像
	QPixmap shotpixmap;//选中的图片
	
	enum shotState{initShot,beginShot,finishShot,endShot,beginMoveShot,finishMoveShot,beginControl,finishControl,tempcontrol}; //进行截屏的状态
	enum controlPointEnum{moveControl0,moveControlLeft,moveControlTopLeft,moveControlTop,moveControlTopRight,moveControlRight,moveControlBottomRight,moveControlBottom,moveControlBottomLeft};

	shotState currentShotState; //当前的截屏状态

signals:
	void signalSetArrowCursor();
	void signalSetOpenHandCursor();
	void signalSetCrossCursor();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
	QPointF beginPoint;
	QPointF endPoint;
	QPointF moveBeginPoint;
	QPointF moveEndPoint;
	
	QRect shotRect;
	controlPointEnum controlValue; //记录移动控制点的值
	QGraphicsRectItem *rectTemp;
	void pointBoundary(QPointF &tempPoint);
	void draw8ControlPoint(QPainter &painter);
	//void getMoveAllSelectedRect(void);



};


#endif