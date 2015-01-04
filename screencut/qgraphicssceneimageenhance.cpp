#include "qgraphicssceneimageenhance.h"
#include "QGraphicsSceneEvent"
#include "qgraphicsitem.h"
#include "qpainter.h"
#include "QFileDialog"
#include "qwindow.h"
#include "qgraphicsrectitemimageenhance.h"
//#include "qgraphicsview.h

QGraphicsSceneImageEnhance::QGraphicsSceneImageEnhance()
{
	beginPoint = QPointF(0,0);
	endPoint = QPointF(0,0);
	currentShotState=initShot;
	controlValue = moveControl0;
    beginPoint =QPoint(0,0);
    endPoint = QPoint(0,0);
    moveBeginPoint = QPoint(0,0);
    moveEndPoint = QPoint(0,0);

	shotRect=QRect(0,0,0,0);
	//updateCursor();
}

void QGraphicsSceneImageEnhance::initScreenState()
{
	beginPoint = QPointF(0,0);
	endPoint = QPointF(0,0);
	currentShotState=initShot;
	controlValue = moveControl0;
    beginPoint =QPoint(0,0);
    endPoint = QPoint(0,0);
    moveBeginPoint = QPoint(0,0);
    moveEndPoint = QPoint(0,0);
	rectTemp=NULL;
   
	shotRect=QRect(0,0,0,0);

	//rectTemp=new QGraphicsRectItemImageEnhance();
	//emit signalSetCrossCursor();
	//item->setCursor(Qt::CrossCursor);
	item->acceptHoverEvents();
	updateCursor();
//	setCursor(Qt::CrossCursor);
	//rectTemp->setAcceptHoverEvents(false);
	//item->setCursor(Qt::CrossCursor);
}

void QGraphicsSceneImageEnhance::setPixelItem()
{
	item=new QGraphicsPixmapItem();
}

void QGraphicsSceneImageEnhance::setPixmap(QPixmap pixmap)
{
	orginalpixmap=pixmap;
}

void QGraphicsSceneImageEnhance::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button()==Qt::LeftButton && currentShotState==beginShot)
	{
		//选定初始截图区域
		currentShotState=tempcontrol;
		beginPoint=event->scenePos();
		selectShotPixmapMousePress();
	}
	//鼠标在左边框上
	else if ((currentShotState==finishMoveShot||currentShotState ==finishShot)
		&& QRectF(beginPoint.x()-5,beginPoint.y(),10,shotRect.height()).contains(event->scenePos().x(),event->scenePos().y()))
	{
		rectTemp->setCursor(Qt::SizeHorCursor);
		currentShotState=beginControl;
		controlValue=moveControlLeft;
		moveBeginPoint=event->scenePos();
	}
	//鼠标在右边框上
	else if ((currentShotState==finishMoveShot||currentShotState ==finishShot)
		&& QRectF(endPoint.x()-5,beginPoint.y(),10,shotRect.height()).contains(event->scenePos().x(),event->scenePos().y()))
	{
		rectTemp->setCursor(Qt::SizeHorCursor);
		currentShotState=beginControl;
		controlValue=moveControlRight;
		moveBeginPoint=event->scenePos();
	}
	//鼠标在上边框上
	else if ((currentShotState==finishMoveShot||currentShotState ==finishShot)
		&& QRectF(beginPoint.x(),beginPoint.y()-5,shotRect.width(),10).contains(event->scenePos().x(),event->scenePos().y()))
	{
		rectTemp->setCursor(Qt::SizeVerCursor);
		currentShotState=beginControl;
		controlValue=moveControlTop;
		moveBeginPoint=event->scenePos();
	}
	//鼠标在下边框上
	else if ((currentShotState==finishMoveShot||currentShotState ==finishShot)
		&& QRectF(beginPoint.x(),endPoint.y()-5,shotRect.width(),10).contains(event->scenePos().x(),event->scenePos().y()))
	{
		rectTemp->setCursor(Qt::SizeVerCursor);
		currentShotState=beginControl;
		controlValue=moveControlBottom;
		moveBeginPoint=event->scenePos();
	}
	else if(event->button()==Qt::LeftButton && ( currentShotState==finishShot || currentShotState ==finishMoveShot)
	   && shotRect.contains(event->scenePos().x(),event->scenePos().y()))
	  // && getMoveControlState(event->scenePos()) == moveControl0)
	{
 		currentShotState=beginMoveShot;
		moveBeginPoint=event->scenePos();
		rectTemp->setCursor(Qt::OpenHandCursor);
	}
	QGraphicsScene::mousePressEvent(event);	
	updateCursor();
}

