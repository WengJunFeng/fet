/*
File lockunlock.h
*/

/***************************************************************************
                                FET
                          -------------------
   copyright            : (C) by Lalescu Liviu
    email                : Please see https://lalescu.ro/liviu/ for details about contacting Liviu Lalescu (in particular, you can find here the e-mail address)
 ***************************************************************************
                          lockunlock.h  -  description
                             -------------------
    begin                : Dec 2008
    copyright            : (C) by Liviu Lalescu (https://lalescu.ro/liviu/) and Volker Dirr (http://www.timetabling.de/)
 ***************************************************************************
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Affero General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef LOCKUNLOCK_H
#define LOCKUNLOCK_H

#include <QObject>

class CommunicationSpinBox: public QObject{
	Q_OBJECT
	
public:
	CommunicationSpinBox();
	
signals:
	void valueChanged();
	
public slots:
	void increaseValue();
};


class LockUnlock{
public:
	static void computeLockedUnlockedActivitiesTimeSpace();
	static void computeLockedUnlockedActivitiesOnlyTime();
	static void computeLockedUnlockedActivitiesOnlySpace();
	
	static void increaseCommunicationSpinBox();

	static QString getActivityLockTipString(int activityId);
	static QString getActivityLockDetailsString(int activityId);
};

#endif
