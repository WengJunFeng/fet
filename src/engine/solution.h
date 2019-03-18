/*
File solution.h
*/

/***************************************************************************
                          solution.h  -  description
                             -------------------
    begin                : 2002
    copyright            : (C) 2002 by Lalescu Liviu
    email                : Please see https://lalescu.ro/liviu/ for details about contacting Liviu Lalescu (in particular, you can find here the e-mail address)
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Affero General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef SOLUTION_H
#define SOLUTION_H

#include "timetable_defs.h"

#include "matrix.h"

#include <QString>
#include <QList>

class Rules;

class TimeConstraint;
class SpaceConstraint;

struct GeneralConstraint {
	enum {TIME, SPACE} type;
	union {TimeConstraint* time; SpaceConstraint* space;} constraint;
};

/**
This class represents a solution (time and space allocation for the activities).
*/
class Solution{
	friend class Generate;
public:
	Solution();

	QList<double> conflictsWeightList;
	QList<QString> conflictsDescriptionList;
	double conflictsTotal;

	QStringList severeConflictList;
	QList<GeneralConstraint> conflictsConstraintList;

	int nPlacedActivities;

private:
	/**
	This array represents every activity's start time
	(time is a unified representation of hour and day,
	stored as an integer value). We have a special value here:
	UNALLOCATED_TIME, which is a large number.
	If changed, resetFitness() must be called.
	*/
	int times[MAX_ACTIVITIES];
	
	int rooms[MAX_ACTIVITIES];

public:
	/**
	Assignment method. We need to have access to the Rules instantiation
	to know the number of activities.
	*/
	void copy(const Rules& r, const Solution& c);

	/**
	Marks the starting time of all the activities as undefined
	(all activities are unallocated).
	*/
	void makeUnallocated(const Rules& r);

	/**
	  Clean fitness cached value.
	  It is needed to force recomputation when calling fitness().
	  It must be called every time the rules change.
	*/
	void resetFitness();

	/**
	ATTENTION: if the rules or the times array change,
	the user has to call resetFitness().
	<p>
	If conflictsString is not null, then this function will
	append at this string an explanation of the conflicts.
	*/
	double fitness(const Rules& r, QString* conflictsString=NULL);

	void getTeachersTimetable(const Rules& r, Matrix3D<int>& a, Matrix3D<QList<int> >& b) const;
	//return value is the number of conflicts, which must be 0

	void getSubgroupsTimetable(const Rules& r, Matrix3D<int>& a) const;
	//return value is the number of conflicts, which must be 0

	void getRoomsTimetable(const Rules& r, Matrix3D<int>& a) const;
	//return value is the number of conflicts, which must be 0

	int getSubgroupsMatrix(const Rules &r, const Matrix3D<int>** p_a) const;

	int getTeachersMatrix(const Rules &r, const Matrix3D<int>** p_a) const;

	int getRoomsMatrix(const Rules &r, const Matrix3D<int>** p_a) const;

	int time(int ai) const;
	int hour(int ai, const Rules &rules) const;
	int day(int ai, const Rules &rules) const;
	int room(int ai) const;

	void setTime(int ai, int time);
	void unsetTime(int ai);
	void setRoom(int ai, int room);
	void unspecifyRoom(int ai);
	void unallocateRoom(int ai);

	QList<int> getUnallocatedActivities(const Rules& rules) const;
	QList<int> getHomelessActivities(const Rules& rules) const;

	bool operator ==(const Solution& s2) const;

private:
	/**
	Fitness; it is calculated only at the initialization or
	at the modification.
	Important assumption: the rules have to ramain the same;
	otherwise the user has to reset this value to -1
	*/
	double _fitness;

	mutable bool teachersMatrixReady;
	mutable Matrix3D<int> cached_teachersMatrix;
	mutable int cached_teachersConflicts;

	mutable bool subgroupsMatrixReady;
	mutable Matrix3D<int> cached_subgroupsMatrix;
	mutable int cached_subgroupsConflicts;

	mutable bool roomsMatrixReady;
	mutable Matrix3D<int> cached_roomsMatrix;
	mutable int cached_roomsConflicts;
};

#endif