void QGraphicsSceneImageEnhance::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && currentShotState==tempcontrol)
	{
		//选定初始截图区域后释放鼠标					   
		endPoint=event->scenePos();	
		selectShotPixmapMouseRelease();	
		currentShotState=finishShot;
		beginPoint=shotRect.topLeft();
		endPoint=shotRect.bottomRight();
		emit signalSetArrowCursor();
		rectTemp->setCursor(Qt::OpenHandCursor);
		updateCursor();
		//QTextCursor
	}
	else if(event->button() == Qt::LeftButton && currentShotState == beginMoveShot)
	{
		currentShotState = finishMoveShot;
		beginPoint=shotRect.topLeft();
		endPoint=shotRect.bottomRight();
		emit signalSetArrowCursor();
		rectTemp->setCursor(Qt::OpenHandCursor);
		updateCursor();
	}
	else if (event->button()==Qt::LeftButton && currentShotState == beginControl && (controlValue==moveControlLeft || controlValue == moveControlRight))
	{
		currentShotState = finishMoveShot;
		beginPoint=shotRect.topLeft();
		endPoint=shotRect.bottomRight();
		emit signalSetArrowCursor();
		rectTemp->setCursor(Qt::SizeHorCursor);
		updateCursor();
	}
	else if (event->button()==Qt::LeftButton && currentShotState == beginControl && (controlValue==moveControlTop || controlValue == moveControlBottom))
	{
		currentShotState = finishMoveShot;
		beginPoint=shotRect.topLeft();
		endPoint=shotRect.bottomRight();
		emit signalSetArrowCursor();
		rectTemp->setCursor(Qt::SizeVerCursor);
		updateCursor();
	}
	//else
	QGraphicsScene::mouseReleaseEvent(event);
	updateCursor();  
}

void QGraphicsSceneImageEnhance::updateCursor()
{
	if (currentShotState==initShot)
	{
		emit signalSetArrowCursor();
		item->setCursor(Qt::ArrowCursor);
	}
	else if (currentShotState==beginShot)
	{
		emit signalSetArrowCursor();//emit signalSetCrossCursor();
		item->setCursor(Qt::CrossCursor);
	}
	else if (currentShotState==beginMoveShot || currentShotState==finishShot || currentShotState == finishMoveShot)
	{
		//emit signalSetOpenHandCursor();
		//rectTemp->setCursor(Qt::OpenHandCursor);
		itemTemp->setCursor(Qt::OpenHandCursor);
		item->setCursor(Qt::ArrowCursor);
	}
	else if (currentShotState==beginControl && (controlValue==moveControlLeft || controlValue==moveControlRight))
	{
			item->setCursor(Qt::SizeHorCursor);
	}
	else if (currentShotState==beginControl &&(controlValue==moveControlBottom || controlValue==moveControlTop))
	{
		item->setCursor(Qt::SizeVerCursor);
	}
}



