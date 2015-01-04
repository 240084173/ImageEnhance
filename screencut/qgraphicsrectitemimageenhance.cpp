#include "qgraphicsrectitemimageenhance.h"
#include "qcursor.h"
#include "qgraphicssceneimageenhance.h"
QGraphicsRectItemImageEnhance::QGraphicsRectItemImageEnhance(QRectF rect)
{
	//QGraphicsRectItem::QGraphicsRectItem(rect);
	QGraphicsRectItem::setRect(rect);
}

QGraphicsRectItemImageEnhance::QGraphicsRectItemImageEnhance()
{
	//QGraphicsRectItem::QGraphicsRectItem(rect);

}

QGraphicsRectItemImageEnhance::~QGraphicsRectItemImageEnhance()
{
}

void QGraphicsRectItemImageEnhance::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
	 
	setCursor(Qt::OpenHandCursor);
	//update();
}
//
//void QGraphicsRectItemImageEnhance::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
//{
//	setCursor(Qt::OpenHandCursor);
//	//update();
//}
//
void QGraphicsRectItemImageEnhance::mouseMoveEvent(QGraphicsSceneEvent *event)
{
	setCursor(Qt::CrossCursor);
}
//
//void QGraphicsRectItemImageEnhance::mousePressEvent(QGraphicsSceneEvent *event)
//{
//	 setCursor(Qt::OpenHandCursor);
//}
//
