#ifndef QGRAPHICSRECTITEMIMAGEENHANCE_H
#define QGRAPHICSRECTITEMIMAGEENHANCE_H

#include "qgraphicsitem.h"
#include "qrect.h"
#include "qgraphicssceneimageenhance.h"

class QGraphicsRectItemImageEnhance : public QGraphicsRectItem
{
public:
	QGraphicsRectItemImageEnhance(QRectF rect);
	QGraphicsRectItemImageEnhance();
	~QGraphicsRectItemImageEnhance();
	//QGraphicsSceneImageEnhance::shotState *currentShotState; 
private:

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	//void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
	void mouseMoveEvent(QGraphicsSceneEvent *event);
	//void mousePressEvent(QGraphicsSceneEvent *event);
//	void moveBy(qreal dx, qreal dy);
};


#endif //QGRAPHICSRECTITEMIMAGEENHANCE_H