void QGraphicsSceneImageEnhance::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{	
	//QGraphicsScene::mouseMoveEvent(event);
	if(currentShotState==tempcontrol)
	{ 
		//选定初始截图区域过程
		endPoint=event->scenePos();
		selectShotPixmapMouseMoveEvent();
		QGraphicsScene::mouseMoveEvent(event);
	}
	else if (currentShotState==beginShot)
	{
		emit signalSetCrossCursor();
	}
	//鼠标在左右边框上
	else if ((currentShotState==finishMoveShot||currentShotState ==finishShot)
		&& (QRectF(endPoint.x()-5,beginPoint.y(),10,shotRect.height()).contains(event->scenePos().x(),event->scenePos().y())
		||QRectF(beginPoint.x()-5,beginPoint.y(),10,shotRect.height()).contains(event->scenePos().x(),event->scenePos().y())))
	{
		rectTemp->setCursor(Qt::SizeHorCursor);
		QGraphicsScene::mouseMoveEvent(event);
	}
	//鼠标在上下边框上
	else if ((currentShotState==finishMoveShot||currentShotState ==finishShot)
		&& (QRectF(beginPoint.x(),beginPoint.y()-5,shotRect.width(),10).contains(event->scenePos().x(),event->scenePos().y())
		||QRectF(beginPoint.x(),endPoint.y()-5,shotRect.width(),10).contains(event->scenePos().x(),event->scenePos().y())))
	{
		rectTemp->setCursor(Qt::SizeVerCursor);
		QGraphicsScene::mouseMoveEvent(event);
	}
	//鼠标在选中区域中
	else if( ( currentShotState==finishShot || currentShotState ==finishMoveShot)
		&& shotRect.contains(event->scenePos().x(),event->scenePos().y()))
		// && getMoveControlState(event->scenePos()) == moveControl0)
	{
		rectTemp->setCursor(Qt::OpenHandCursor);
		QGraphicsScene::mouseMoveEvent(event);
	}
	//左边
	else if (currentShotState == beginControl && controlValue == moveControlLeft)
	{
		rectTemp->setCursor(Qt::SizeHorCursor);
		currentShotState=beginControl;
		beginPoint.setX(beginPoint.x()-moveBeginPoint.x()+event->scenePos().x());
		selectShotPixmapMousePress();
		if (beginPoint.x()!=endPoint.x())
		{
			moveBeginPoint.setX(beginPoint.x());
			selectShotPixmapMouseMoveEvent();
		}
	QGraphicsScene::mouseMoveEvent(event);
		//	rectTemp->setCursor(Qt::OpenHandCursor);
	}
	//右边
	else if (currentShotState == beginControl && controlValue == moveControlRight)
	{
		rectTemp->setCursor(Qt::SizeHorCursor);
		currentShotState=beginControl;
		endPoint.setX(endPoint.x()-moveBeginPoint.x()+event->scenePos().x());
		pointBoundary(endPoint);
		if (beginPoint.x()!=endPoint.x())
		{
			moveBeginPoint.setX(endPoint.x());
			selectShotPixmapMouseMoveEvent();
			//rectTemp->setCursor(Qt::OpenHandCursor);
		}
		QGraphicsScene::mouseMoveEvent(event);
	}
	//上边
	else if (currentShotState == beginControl && controlValue == moveControlTop)
	{
		rectTemp->setCursor(Qt::SizeVerCursor);
		currentShotState=beginControl;
		beginPoint.setY(beginPoint.y()-moveBeginPoint.y()+event->scenePos().y());
		pointBoundary(beginPoint);
		//selectShotPixmapMousePress();
		if (beginPoint.y()!=endPoint.y())
		{
			moveBeginPoint.setY(beginPoint.y());
			selectShotPixmapMouseMoveEvent();
		//	rectTemp->setCursor(Qt::OpenHandCursor);
		}
		QGraphicsScene::mouseMoveEvent(event);
	}
	//下边
	else if (currentShotState == beginControl && controlValue == moveControlBottom)
	{
		rectTemp->setCursor(Qt::SizeVerCursor);
		currentShotState=beginControl;
		endPoint.setY(endPoint.y()-moveBeginPoint.y()+event->scenePos().y());
		pointBoundary(endPoint);
		if (beginPoint.y()!=endPoint.y())
		{
			moveBeginPoint.setY(endPoint.y());
			selectShotPixmapMouseMoveEvent();
		//	rectTemp->setCursor(Qt::OpenHandCursor);
		}
	}
	//移动
	else if(currentShotState==beginMoveShot  )			   //&& shotRect.contains(event->scenePos().x(),event->scenePos().y())
	{
		//emit signalSetOpenHandCursor();
		moveEndPoint = event->scenePos();
		QRect result;
		QPointF tmpBeginPoint,tmpEndPoint;
		int moveX,moveY;																		   
		int x,y;
		x=moveEndPoint.x()-moveBeginPoint.x();
		y=moveEndPoint.y()-moveBeginPoint.y();

		if((x+beginPoint.x())<0)
		{
			moveEndPoint.setX(moveBeginPoint.x()-beginPoint.x());
		}

		if((y+beginPoint.y())<0)
		{
			moveEndPoint.setY(moveBeginPoint.y()-beginPoint.y());
		}

		if((x+endPoint.x())>orginalpixmap.width())
		{
			if(x+beginPoint.x()+shotRect.width()>orginalpixmap.width())
			{
			//	moveEndPoint.setX(orginalpixmap.width()+moveBeginPoint.x()-beginPoint.x()-shotRect.width());
			}
			moveEndPoint.setX(orginalpixmap.width()+moveBeginPoint.x()-endPoint.x());
		}

		if((y+endPoint.y())>orginalpixmap.height())
		{
			if(y+beginPoint.y()+shotRect.height()>orginalpixmap.height())
			{
			//	moveEndPoint.setY(orginalpixmap.height()+moveBeginPoint.y()-beginPoint.y()-shotRect.height());
			}
			moveEndPoint.setY(orginalpixmap.height()+moveBeginPoint.y()-endPoint.y());
		}

		moveX=moveEndPoint.x()-moveBeginPoint.x();
		moveY=moveEndPoint.y()-moveBeginPoint.y();
		tmpBeginPoint.setX(beginPoint.x()+moveX);
		tmpBeginPoint.setY(beginPoint.y()+moveY);
		tmpEndPoint.setX(endPoint.x()+moveX);
		tmpEndPoint.setY(endPoint.y()+moveY);
		QPixmap tempbg=orginalpixmap;
		QPainter painter(&tempbg);
		painter.setPen(QPen(Qt::blue,4,Qt::SolidLine,Qt::FlatCap));
		painter.drawPixmap(tempbg.width(),tempbg.height(),tempbg);
		painter.fillRect(0,0,tempbg.width(),tempbg.height(),QColor(0,0,0,100));
		sceneUpdate(tempbg);  
		pointBoundary(tmpEndPoint);
	/*	if (tmpEndPoint.x()<0)
		{
			tmpEndPoint.setX(0);
		}
		if (tmpEndPoint.y()<0)
		{
			tmpEndPoint.setY(0);
		}
		if (tmpEndPoint.x()>orginalpixmap.width())
		{
			tmpEndPoint.setX(orginalpixmap.width());
		}
		if (tmpEndPoint.y()>orginalpixmap.height())
		{
			tmpEndPoint.setY(orginalpixmap.height());
		}*/
		//selectShotPixmap();
		int widthx=qAbs(tmpBeginPoint.x()-tmpEndPoint.x());
		int heighty=qAbs(tmpBeginPoint.y()-tmpEndPoint.y());
		if (widthx!=0 && heighty!=0)
		{	 
			int x=tmpBeginPoint.x()<tmpEndPoint.x()?tmpBeginPoint.x():tmpEndPoint.x();
			int y=tmpBeginPoint.y()<tmpEndPoint.y()?tmpBeginPoint.y():tmpEndPoint.y();
			shotRect=QRect(x,y,widthx,heighty);
			QPixmap temp=orginalpixmap.copy(x,y,widthx,heighty);	
			shotpixmap=temp;
			//QGraphicsPixmapItem *
			itemTemp=new QGraphicsPixmapItem();
			itemTemp->setPixmap(temp);
			this->addItem(itemTemp);
			itemTemp->setPos(QPointF(x,y));
			itemTemp->acceptHoverEvents();
			itemTemp->acceptedMouseButtons();
			rectTemp=new QGraphicsRectItem(QRectF(0,0,widthx,heighty));
			rectTemp->setParentItem(itemTemp);
			//rectTemp->setAcceptHoverEvents(true);
			//rectTemp->setAcceptedMouseButtons(false);
			QPen pen;
			pen.setWidth(3);
			pen.setColor(QColor(Qt::blue));
			rectTemp->setPen(pen);
			this->addItem(rectTemp);
		}
		QGraphicsScene::mouseMoveEvent(event);
	}
	//else
	QGraphicsScene::mouseMoveEvent(event);
	updateCursor();

}

