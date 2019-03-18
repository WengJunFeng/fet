/***************************************************************************
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Affero General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include <QtTest>

#include "timeconstraint.h"
#include "rules.h"
#include "solution.h"

#include "timetable.h"
Timetable gt; // Just to please generate_pre.cpp that yet require it. It must be not used in tests

class ConstraintStudentsMinContinuousGapInIntervalTest : public QObject
{
	Q_OBJECT

public:
	ConstraintStudentsMinContinuousGapInIntervalTest();

private Q_SLOTS:
	void OneStudentSet_CheckInvalidValues();
	void AllStudents_CheckInvalidValues();
	void OneStudentsSet_FitnessAcceptsNullPointer();
	void AllStudents_FitnessAcceptsNullPointer();
	void OneStudentsSet_CheckFitness();
	void OneStudentsGroup_CheckFitness();
	void AllStudents_CheckFitness();
	void OneStudentsSet_CheckFitness_EnoughGapButNotContinuous();
	void AllStudents_CheckFitness_EnoughGapButNotContinuous();
	// TODO check read/write xml
};

ConstraintStudentsMinContinuousGapInIntervalTest::ConstraintStudentsMinContinuousGapInIntervalTest()
{
}

void ConstraintStudentsMinContinuousGapInIntervalTest::OneStudentSet_CheckInvalidValues()
{
	Rules rules;
	rules.init();
	StudentsYear *sty = new StudentsYear();
	sty->name = "y1";
	rules.addYear(sty);
	rules.computeInternalStructure();

	ConstraintStudentsSetMinContinuousGapInInterval ctr(100.0, 2, "y1", 1, 5);

	ctr.weightPercentage = 120;
	ErrorCode result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted weight > 100%");

	ctr.weightPercentage = -2;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted weight < 0%");

	ctr.weightPercentage = 100;

	ctr.minGapDuration = -1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted min continuous gap < 0");

	ctr.minGapDuration = ctr.endHour-ctr.startHour+1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted min continuous gap > interval");

	ctr.minGapDuration = 2;

	ctr.startHour = -1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted start hour < 0");

	ctr.startHour = ctr.endHour+1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted start hour > end hour");

	ctr.startHour = 1;

	ctr.endHour = 0;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted start hour > end hour");

	ctr.endHour = -1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted end hour < 0");

	ctr.endHour = rules.nHoursPerDay + 1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted end hour > hours per day");

	ctr.endHour = rules.nHoursPerDay;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(!result, "Does not accept end-of-day as end hour");
}

void ConstraintStudentsMinContinuousGapInIntervalTest::AllStudents_CheckInvalidValues()
{
	Rules rules;
	rules.init();
	rules.computeInternalStructure();

	ConstraintStudentsMinContinuousGapInInterval ctr(100.0, 2, 1, 5);

	ctr.weightPercentage = 120;
	ErrorCode result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted weight > 100%");

	ctr.weightPercentage = -2;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted weight < 0%");

	ctr.weightPercentage = 100;

	ctr.minGapDuration = -1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted min continuous gap < 0");

	ctr.minGapDuration = ctr.endHour-ctr.startHour+1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted min continuous gap > interval");

	ctr.minGapDuration = 2;

	ctr.startHour = -1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted start hour < 0");

	ctr.startHour = ctr.endHour+1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted start hour > end hour");

	ctr.startHour = 1;

	ctr.endHour = 0;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted start hour > end hour");

	ctr.endHour = -1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted end hour < 0");

	ctr.endHour = rules.nHoursPerDay + 1;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(result, "Accepted end hour > hours per day");

	ctr.endHour = rules.nHoursPerDay;
	result = ctr.computeInternalStructure(rules);
	QVERIFY2(!result, "Does not accept end-of-day as end hour");
}

void ConstraintStudentsMinContinuousGapInIntervalTest::OneStudentsSet_FitnessAcceptsNullPointer()
{
	Rules rules;
	rules.init();
	StudentsYear *sty1 = new StudentsYear();
	sty1->name = "y1";
	bool ok = rules.addYearFast(sty1);
	QVERIFY2(ok, "Could not add students year");

	ConstraintStudentsSetMinContinuousGapInInterval *ctr = new ConstraintStudentsSetMinContinuousGapInInterval(100.0, 2, "y1", 1, 3);
	ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;
	c.setTime(0, 1);

	ctr->fitness(c, rules);
}

void ConstraintStudentsMinContinuousGapInIntervalTest::AllStudents_FitnessAcceptsNullPointer()
{
	Rules rules;
	rules.init();

	ConstraintStudentsMinContinuousGapInInterval *ctr = new ConstraintStudentsMinContinuousGapInInterval(100.0, 2, 1, 3);
	bool ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;
	c.setTime(0, 1);

	ctr->fitness(c, rules);
}

void ConstraintStudentsMinContinuousGapInIntervalTest::OneStudentsSet_CheckFitness()
{
	Rules rules;
	rules.init();
	StudentsYear *sty1 = new StudentsYear();
	sty1->name = "y1";
	rules.addYearFast(sty1);
	Subject *s1 = new Subject();
	s1->name = "subject1";
	rules.addSubjectFast(s1);

	QStringList tags, students;
	QStringList teachers;
	students << sty1->name;
	const int duration = 2;
	ErrorList errors = rules.addSimpleActivityFast(1, 1, teachers, "subject1", tags, students, duration, duration, true, false, 0, 0);
	QVERIFY2(!errors.hasError(), "Could not add activity");

	ConstraintStudentsSetMinContinuousGapInInterval *ctr = new ConstraintStudentsSetMinContinuousGapInInterval(100.0, 2, "y1", 2, 4);
	bool ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;

	double fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*0+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*1+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*2+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*3+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*4+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);


	c.setTime(0, rules.nDaysPerWeek*0+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*1+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*2+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*3+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*4+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);
}

void ConstraintStudentsMinContinuousGapInIntervalTest::OneStudentsGroup_CheckFitness()
{
	Rules rules;
	rules.init();
	StudentsYear *sty1 = new StudentsYear();
	sty1->name = "y1";
	rules.addYearFast(sty1);
	StudentsGroup *stg1 = new StudentsGroup();
	stg1->name = "y1 g1";
	rules.addGroupFast(sty1, stg1);
	Subject *s1 = new Subject();
	s1->name = "subject1";
	rules.addSubjectFast(s1);

	QStringList tags, students;
	QStringList teachers;
	students << sty1->name;
	const int duration = 2;
	ErrorList errors = rules.addSimpleActivityFast(1, 1, teachers, "subject1", tags, students, duration, duration, true, false, 0, 0);
	QVERIFY2(!errors.hasError(), "Could not add activity");

	ConstraintStudentsSetMinContinuousGapInInterval *ctr = new ConstraintStudentsSetMinContinuousGapInInterval(100.0, 2, "y1 g1", 2, 4);
	bool ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;

	double fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*0+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*1+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*2+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*3+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*4+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);


	c.setTime(0, rules.nDaysPerWeek*0+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*1+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*2+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*3+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);

	c.setTime(0, rules.nDaysPerWeek*4+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);
}

void ConstraintStudentsMinContinuousGapInIntervalTest::AllStudents_CheckFitness()
{
	Rules rules;
	rules.init();
	StudentsYear *sty1 = new StudentsYear();
	sty1->name = "y1";
	rules.addYearFast(sty1);
	sty1 = new StudentsYear();
	sty1->name = "y2";
	rules.addYearFast(sty1);
	Subject *s1 = new Subject();
	s1->name = "subject1";
	rules.addSubjectFast(s1);

	QStringList tags, students;
	QStringList teachers;
	students << "y1" << "y2";
	const int duration = 2;
	ErrorList errors = rules.addSimpleActivityFast(1, 1, teachers, "subject1", tags, students, duration, duration, true, false, 0, 0);
	QVERIFY2(!errors.hasError(), "Could not add activity");

	ConstraintStudentsMinContinuousGapInInterval *ctr = new ConstraintStudentsMinContinuousGapInInterval(100.0, 2, 2, 4);
	bool ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;

	double fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*0+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*1+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*2+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 4.0);

	c.setTime(0, rules.nDaysPerWeek*3+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*4+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);


	c.setTime(0, rules.nDaysPerWeek*0+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*1+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	ConflictInfo conflicts;
	c.setTime(0, rules.nDaysPerWeek*2+2);
	fitness = ctr->fitness(c, rules, &conflicts);
	QCOMPARE(fitness, 4.0);
	QCOMPARE(conflicts.weights.count(), 2);
	QCOMPARE(conflicts.weights[0], 2.0);

	c.setTime(0, rules.nDaysPerWeek*3+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 2.0);

	c.setTime(0, rules.nDaysPerWeek*4+2);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);
}

void ConstraintStudentsMinContinuousGapInIntervalTest::OneStudentsSet_CheckFitness_EnoughGapButNotContinuous()
{
	Rules rules;
	rules.init();
	StudentsYear *sty1 = new StudentsYear();
	sty1->name = "y1";
	rules.addYearFast(sty1);
	Subject *s1 = new Subject();
	s1->name = "subject1";
	rules.addSubjectFast(s1);

	QStringList tags, students;
	QStringList teachers;
	students << sty1->name;
	const int duration = 2;
	ErrorList errors = rules.addSimpleActivityFast(1, 1, teachers, "subject1", tags, students, duration, duration, true, false, 0, 0);
	QVERIFY2(!errors.hasError(), "Could not add activity");

	ConstraintStudentsSetMinContinuousGapInInterval *ctr = new ConstraintStudentsSetMinContinuousGapInInterval(100.0, 2, "y1", 2, 6);
	bool ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;

	double fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 0.0);

	c.setTime(0, rules.nDaysPerWeek*3+0);
	fitness = ctr->fitness(c, rules);
	QCOMPARE(fitness, 1.0);
}

void ConstraintStudentsMinContinuousGapInIntervalTest::AllStudents_CheckFitness_EnoughGapButNotContinuous()
{
	Rules rules;
	rules.init();
	StudentsYear *sty1 = new StudentsYear();
	sty1->name = "y1";
	rules.addYearFast(sty1);
	sty1 = new StudentsYear();
	sty1->name = "y2";
	rules.addYearFast(sty1);
	Subject *s1 = new Subject();
	s1->name = "subject1";
	rules.addSubjectFast(s1);

	QStringList tags, students;
	QStringList teachers;
	students << "y1" << "y2";
	const int duration = 2;
	ErrorList errors = rules.addSimpleActivityFast(1, 1, teachers, "subject1", tags, students, duration, duration, true, false, 0, 0);
	QVERIFY2(!errors.hasError(), "Could not add activity");

	ConstraintStudentsMinContinuousGapInInterval *ctr = new ConstraintStudentsMinContinuousGapInInterval(100.0, 2, 2, 6);
	bool ok = rules.addTimeConstraint(ctr);
	QVERIFY2(ok, "Could not add constraint");

	rules.computeInternalStructure();

	Solution c;

	ConflictInfo conflicts;
	double fitness = ctr->fitness(c, rules, &conflicts);
	QCOMPARE(fitness, 0.0);
	QCOMPARE(conflicts.weights.count(), 0);

	conflicts.clear();
	c.setTime(0, rules.nDaysPerWeek*3+0);
	fitness = ctr->fitness(c, rules, &conflicts);
	QCOMPARE(fitness, 2.0);
	QCOMPARE(conflicts.weights.count(), 2);
	QCOMPARE(conflicts.weights[0], 1.0);
	QCOMPARE(conflicts.descriptions.count(), 2);
}

QTEST_APPLESS_MAIN(ConstraintStudentsMinContinuousGapInIntervalTest)

#include "tst_constraintstudentsmincontinuousgapinintervaltest.moc"
