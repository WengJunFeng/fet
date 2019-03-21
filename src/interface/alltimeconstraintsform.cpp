/***************************************************************************
                          alltimeconstraintsform.cpp  -  description
                             -------------------
    begin                : Feb 10, 2005
    copyright            : (C) 2005 by Lalescu Liviu
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

#include "fetguisettings.h"
#include "centerwidgetonscreen.h"

#include "longtextmessagebox.h"

#include "alltimeconstraintsform.h"

#include "modifyconstraintbreaktimesform.h"
#include "modifyconstraintbasiccompulsorytimeform.h"

#include "modifyconstraintactivitypreferredtimeslotsform.h"
#include "modifyconstraintactivitypreferredstartingtimesform.h"
#include "modifyconstrainttwoactivitiesconsecutiveform.h"
#include "modifyconstrainttwoactivitiesgroupedform.h"
#include "modifyconstraintthreeactivitiesgroupedform.h"
#include "modifyconstrainttwoactivitiesorderedform.h"
#include "modifyconstrainttwoactivitiesorderedifsamedayform.h"

#include "modifyconstraintactivitiespreferredtimeslotsform.h"
#include "modifyconstraintactivitiespreferredstartingtimesform.h"

#include "modifyconstraintsubactivitiespreferredtimeslotsform.h"
#include "modifyconstraintsubactivitiespreferredstartingtimesform.h"

#include "modifyconstraintactivitiessamestartingtimeform.h"
#include "modifyconstraintactivitiessamestartinghourform.h"
#include "modifyconstraintactivitiessamestartingdayform.h"
#include "modifyconstraintactivitypreferredstartingtimeform.h"
#include "modifyconstraintactivitiesnotoverlappingform.h"
#include "modifyconstraintmindaysbetweenactivitiesform.h"
#include "modifyconstraintmaxdaysbetweenactivitiesform.h"
#include "modifyconstraintmingapsbetweenactivitiesform.h"
#include "modifyconstraintactivityendsstudentsdayform.h"

#include "modifyconstraintactivitiesendstudentsdayform.h"

#include "modifyconstraintteachernotavailabletimesform.h"
#include "modifyconstraintteachersmaxgapsperweekform.h"
#include "modifyconstraintteachermaxgapsperweekform.h"
#include "modifyconstraintteachersmaxgapsperdayform.h"
#include "modifyconstraintteachermaxgapsperdayform.h"
#include "modifyconstraintteachermaxdaysperweekform.h"
#include "modifyconstraintteachersmaxdaysperweekform.h"
#include "modifyconstraintteachersmaxhoursdailyform.h"
#include "modifyconstraintteachermaxhoursdailyform.h"
#include "modifyconstraintteachersmaxhourscontinuouslyform.h"
#include "modifyconstraintteachermaxhourscontinuouslyform.h"
#include "modifyconstraintteachersminhoursdailyform.h"
#include "modifyconstraintteacherminhoursdailyform.h"

#include "modifyconstraintteachermindaysperweekform.h"
#include "modifyconstraintteachersmindaysperweekform.h"

#include "modifyconstraintteachersactivitytagmaxhourscontinuouslyform.h"
#include "modifyconstraintteacheractivitytagmaxhourscontinuouslyform.h"

#include "modifyconstraintteachersactivitytagmaxhoursdailyform.h"
#include "modifyconstraintteacheractivitytagmaxhoursdailyform.h"

#include "modifyconstraintstudentssetnotavailabletimesform.h"
#include "modifyconstraintstudentssetmaxgapsperweekform.h"
#include "modifyconstraintstudentsmaxgapsperweekform.h"

#include "modifyconstraintstudentssetmaxgapsperdayform.h"
#include "modifyconstraintstudentsmaxgapsperdayform.h"

#include "modifyconstraintstudentsearlymaxbeginningsatsecondhourform.h"
#include "modifyconstraintstudentssetearlymaxbeginningsatsecondhourform.h"
#include "modifyconstraintstudentssetmaxhoursdailyform.h"
#include "modifyconstraintstudentsmaxhoursdailyform.h"
#include "modifyconstraintstudentssetmaxhourscontinuouslyform.h"
#include "modifyconstraintstudentsmaxhourscontinuouslyform.h"
#include "modifyconstraintstudentssetminhoursdailyform.h"
#include "modifyconstraintstudentsminhoursdailyform.h"

#include "modifyconstraintstudentssetactivitytagmaxhourscontinuouslyform.h"
#include "modifyconstraintstudentsactivitytagmaxhourscontinuouslyform.h"

#include "modifyconstraintstudentssetactivitytagmaxhoursdailyform.h"
#include "modifyconstraintstudentsactivitytagmaxhoursdailyform.h"

#include "modifyconstraintteacherintervalmaxdaysperweekform.h"
#include "modifyconstraintteachersintervalmaxdaysperweekform.h"

#include "modifyconstraintstudentssetintervalmaxdaysperweekform.h"
#include "modifyconstraintstudentsintervalmaxdaysperweekform.h"

#include "modifyconstraintactivitiesoccupymaxtimeslotsfromselectionform.h"
#include "modifyconstraintactivitiesmaxsimultaneousinselectedtimeslotsform.h"

#include "modifyconstraintstudentssetmaxdaysperweekform.h"
#include "modifyconstraintstudentsmaxdaysperweekform.h"

//2017-02-07
#include "modifyconstraintteachermaxspanperdayform.h"
#include "modifyconstraintteachersmaxspanperdayform.h"
#include "modifyconstraintstudentssetmaxspanperdayform.h"
#include "modifyconstraintstudentsmaxspanperdayform.h"
#include "modifyconstraintteacherminrestinghoursform.h"
#include "modifyconstraintteachersminrestinghoursform.h"
#include "modifyconstraintstudentssetminrestinghoursform.h"
#include "modifyconstraintstudentsminrestinghoursform.h"

#include "addconstraintteachersmincontinuousgapinintervalform.h"
#include "addconstraintstudentsmincontinuousgapinintervalform.h"

#include "editcommentsform.h"

#include "lockunlock.h"

#include "advancedfilterform.h"

#include <QMessageBox>

#include <QPlainTextEdit>

#include <QRegExp>

#include <QListWidget>
#include <QScrollBar>
#include <QAbstractItemView>

#include <QSplitter>
#include <QSettings>
#include <QObject>
#include <QMetaObject>

#include <QBrush>
#include <QPalette>

#include <QtAlgorithms>

#include <algorithm>
using namespace std;

const int DESCRIPTION=0;
//const int DETDESCRIPTION=1;

const int CONTAINS=0;
const int DOESNOTCONTAIN=1;
const int REGEXP=2;
const int NOTREGEXP=3;

AllTimeConstraintsForm::AllTimeConstraintsForm(QWidget* parent): QDialog(parent)
{
	setupUi(this);

	filterCheckBox->setChecked(false);
	sortedCheckBox->setChecked(false);
	
	currentConstraintTextEdit->setReadOnly(true);
	
	modifyConstraintPushButton->setDefault(true);
	
	constraintsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(constraintsListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(constraintChanged()));
	connect(closePushButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(removeConstraintPushButton, SIGNAL(clicked()), this, SLOT(removeConstraint()));
	connect(modifyConstraintPushButton, SIGNAL(clicked()), this, SLOT(modifyConstraint()));
	connect(constraintsListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyConstraint()));
	connect(filterCheckBox, SIGNAL(toggled(bool)), this, SLOT(filter(bool)));

	connect(moveTimeConstraintUpPushButton, SIGNAL(clicked()), this, SLOT(moveTimeConstraintUp()));
	connect(moveTimeConstraintDownPushButton, SIGNAL(clicked()), this, SLOT(moveTimeConstraintDown()));

	connect(sortedCheckBox, SIGNAL(toggled(bool)), this, SLOT(sortedChanged(bool)));
	connect(activatePushButton, SIGNAL(clicked()), this, SLOT(activateConstraint()));
	connect(deactivatePushButton, SIGNAL(clicked()), this, SLOT(deactivateConstraint()));
	//connect(sortByCommentsPushButton, SIGNAL(clicked()), this, SLOT(sortConstraintsByComments()));
	connect(commentsPushButton, SIGNAL(clicked()), this, SLOT(constraintComments()));

	centerWidgetOnScreen(this);
	restoreFETDialogGeometry(this);
	//restore splitter state
	QSettings settings;
	if(settings.contains(this->metaObject()->className()+QString("/splitter-state")))
		splitter->restoreState(settings.value(this->metaObject()->className()+QString("/splitter-state")).toByteArray());
		
	QString settingsName="AllTimeConstraintsAdvancedFilterForm";
	
	all=settings.value(settingsName+"/all-conditions", "true").toBool();
	
	descrDetDescr.clear();
	int n=settings.value(settingsName+"/number-of-descriptions", "1").toInt();
	for(int i=0; i<n; i++)
		descrDetDescr.append(settings.value(settingsName+"/description/"+CustomFETString::number(i+1), CustomFETString::number(DESCRIPTION)).toInt());
	
	contains.clear();
	n=settings.value(settingsName+"/number-of-contains", "1").toInt();
	for(int i=0; i<n; i++)
		contains.append(settings.value(settingsName+"/contains/"+CustomFETString::number(i+1), CustomFETString::number(CONTAINS)).toInt());
	
	text.clear();
	n=settings.value(settingsName+"/number-of-texts", "1").toInt();
	for(int i=0; i<n; i++)
		text.append(settings.value(settingsName+"/text/"+CustomFETString::number(i+1), QString("")).toString());

	caseSensitive=settings.value(settingsName+"/case-sensitive", "false").toBool();
	
	useFilter=false;
	
	assert(filterCheckBox->isChecked()==false);
	assert(sortedCheckBox->isChecked()==false);
	
	filterChanged();
}

AllTimeConstraintsForm::~AllTimeConstraintsForm()
{
	saveFETDialogGeometry(this);
	//save splitter state
	QSettings settings;
	settings.setValue(this->metaObject()->className()+QString("/splitter-state"), splitter->saveState());

	QString settingsName="AllTimeConstraintsAdvancedFilterForm";
	
	settings.setValue(settingsName+"/all-conditions", all);
	
	settings.setValue(settingsName+"/number-of-descriptions", descrDetDescr.count());
	settings.remove(settingsName+"/description");
	for(int i=0; i<descrDetDescr.count(); i++)
		settings.setValue(settingsName+"/description/"+CustomFETString::number(i+1), descrDetDescr.at(i));
	
	settings.setValue(settingsName+"/number-of-contains", contains.count());
	settings.remove(settingsName+"/contains");
	for(int i=0; i<contains.count(); i++)
		settings.setValue(settingsName+"/contains/"+CustomFETString::number(i+1), contains.at(i));
	
	settings.setValue(settingsName+"/number-of-texts", text.count());
	settings.remove(settingsName+"/text");
	for(int i=0; i<text.count(); i++)
		settings.setValue(settingsName+"/text/"+CustomFETString::number(i+1), text.at(i));
	
	settings.setValue(settingsName+"/case-sensitive", caseSensitive);
}

bool AllTimeConstraintsForm::filterOk(TimeConstraint* ctr)
{
	if(!useFilter)
		return true;

	assert(descrDetDescr.count()==contains.count());
	assert(contains.count()==text.count());
	
	Qt::CaseSensitivity csens=Qt::CaseSensitive;
	if(!caseSensitive)
		csens=Qt::CaseInsensitive;
	
	QList<bool> okPartial;
	
	for(int i=0; i<descrDetDescr.count(); i++){
		QString s;
		if(descrDetDescr.at(i)==DESCRIPTION)
			s=ctr->getDescription(gt.rules);
		else
			s=ctr->getDetailedDescription(gt.rules);
			
		QString t=text.at(i);
		if(contains.at(i)==CONTAINS){
			okPartial.append(s.contains(t, csens));
		}
		else if(contains.at(i)==DOESNOTCONTAIN){
			okPartial.append(!(s.contains(t, csens)));
		}
		else if(contains.at(i)==REGEXP){
			QRegExp regExp(t);
			regExp.setCaseSensitivity(csens);
			okPartial.append(regExp.indexIn(s)>=0);
		}
		else if(contains.at(i)==NOTREGEXP){
			QRegExp regExp(t);
			regExp.setCaseSensitivity(csens);
			okPartial.append(regExp.indexIn(s)<0);
		}
		else
			assert(0);
	}
	
	if(all){
		bool ok=true;
		for(bool b : qAsConst(okPartial))
			ok = ok && b;
			
		return ok;
	}
	else{ //any
		bool ok=false;
		for(bool b : qAsConst(okPartial))
			ok = ok || b;
			
		return ok;
	}
}

void AllTimeConstraintsForm::moveTimeConstraintUp()
{
	if(filterCheckBox->isChecked()){
		QMessageBox::information(this, tr("FET information"), tr("To move a time constraint, the 'Filter' check box must not be checked."));
		return;
	}
	if(sortedCheckBox->isChecked()){
		QMessageBox::information(this, tr("FET information"), tr("To move a time constraint, the 'Sorted' check box must not be checked."));
		return;
	}
	
	if(constraintsListWidget->count()<=1)
		return;
	int i=constraintsListWidget->currentRow();
	if(i<0 || i>=constraintsListWidget->count())
		return;
	if(i==0)
		return;
		
	QString s1=constraintsListWidget->item(i)->text();
	QString s2=constraintsListWidget->item(i-1)->text();
	
	assert(gt.rules.timeConstraintsList.count()==visibleTimeConstraintsList.count());
	TimeConstraint* tc1=gt.rules.timeConstraintsList.at(i);
	assert(tc1==visibleTimeConstraintsList.at(i));
	TimeConstraint* tc2=gt.rules.timeConstraintsList.at(i-1);
	assert(tc2==visibleTimeConstraintsList.at(i-1));
	
	gt.rules.internalStructureComputed=false;
	gt.rules.setModified(true);
	
	constraintsListWidget->item(i)->setText(s2);
	constraintsListWidget->item(i-1)->setText(s1);
	
	gt.rules.timeConstraintsList.swap(i, i-1);
	
	visibleTimeConstraintsList[i]=tc2;
	visibleTimeConstraintsList[i-1]=tc1;
	
	if(USE_GUI_COLORS){
		if(tc2->active)
			constraintsListWidget->item(i)->setBackground(constraintsListWidget->palette().base());
		else
			constraintsListWidget->item(i)->setBackground(constraintsListWidget->palette().alternateBase());

		if(tc1->active)
			constraintsListWidget->item(i-1)->setBackground(constraintsListWidget->palette().base());
		else
			constraintsListWidget->item(i-1)->setBackground(constraintsListWidget->palette().alternateBase());
	}

	constraintsListWidget->setCurrentRow(i-1);
}

void AllTimeConstraintsForm::moveTimeConstraintDown()
{
	if(filterCheckBox->isChecked()){
		QMessageBox::information(this, tr("FET information"), tr("To move a time constraint, the 'Filter' check box must not be checked."));
		return;
	}
	if(sortedCheckBox->isChecked()){
		QMessageBox::information(this, tr("FET information"), tr("To move a time constraint, the 'Sorted' check box must not be checked."));
		return;
	}
	
	if(constraintsListWidget->count()<=1)
		return;
	int i=constraintsListWidget->currentRow();
	if(i<0 || i>=constraintsListWidget->count())
		return;
	if(i==constraintsListWidget->count()-1)
		return;
		
	QString s1=constraintsListWidget->item(i)->text();
	QString s2=constraintsListWidget->item(i+1)->text();
	
	assert(gt.rules.timeConstraintsList.count()==visibleTimeConstraintsList.count());
	TimeConstraint* tc1=gt.rules.timeConstraintsList.at(i);
	assert(tc1==visibleTimeConstraintsList.at(i));
	TimeConstraint* tc2=gt.rules.timeConstraintsList.at(i+1);
	assert(tc2==visibleTimeConstraintsList.at(i+1));
	
	gt.rules.internalStructureComputed=false;
	gt.rules.setModified(true);
	
	constraintsListWidget->item(i)->setText(s2);
	constraintsListWidget->item(i+1)->setText(s1);
	
	gt.rules.timeConstraintsList.swap(i, i+1);
	
	visibleTimeConstraintsList[i]=tc2;
	visibleTimeConstraintsList[i+1]=tc1;
	
	if(USE_GUI_COLORS){
		if(tc2->active)
			constraintsListWidget->item(i)->setBackground(constraintsListWidget->palette().base());
		else
			constraintsListWidget->item(i)->setBackground(constraintsListWidget->palette().alternateBase());

		if(tc1->active)
			constraintsListWidget->item(i+1)->setBackground(constraintsListWidget->palette().base());
		else
			constraintsListWidget->item(i+1)->setBackground(constraintsListWidget->palette().alternateBase());
	}

	constraintsListWidget->setCurrentRow(i+1);
}

void AllTimeConstraintsForm::sortedChanged(bool checked)
{
	Q_UNUSED(checked);

	filterChanged();
}

static bool timeConstraintsAscendingByDescription(const TimeConstraint* t1, const TimeConstraint* t2)
{
//	return t1->getDescription(gt.rules) < t2->getDescription(gt.rules);
	//by rodolforg
	return t1->getDescription(gt.rules).localeAwareCompare(t2->getDescription(gt.rules))<0;
}

void AllTimeConstraintsForm::filterChanged()
{
	visibleTimeConstraintsList.clear();
	constraintsListWidget->clear();
	int n_active=0;
	for(TimeConstraint* ctr : qAsConst(gt.rules.timeConstraintsList))
		if(filterOk(ctr))
			visibleTimeConstraintsList.append(ctr);
		
	if(sortedCheckBox->isChecked())
		std::stable_sort(visibleTimeConstraintsList.begin(), visibleTimeConstraintsList.end(), timeConstraintsAscendingByDescription);

	for(TimeConstraint* ctr : qAsConst(visibleTimeConstraintsList)){
		assert(filterOk(ctr));
		constraintsListWidget->addItem(ctr->getDescription(gt.rules));
			
		if(USE_GUI_COLORS && !ctr->active)
			constraintsListWidget->item(constraintsListWidget->count()-1)->setBackground(constraintsListWidget->palette().alternateBase());
		
		if(ctr->active)
			n_active++;
	}
	
	if(constraintsListWidget->count()<=0)
		currentConstraintTextEdit->setPlainText("");
	else
		constraintsListWidget->setCurrentRow(0);
	
	constraintsTextLabel->setText(tr("%1 / %2 time constraints",
	 "%1 represents the number of visible active time constraints, %2 represents the total number of visible time constraints")
	 .arg(n_active).arg(visibleTimeConstraintsList.count()));
}

void AllTimeConstraintsForm::constraintChanged()
{
	int index=constraintsListWidget->currentRow();

	if(index<0)
		return;
		
	assert(index<visibleTimeConstraintsList.count());
	TimeConstraint* ctr=visibleTimeConstraintsList.at(index);
	assert(ctr!=NULL);
	QString s=ctr->getDetailedDescription(gt.rules);
	currentConstraintTextEdit->setPlainText(s);
}

void AllTimeConstraintsForm::modifyConstraint()
{
	int i=constraintsListWidget->currentRow();
	if(i<0){
		QMessageBox::information(this, tr("FET information"), tr("Invalid selected constraint"));
	
		constraintsListWidget->setFocus();

		return;
	}
	
	int valv=constraintsListWidget->verticalScrollBar()->value();
	int valh=constraintsListWidget->horizontalScrollBar()->value();
	
	assert(i<visibleTimeConstraintsList.count());
	TimeConstraint* ctr=visibleTimeConstraintsList.at(i);
	
	launchModifyConstraintDialog(this, ctr);

	filterChanged();

	constraintsListWidget->verticalScrollBar()->setValue(valv);
	constraintsListWidget->horizontalScrollBar()->setValue(valh);

	if(i>=constraintsListWidget->count())
		i=constraintsListWidget->count()-1;

	if(i>=0)
		constraintsListWidget->setCurrentRow(i);

	constraintsListWidget->setFocus();
}

bool AllTimeConstraintsForm::launchModifyConstraintDialog(QWidget* parent, TimeConstraint* ctr)
{
	//1
	if(ctr->type==CONSTRAINT_BASIC_COMPULSORY_TIME){
		ModifyConstraintBasicCompulsoryTimeForm form(parent, (ConstraintBasicCompulsoryTime*)ctr);
		form.exec();
	}
	//2
	else if(ctr->type==CONSTRAINT_TWO_ACTIVITIES_CONSECUTIVE){
		ModifyConstraintTwoActivitiesConsecutiveForm form(parent, (ConstraintTwoActivitiesConsecutive*)ctr);
		form.exec();
	}
	//3
	else if(ctr->type==CONSTRAINT_TWO_ACTIVITIES_ORDERED){
		ModifyConstraintTwoActivitiesOrderedForm form(parent, (ConstraintTwoActivitiesOrdered*)ctr);
		form.exec();
	}
	//4
	else if(ctr->type==CONSTRAINT_ACTIVITY_PREFERRED_TIME_SLOTS){
		ModifyConstraintActivityPreferredTimeSlotsForm form(parent, (ConstraintActivityPreferredTimeSlots*)ctr);
		form.exec();
	}
	//5
	else if(ctr->type==CONSTRAINT_ACTIVITY_PREFERRED_STARTING_TIMES){
		ModifyConstraintActivityPreferredStartingTimesForm form(parent, (ConstraintActivityPreferredStartingTimes*)ctr);
		form.exec();
	}
	//6
	else if(ctr->type==CONSTRAINT_ACTIVITIES_PREFERRED_TIME_SLOTS){
		ModifyConstraintActivitiesPreferredTimeSlotsForm form(parent, (ConstraintActivitiesPreferredTimeSlots*)ctr);
		form.exec();
	}
	//7
	else if(ctr->type==CONSTRAINT_ACTIVITIES_PREFERRED_STARTING_TIMES){
		ModifyConstraintActivitiesPreferredStartingTimesForm form(parent, (ConstraintActivitiesPreferredStartingTimes*)ctr);
		form.exec();
	}
	//8
	else if(ctr->type==CONSTRAINT_SUBACTIVITIES_PREFERRED_TIME_SLOTS){
		ModifyConstraintSubactivitiesPreferredTimeSlotsForm form(parent, (ConstraintSubactivitiesPreferredTimeSlots*)ctr);
		form.exec();
	}
	//9
	else if(ctr->type==CONSTRAINT_SUBACTIVITIES_PREFERRED_STARTING_TIMES){
		ModifyConstraintSubactivitiesPreferredStartingTimesForm form(parent, (ConstraintSubactivitiesPreferredStartingTimes*)ctr);
		form.exec();
	}
	//10
	else if(ctr->type==CONSTRAINT_ACTIVITIES_SAME_STARTING_TIME){
		ModifyConstraintActivitiesSameStartingTimeForm form(parent, (ConstraintActivitiesSameStartingTime*)ctr);
		form.exec();
	}
	//11
	else if(ctr->type==CONSTRAINT_ACTIVITIES_SAME_STARTING_HOUR){
		ModifyConstraintActivitiesSameStartingHourForm form(parent, (ConstraintActivitiesSameStartingHour*)ctr);
		form.exec();
	}
	//12
	else if(ctr->type==CONSTRAINT_ACTIVITIES_SAME_STARTING_DAY){
		ModifyConstraintActivitiesSameStartingDayForm form(parent, (ConstraintActivitiesSameStartingDay*)ctr);
		form.exec();
	}
	//13
	else if(ctr->type==CONSTRAINT_TEACHER_NOT_AVAILABLE_TIMES){
		ModifyConstraintTeacherNotAvailableTimesForm form(parent, (ConstraintTeacherNotAvailableTimes*)ctr);
		form.exec();
	}
	//14
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_NOT_AVAILABLE_TIMES){
		ModifyConstraintStudentsSetNotAvailableTimesForm form(parent, (ConstraintStudentsSetNotAvailableTimes*)ctr);
		form.exec();
	}
	//15
	else if(ctr->type==CONSTRAINT_BREAK_TIMES){
		ModifyConstraintBreakTimesForm form(parent, (ConstraintBreakTimes*)ctr);
		form.exec();
	}
	//16
	else if(ctr->type==CONSTRAINT_TEACHER_MAX_DAYS_PER_WEEK){
		ModifyConstraintTeacherMaxDaysPerWeekForm form(parent, (ConstraintTeacherMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//17
	else if(ctr->type==CONSTRAINT_TEACHERS_MAX_HOURS_DAILY){
		ModifyConstraintTeachersMaxHoursDailyForm form(parent, (ConstraintTeachersMaxHoursDaily*)ctr);
		form.exec();
	}
	//18
	else if(ctr->type==CONSTRAINT_TEACHER_MAX_HOURS_DAILY){
		ModifyConstraintTeacherMaxHoursDailyForm form(parent, (ConstraintTeacherMaxHoursDaily*)ctr);
		form.exec();
	}
	//19
	else if(ctr->type==CONSTRAINT_TEACHERS_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintTeachersMaxHoursContinuouslyForm form(parent, (ConstraintTeachersMaxHoursContinuously*)ctr);
		form.exec();
	}
	//20
	else if(ctr->type==CONSTRAINT_TEACHER_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintTeacherMaxHoursContinuouslyForm form(parent, (ConstraintTeacherMaxHoursContinuously*)ctr);
		form.exec();
	}
	//21
	else if(ctr->type==CONSTRAINT_TEACHERS_MIN_HOURS_DAILY){
		ModifyConstraintTeachersMinHoursDailyForm form(parent, (ConstraintTeachersMinHoursDaily*)ctr);
		form.exec();
	}
	//22
	else if(ctr->type==CONSTRAINT_TEACHER_MIN_HOURS_DAILY){
		ModifyConstraintTeacherMinHoursDailyForm form(parent, (ConstraintTeacherMinHoursDaily*)ctr);
		form.exec();
	}
	//23
	else if(ctr->type==CONSTRAINT_TEACHERS_MAX_GAPS_PER_WEEK){
		ModifyConstraintTeachersMaxGapsPerWeekForm form(parent, (ConstraintTeachersMaxGapsPerWeek*)ctr);
		form.exec();
	}
	//24
	else if(ctr->type==CONSTRAINT_TEACHER_MAX_GAPS_PER_WEEK){
		ModifyConstraintTeacherMaxGapsPerWeekForm form(parent, (ConstraintTeacherMaxGapsPerWeek*)ctr);
		form.exec();
	}
	//25
	else if(ctr->type==CONSTRAINT_TEACHERS_MAX_GAPS_PER_DAY){
		ModifyConstraintTeachersMaxGapsPerDayForm form(parent, (ConstraintTeachersMaxGapsPerDay*)ctr);
		form.exec();
	}
	//26
	else if(ctr->type==CONSTRAINT_TEACHER_MAX_GAPS_PER_DAY){
		ModifyConstraintTeacherMaxGapsPerDayForm form(parent, (ConstraintTeacherMaxGapsPerDay*)ctr);
		form.exec();
	}
	//27
	else if(ctr->type==CONSTRAINT_ACTIVITY_PREFERRED_STARTING_TIME){
		ModifyConstraintActivityPreferredStartingTimeForm form(parent, (ConstraintActivityPreferredStartingTime*)ctr);
		form.exec();
	}
	//28
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MAX_GAPS_PER_WEEK){
		ModifyConstraintStudentsSetMaxGapsPerWeekForm form(parent, (ConstraintStudentsSetMaxGapsPerWeek*)ctr);
		form.exec();
	}
	//29
	else if(ctr->type==CONSTRAINT_STUDENTS_MAX_GAPS_PER_WEEK){
		ModifyConstraintStudentsMaxGapsPerWeekForm form(parent, (ConstraintStudentsMaxGapsPerWeek*)ctr);
		form.exec();
	}
	//30
	else if(ctr->type==CONSTRAINT_STUDENTS_EARLY_MAX_BEGINNINGS_AT_SECOND_HOUR){
		ModifyConstraintStudentsEarlyMaxBeginningsAtSecondHourForm form(parent, (ConstraintStudentsEarlyMaxBeginningsAtSecondHour*)ctr);
		form.exec();
	}
	//31
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_EARLY_MAX_BEGINNINGS_AT_SECOND_HOUR){
		ModifyConstraintStudentsSetEarlyMaxBeginningsAtSecondHourForm form(parent, (ConstraintStudentsSetEarlyMaxBeginningsAtSecondHour*)ctr);
		form.exec();
	}
	//32
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MAX_HOURS_DAILY){
		ModifyConstraintStudentsSetMaxHoursDailyForm form(parent, (ConstraintStudentsSetMaxHoursDaily*)ctr);
		form.exec();
	}
	//33
	else if(ctr->type==CONSTRAINT_STUDENTS_MAX_HOURS_DAILY){
		ModifyConstraintStudentsMaxHoursDailyForm form(parent, (ConstraintStudentsMaxHoursDaily*)ctr);
		form.exec();
	}
	//34
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintStudentsSetMaxHoursContinuouslyForm form(parent, (ConstraintStudentsSetMaxHoursContinuously*)ctr);
		form.exec();
	}
	//35
	else if(ctr->type==CONSTRAINT_STUDENTS_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintStudentsMaxHoursContinuouslyForm form(parent, (ConstraintStudentsMaxHoursContinuously*)ctr);
		form.exec();
	}
	//36
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MIN_HOURS_DAILY){
		ModifyConstraintStudentsSetMinHoursDailyForm form(parent, (ConstraintStudentsSetMinHoursDaily*)ctr);
		form.exec();
	}
	//37
	else if(ctr->type==CONSTRAINT_STUDENTS_MIN_HOURS_DAILY){
		ModifyConstraintStudentsMinHoursDailyForm form(parent, (ConstraintStudentsMinHoursDaily*)ctr);
		form.exec();
	}
	//38
	else if(ctr->type==CONSTRAINT_ACTIVITIES_NOT_OVERLAPPING){
		ModifyConstraintActivitiesNotOverlappingForm form(parent, (ConstraintActivitiesNotOverlapping*)ctr);
		form.exec();
	}
	//39
	else if(ctr->type==CONSTRAINT_MIN_DAYS_BETWEEN_ACTIVITIES){
		ModifyConstraintMinDaysBetweenActivitiesForm form(parent, (ConstraintMinDaysBetweenActivities*)ctr);
		form.exec();
	}
	//40
	else if(ctr->type==CONSTRAINT_MIN_GAPS_BETWEEN_ACTIVITIES){
		ModifyConstraintMinGapsBetweenActivitiesForm form(parent, (ConstraintMinGapsBetweenActivities*)ctr);
		form.exec();
	}
	//41
	else if(ctr->type==CONSTRAINT_ACTIVITY_ENDS_STUDENTS_DAY){
		ModifyConstraintActivityEndsStudentsDayForm form(parent, (ConstraintActivityEndsStudentsDay*)ctr);
		form.exec();
	}
	//42
	else if(ctr->type==CONSTRAINT_TEACHER_INTERVAL_MAX_DAYS_PER_WEEK){
		ModifyConstraintTeacherIntervalMaxDaysPerWeekForm form(parent, (ConstraintTeacherIntervalMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//43
	else if(ctr->type==CONSTRAINT_TEACHERS_INTERVAL_MAX_DAYS_PER_WEEK){
		ModifyConstraintTeachersIntervalMaxDaysPerWeekForm form(parent, (ConstraintTeachersIntervalMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//44
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_INTERVAL_MAX_DAYS_PER_WEEK){
		ModifyConstraintStudentsSetIntervalMaxDaysPerWeekForm form(parent, (ConstraintStudentsSetIntervalMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//45
	else if(ctr->type==CONSTRAINT_STUDENTS_INTERVAL_MAX_DAYS_PER_WEEK){
		ModifyConstraintStudentsIntervalMaxDaysPerWeekForm form(parent, (ConstraintStudentsIntervalMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//46
	else if(ctr->type==CONSTRAINT_ACTIVITIES_END_STUDENTS_DAY){
		ModifyConstraintActivitiesEndStudentsDayForm form(parent, (ConstraintActivitiesEndStudentsDay*)ctr);
		form.exec();
	}
	//47
	else if(ctr->type==CONSTRAINT_TWO_ACTIVITIES_GROUPED){
		ModifyConstraintTwoActivitiesGroupedForm form(parent, (ConstraintTwoActivitiesGrouped*)ctr);
		form.exec();
	}
	//48
	else if(ctr->type==CONSTRAINT_TEACHERS_ACTIVITY_TAG_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintTeachersActivityTagMaxHoursContinuouslyForm form(parent, (ConstraintTeachersActivityTagMaxHoursContinuously*)ctr);
		form.exec();
	}
	//49
	else if(ctr->type==CONSTRAINT_TEACHER_ACTIVITY_TAG_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintTeacherActivityTagMaxHoursContinuouslyForm form(parent, (ConstraintTeacherActivityTagMaxHoursContinuously*)ctr);
		form.exec();
	}
	//50
	else if(ctr->type==CONSTRAINT_STUDENTS_ACTIVITY_TAG_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintStudentsActivityTagMaxHoursContinuouslyForm form(parent, (ConstraintStudentsActivityTagMaxHoursContinuously*)ctr);
		form.exec();
	}
	//51
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_ACTIVITY_TAG_MAX_HOURS_CONTINUOUSLY){
		ModifyConstraintStudentsSetActivityTagMaxHoursContinuouslyForm form(parent, (ConstraintStudentsSetActivityTagMaxHoursContinuously*)ctr);
		form.exec();
	}
	//52
	else if(ctr->type==CONSTRAINT_TEACHERS_MAX_DAYS_PER_WEEK){
		ModifyConstraintTeachersMaxDaysPerWeekForm form(parent, (ConstraintTeachersMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//53
	else if(ctr->type==CONSTRAINT_THREE_ACTIVITIES_GROUPED){
		ModifyConstraintThreeActivitiesGroupedForm form(parent, (ConstraintThreeActivitiesGrouped*)ctr);
		form.exec();
	}
	//54
	else if(ctr->type==CONSTRAINT_MAX_DAYS_BETWEEN_ACTIVITIES){
		ModifyConstraintMaxDaysBetweenActivitiesForm form(parent, (ConstraintMaxDaysBetweenActivities*)ctr);
		form.exec();
	}
	//55
	else if(ctr->type==CONSTRAINT_TEACHERS_MIN_DAYS_PER_WEEK){
		ModifyConstraintTeachersMinDaysPerWeekForm form(parent, (ConstraintTeachersMinDaysPerWeek*)ctr);
		form.exec();
	}
	//56
	else if(ctr->type==CONSTRAINT_TEACHER_MIN_DAYS_PER_WEEK){
		ModifyConstraintTeacherMinDaysPerWeekForm form(parent, (ConstraintTeacherMinDaysPerWeek*)ctr);
		form.exec();
	}
	//57
	else if(ctr->type==CONSTRAINT_TEACHERS_ACTIVITY_TAG_MAX_HOURS_DAILY){
		ModifyConstraintTeachersActivityTagMaxHoursDailyForm form(parent, (ConstraintTeachersActivityTagMaxHoursDaily*)ctr);
		form.exec();
	}
	//58
	else if(ctr->type==CONSTRAINT_TEACHER_ACTIVITY_TAG_MAX_HOURS_DAILY){
		ModifyConstraintTeacherActivityTagMaxHoursDailyForm form(parent, (ConstraintTeacherActivityTagMaxHoursDaily*)ctr);
		form.exec();
	}
	//59
	else if(ctr->type==CONSTRAINT_STUDENTS_ACTIVITY_TAG_MAX_HOURS_DAILY){
		ModifyConstraintStudentsActivityTagMaxHoursDailyForm form(parent, (ConstraintStudentsActivityTagMaxHoursDaily*)ctr);
		form.exec();
	}
	//60
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_ACTIVITY_TAG_MAX_HOURS_DAILY){
		ModifyConstraintStudentsSetActivityTagMaxHoursDailyForm form(parent, (ConstraintStudentsSetActivityTagMaxHoursDaily*)ctr);
		form.exec();
	}

	//61
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MAX_GAPS_PER_DAY){
		ModifyConstraintStudentsSetMaxGapsPerDayForm form(parent, (ConstraintStudentsSetMaxGapsPerDay*)ctr);
		form.exec();
	}
	//62
	else if(ctr->type==CONSTRAINT_STUDENTS_MAX_GAPS_PER_DAY){
		ModifyConstraintStudentsMaxGapsPerDayForm form(parent, (ConstraintStudentsMaxGapsPerDay*)ctr);
		form.exec();
	}
	//63
	else if(ctr->type==CONSTRAINT_ACTIVITIES_OCCUPY_MAX_TIME_SLOTS_FROM_SELECTION){
		ModifyConstraintActivitiesOccupyMaxTimeSlotsFromSelectionForm form(parent, (ConstraintActivitiesOccupyMaxTimeSlotsFromSelection*)ctr);
		form.exec();
	}
	//64
	else if(ctr->type==CONSTRAINT_ACTIVITIES_MAX_SIMULTANEOUS_IN_SELECTED_TIME_SLOTS){
		ModifyConstraintActivitiesMaxSimultaneousInSelectedTimeSlotsForm form(parent, (ConstraintActivitiesMaxSimultaneousInSelectedTimeSlots*)ctr);
		form.exec();
	}
	//65
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MAX_DAYS_PER_WEEK){
		ModifyConstraintStudentsSetMaxDaysPerWeekForm form(parent, (ConstraintStudentsSetMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//66
	else if(ctr->type==CONSTRAINT_STUDENTS_MAX_DAYS_PER_WEEK){
		ModifyConstraintStudentsMaxDaysPerWeekForm form(parent, (ConstraintStudentsMaxDaysPerWeek*)ctr);
		form.exec();
	}
	//2017-02-07
	//67
	else if(ctr->type==CONSTRAINT_TEACHER_MAX_SPAN_PER_DAY){
		ModifyConstraintTeacherMaxSpanPerDayForm form(parent, (ConstraintTeacherMaxSpanPerDay*)ctr);
		form.exec();
	}
	//68
	else if(ctr->type==CONSTRAINT_TEACHERS_MAX_SPAN_PER_DAY){
		ModifyConstraintTeachersMaxSpanPerDayForm form(parent, (ConstraintTeachersMaxSpanPerDay*)ctr);
		form.exec();
	}
	//69
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MAX_SPAN_PER_DAY){
		ModifyConstraintStudentsSetMaxSpanPerDayForm form(parent, (ConstraintStudentsSetMaxSpanPerDay*)ctr);
		form.exec();
	}
	//70
	else if(ctr->type==CONSTRAINT_STUDENTS_MAX_SPAN_PER_DAY){
		ModifyConstraintStudentsMaxSpanPerDayForm form(parent, (ConstraintStudentsMaxSpanPerDay*)ctr);
		form.exec();
	}
	//71
	else if(ctr->type==CONSTRAINT_TEACHER_MIN_RESTING_HOURS){
		ModifyConstraintTeacherMinRestingHoursForm form(parent, (ConstraintTeacherMinRestingHours*)ctr);
		form.exec();
	}
	//72
	else if(ctr->type==CONSTRAINT_TEACHERS_MIN_RESTING_HOURS){
		ModifyConstraintTeachersMinRestingHoursForm form(parent, (ConstraintTeachersMinRestingHours*)ctr);
		form.exec();
	}
	//73
	else if(ctr->type==CONSTRAINT_STUDENTS_SET_MIN_RESTING_HOURS){
		ModifyConstraintStudentsSetMinRestingHoursForm form(parent, (ConstraintStudentsSetMinRestingHours*)ctr);
		form.exec();
	}
	//74
	else if(ctr->type==CONSTRAINT_STUDENTS_MIN_RESTING_HOURS){
		ModifyConstraintStudentsMinRestingHoursForm form(parent, (ConstraintStudentsMinRestingHours*)ctr);
		form.exec();
	}
	//2018-06-13
	//75
	else if(ctr->type==CONSTRAINT_TWO_ACTIVITIES_ORDERED_IF_SAME_DAY){
		ModifyConstraintTwoActivitiesOrderedIfSameDayForm form(parent, (ConstraintTwoActivitiesOrderedIfSameDay*)ctr);
		form.exec();
	}
	//201
	else if(ctr->type==CONSTRAINT_TEACHER_MIN_CONTINUOUS_GAP_IN_INTERVAL){
		AddConstraintTeachersMinContinuousGapInIntervalForm form(parent, (ConstraintTeacherMinContinuousGapInInterval*)ctr);
		form.exec();
	}
	//202
	else if(ctr->type==CONSTRAINT_TEACHERS_MIN_CONTINUOUS_GAP_IN_INTERVAL){
		AddConstraintTeachersMinContinuousGapInIntervalForm form(parent, (ConstraintTeachersMinContinuousGapInInterval*)ctr);
		form.exec();
	}
	//203
	else if(ctr->type==CONSTRAINT_STUDENTSSET_MIN_CONTINUOUS_GAP_IN_INTERVAL){
		AddConstraintStudentsMinContinuousGapInIntervalForm form(parent, (ConstraintStudentsSetMinContinuousGapInInterval*)ctr);
		form.exec();
	}
	//204
	else if(ctr->type==CONSTRAINT_STUDENTS_MIN_CONTINUOUS_GAP_IN_INTERVAL){
		AddConstraintStudentsMinContinuousGapInIntervalForm form(parent, (ConstraintStudentsMinContinuousGapInInterval*)ctr);
		form.exec();
	}

	else{
		QMessageBox::critical(parent, tr("FET critical"), tr("You have found a bug in FET. Please report it. This kind of constraint"
		 " is not correctly recognized in all time constraints dialog. FET will skip parent error, so that you can continue work."
		 " Probably the constraint can be modified from the specific constraint dialog."));
		//assert(0);
		//exit(1);
		return false;
	}
	return true;
}

void AllTimeConstraintsForm::removeConstraint()
{
	int i=constraintsListWidget->currentRow();
	if(i<0){
		QMessageBox::information(this, tr("FET information"), tr("Invalid selected constraint"));
		return;
	}
	
	assert(i<visibleTimeConstraintsList.count());
	TimeConstraint* ctr=visibleTimeConstraintsList.at(i);

	QString s;
	s=tr("Remove constraint?");
	s+="\n\n";
	s+=ctr->getDetailedDescription(gt.rules);
	
	bool t;
	
	bool recompute;
	
	QListWidgetItem* item;
	
	int lres=LongTextMessageBox::confirmation( this, tr("FET confirmation"),
		s, tr("Yes"), tr("No"), 0, 0, 1 );
		
	if(lres==0){
		//The user clicked the OK button or pressed Enter
		
		QMessageBox::StandardButton wr=QMessageBox::Yes;
		
		if(ctr->type==CONSTRAINT_BASIC_COMPULSORY_TIME){ //additional confirmation for this one
			QString s=tr("Do you really want to remove the basic compulsory time constraint?");
			s+=" ";
			s+=tr("You cannot generate a timetable without this constraint.");
			s+="\n\n";
			s+=tr("Note: you can add again a constraint of this type from the menu Data -> Time constraints -> "
				"Miscellaneous -> Basic compulsory time constraints.");
				
			wr=QMessageBox::warning(this, tr("FET warning"), s,
				QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
		}
		
		if(wr==QMessageBox::Yes){
			if(ctr->type==CONSTRAINT_ACTIVITY_PREFERRED_STARTING_TIME){
				recompute=true;
			}
			else{
				recompute=false;
			}
		
			t=gt.rules.removeTimeConstraint(ctr);
			assert(t);
			visibleTimeConstraintsList.removeAt(i);
			constraintsListWidget->setCurrentRow(-1);
			item=constraintsListWidget->takeItem(i);
			delete item;
		
			constraintsTextLabel->setText(tr("%1 Time Constraints", "%1 represents the number of constraints").arg(visibleTimeConstraintsList.count()));
		
			if(recompute){
				LockUnlock::computeLockedUnlockedActivitiesOnlyTime(&gt.rules);
				LockUnlock::increaseCommunicationSpinBox();
			}
		}
	}
	//else if(lres==1){
		//The user clicked the Cancel button or pressed Escape
	//}

	if(i>=constraintsListWidget->count())
		i=constraintsListWidget->count()-1;
	if(i>=0)
		constraintsListWidget->setCurrentRow(i);
	else
		currentConstraintTextEdit->setPlainText(QString(""));
}

void AllTimeConstraintsForm::filter(bool active)
{
	if(!active){
		assert(useFilter==true);
		useFilter=false;
		
		filterChanged();
	
		return;
	}
	
	assert(active);
	
	AdvancedFilterForm filterForm(this, all, descrDetDescr, contains, text, caseSensitive, "AllTimeConstraintsAdvancedFilterForm");

	int t=filterForm.exec();
	
	if(t==QDialog::Accepted){
		assert(useFilter==false);
		useFilter=true;
	
		if(filterForm.allRadio->isChecked())
			all=true;
		else if(filterForm.anyRadio->isChecked())
			all=false;
		else
			assert(0);
			
		caseSensitive=filterForm.caseSensitiveCheckBox->isChecked();
			
		descrDetDescr.clear();
		contains.clear();
		text.clear();
			
		assert(filterForm.descrDetDescrComboBoxList.count()==filterForm.contNContReNReComboBoxList.count());
		assert(filterForm.descrDetDescrComboBoxList.count()==filterForm.textLineEditList.count());
		for(int i=0; i<filterForm.rows; i++){
			QComboBox* cb1=filterForm.descrDetDescrComboBoxList.at(i);
			QComboBox* cb2=filterForm.contNContReNReComboBoxList.at(i);
			QLineEdit* tl=filterForm.textLineEditList.at(i);
			
			descrDetDescr.append(cb1->currentIndex());
			contains.append(cb2->currentIndex());
			text.append(tl->text());
		}
		
		filterChanged();
	}
	else{
		assert(useFilter==false);
		useFilter=false;
	
		disconnect(filterCheckBox, SIGNAL(toggled(bool)), this, SLOT(filter(bool)));
		filterCheckBox->setChecked(false);
		connect(filterCheckBox, SIGNAL(toggled(bool)), this, SLOT(filter(bool)));
	}
}

void AllTimeConstraintsForm::activateConstraint()
{
	int i=constraintsListWidget->currentRow();
	if(i<0){
		QMessageBox::information(this, tr("FET information"), tr("Invalid selected constraint"));
	
		constraintsListWidget->setFocus();

		return;
	}
	
	assert(i<visibleTimeConstraintsList.count());
	TimeConstraint* ctr=visibleTimeConstraintsList.at(i);
	
	if(!ctr->active){
		ctr->active=true;
		
		gt.rules.internalStructureComputed=false;
		gt.rules.setModified(true);

		constraintsListWidget->currentItem()->setText(ctr->getDescription(gt.rules));
		if(USE_GUI_COLORS)
			constraintsListWidget->currentItem()->setBackground(constraintsListWidget->palette().base());
		constraintChanged();
		
		if(ctr->type==CONSTRAINT_ACTIVITY_PREFERRED_STARTING_TIME){
			LockUnlock::computeLockedUnlockedActivitiesOnlyTime(&gt.rules);
			LockUnlock::increaseCommunicationSpinBox();
		}
		
		int n_active=0;
		for(TimeConstraint* ctr2 : qAsConst(gt.rules.timeConstraintsList))
			if(filterOk(ctr2)){
				if(ctr2->active)
					n_active++;
			}
	
		constraintsTextLabel->setText(tr("%1 / %2 time constraints",
		 "%1 represents the number of visible active time constraints, %2 represents the total number of visible time constraints")
		 .arg(n_active).arg(visibleTimeConstraintsList.count()));
	}
	
	constraintsListWidget->setFocus();
}

void AllTimeConstraintsForm::deactivateConstraint()
{
	int i=constraintsListWidget->currentRow();
	if(i<0){
		QMessageBox::information(this, tr("FET information"), tr("Invalid selected constraint"));
	
		constraintsListWidget->setFocus();

		return;
	}
	
	assert(i<visibleTimeConstraintsList.count());
	TimeConstraint* ctr=visibleTimeConstraintsList.at(i);

	if(ctr->active){
		if(ctr->type==CONSTRAINT_BASIC_COMPULSORY_TIME){
			QMessageBox::warning(this, tr("FET warning"), tr("You are not allowed to deactivate the basic compulsory time constraints"));
			return;
		}
	
		ctr->active=false;
		
		gt.rules.internalStructureComputed=false;
		gt.rules.setModified(true);

		constraintsListWidget->currentItem()->setText(ctr->getDescription(gt.rules));
		if(USE_GUI_COLORS)
			constraintsListWidget->currentItem()->setBackground(constraintsListWidget->palette().alternateBase());
		constraintChanged();
		
		if(ctr->type==CONSTRAINT_ACTIVITY_PREFERRED_STARTING_TIME){
			LockUnlock::computeLockedUnlockedActivitiesOnlyTime(&gt.rules);
			LockUnlock::increaseCommunicationSpinBox();
		}

		int n_active=0;
		for(TimeConstraint* ctr2 : qAsConst(gt.rules.timeConstraintsList))
			if(filterOk(ctr2)){
				if(ctr2->active)
					n_active++;
			}
	
		constraintsTextLabel->setText(tr("%1 / %2 time constraints",
		 "%1 represents the number of visible active time constraints, %2 represents the total number of visible time constraints")
		 .arg(n_active).arg(visibleTimeConstraintsList.count()));
	}
	
	constraintsListWidget->setFocus();
}

/*static int timeConstraintsAscendingByComments(const TimeConstraint* t1, const TimeConstraint* t2)
{
	return t1->comments < t2->comments;
}

void AllTimeConstraintsForm::sortConstraintsByComments()
{
	QMessageBox::StandardButton t=QMessageBox::question(this, tr("Sort constraints?"),
	 tr("This will sort the time constraints list ascending according to their comments. You can obtain "
	 "a custom ordering by adding comments to some or all time constraints, for example 'rank #1 ... other comments', "
	 "'rank #2 ... other different comments'.")
	 +" "+tr("Are you sure you want to continue?"),
	 QMessageBox::Yes|QMessageBox::Cancel);
	
	if(t==QMessageBox::Cancel)
		return;
	
	std::stable_sort(gt.rules.timeConstraintsList.begin(), gt.rules.timeConstraintsList.end(), timeConstraintsAscendingByComments);

	gt.rules.internalStructureComputed=false;
	gt.rules.setModified(true);
	
	filterChanged();
}*/

void AllTimeConstraintsForm::constraintComments()
{
	int i=constraintsListWidget->currentRow();
	if(i<0){
		QMessageBox::information(this, tr("FET information"), tr("Invalid selected constraint"));
		return;
	}
	
	assert(i<visibleTimeConstraintsList.count());
	TimeConstraint* ctr=visibleTimeConstraintsList.at(i);

	EditCommentsForm dialog("TimeConstraintCommentsDialog", this, tr("Constraint comments"));
	dialog.setComments(ctr->comments);

	int t=dialog.exec();

	if(t==QDialog::Accepted){
		ctr->comments=dialog.getComments();
	
		gt.rules.internalStructureComputed=false;
		gt.rules.setModified(true);

		constraintsListWidget->currentItem()->setText(ctr->getDescription(gt.rules));
		constraintChanged();
	}
}