void QGraphicsSceneImageEnhance::selectShotPixmapMousePress()
{	
	/*if (beginPoint.x()<0)
	{
		beginPoint.setX(0);
	}
	if (beginPoint.y()<0)
	{
		beginPoint.setY(0);
	}
	if (beginPoint.x()>orginalpixmap.width())
	{
		beginPoint.setX(orginalpixmap.width());
	}
	if (beginPoint.y()>orginalpixmap.height())
	{
		beginPoint.setY(orginalpixmap.height());
	}*/
	pointBoundary(beginPoint);
}

void QGraphicsSceneImageEnhance::pointBoundary(QPointF &tempPoint)
{
	if (tempPoint.x()<0)
	{
		tempPoint.setX(0);
	}
	if (tempPoint.y()<0)
	{
		tempPoint.setY(0);
	}
	if (tempPoint.x()>orginalpixmap.width())
	{
		tempPoint.setX(orginalpixmap.width());
	}
	if (tempPoint.y()>orginalpixmap.height())
	{
		tempPoint.setY(orginalpixmap.height());
	}
}

void QGraphicsSceneImageEnhance::selectShotPixmapMouseRelease()
{  
	QPixmap tempbg=backgroundpixmap;
	sceneUpdate(tempbg);
	/*if (endPoint.x()<0)
	{
		endPoint.setX(0);
	}
	if (endPoint.y()<0)
	{
		endPoint.setY(0);
	}
	if (endPoint.x()>orginalpixmap.width())
	{
		endPoint.setX(orginalpixmap.width());
	}
	if (endPoint.y()>orginalpixmap.height())
	{
		endPoint.setY(orginalpixmap.height());
	}*/
	pointBoundary(endPoint);
	selectShotPixmap();	 
}

