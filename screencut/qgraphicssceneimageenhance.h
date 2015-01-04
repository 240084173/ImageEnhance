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

	//��Ա����
	QGraphicsPixmapItem *item;//����item
	QGraphicsPixmapItem *itemTemp;
	QPixmap backgroundpixmap;//����Ӱ�ı���ͼƬ
	QPixmap orginalpixmap;//ԭͼ��
	QPixmap shotpixmap;//ѡ�е�ͼƬ
	
	enum shotState{initShot,beginShot,finishShot,endShot,beginMoveShot,finishMoveShot,beginControl,finishControl,tempcontrol}; //���н�����״̬
	enum controlPointEnum{moveControl0,moveControlLeft,moveControlTopLeft,moveControlTop,moveControlTopRight,moveControlRight,moveControlBottomRight,moveControlBottom,moveControlBottomLeft};

	shotState currentShotState; //��ǰ�Ľ���״̬

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
	controlPointEnum controlValue; //��¼�ƶ����Ƶ��ֵ
	QGraphicsRectItem *rectTemp;
	void pointBoundary(QPointF &tempPoint);
	void draw8ControlPoint(QPainter &painter);
	//void getMoveAllSelectedRect(void);



};


#endif