void QGraphicsSceneImageEnhance::selectShotPixmapMouseMoveEvent()
{
    //加载有阴影的图像
	QPixmap tempbg=orginalpixmap;
	QPainter painter(&tempbg);
	painter.setPen(QPen(Qt::blue,4,Qt::SolidLine,Qt::FlatCap));
	painter.drawPixmap(tempbg.width(),tempbg.height(),tempbg);
	painter.fillRect(0,0,tempbg.width(),tempbg.height(),QColor(0,0,0,100));
	sceneUpdate(tempbg);  

	pointBoundary(endPoint);
	//if (endPoint.x()<0)
	//{
	//	endPoint.setX(0);
	//}
	//if (endPoint.y()<0)
	//{
	//	endPoint.setY(0);
	//}
	//if (endPoint.x()>orginalpixmap.width())
	//{
	//	endPoint.setX(orginalpixmap.width());
	//}
	//if (endPoint.y()>orginalpixmap.height())
	//{
	//	endPoint.setY(orginalpixmap.height());
	//}
	selectShotPixmap();
}

void QGraphicsSceneImageEnhance::sceneUpdate(QPixmap pixmap)
{
	this->update();
	this->clear();
	this->item=new QGraphicsPixmapItem();
	this->item->setPixmap(pixmap);
	this->setSceneRect(QRect(0,0,pixmap.width(),pixmap.height()));		//设定场景的边界，可以使得在中央
	this->addItem(this->item);
	
}

void QGraphicsSceneImageEnhance::selectShotPixmap()
{
	int widthx=qAbs(beginPoint.x()-endPoint.x());
	int heighty=qAbs(beginPoint.y()-endPoint.y());
	if (widthx!=0 && heighty!=0)
	{	 
		int x=beginPoint.x()<endPoint.x()?beginPoint.x():endPoint.x();
		int y=beginPoint.y()<endPoint.y()?beginPoint.y():endPoint.y();
		shotRect=QRect(x,y,widthx,heighty);
		QPixmap temp=orginalpixmap.copy(x,y,widthx,heighty);	
		shotpixmap=temp;
		//QGraphicsPixmapItem *
		itemTemp=new QGraphicsPixmapItem();
		itemTemp->setPixmap(temp);
		this->addItem(itemTemp);
		itemTemp->setPos(QPointF(x,y));
		itemTemp->acceptHoverEvents();
		itemTemp->acceptedMouseButtons();
		rectTemp=new QGraphicsRectItem(QRectF(0,0,widthx,heighty));
		rectTemp->setParentItem(itemTemp);
		//itemTemp->setParentItem(rectTemp);
		//rectTemp->setAcceptHoverEvents(true);
		//rectTemp->setAcceptedMouseButtons(false);
		QPen pen;
		pen.setWidth(3);
		pen.setColor(QColor(Qt::blue));
		rectTemp->setPen(pen);
		this->addItem(rectTemp);
		//rectTemp->setPos(QPointF(x,y));

		
	}
}

void draw8ControlPoint(QPainter &painter)
{

}


