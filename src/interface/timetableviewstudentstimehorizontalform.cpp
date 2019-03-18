/***************************************************************************
                          timetableviewstudentstimehorizontalform.cpp  -  description
                             -------------------
    begin                : 2017
    copyright            : (C) 2017 by Lalescu Liviu
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

#include <QtGlobal>

#include "tablewidgetupdatebug.h"

#include "longtextmessagebox.h"
#include "centerwidgetonscreen.h"

#include "fetmainform.h"
#include "timetableviewstudentstimehorizontalform.h"
#include "timetable_defs.h"
#include "timetable.h"
#include "solution.h"

#include "fet.h"

#include "matrix.h"

#include "lockunlock.h"

#include "errorrenderer.h"

#include <QMessageBox>

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <QAbstractItemView>

#include <QListWidget>

#include <QList>

#include <QCoreApplication>
#include <QApplication>

#include <QString>
#include <QStringList>

#include <QSplitter>
#include <QSettings>
#include <QObject>
#include <QMetaObject>

//begin by Marco Vassura
#include <QBrush>
#include <QColor>
//end by Marco Vassura

#include <QPainter>

#include <QHash>
#include <QSet>
#include <QPair>

#include "timetableexport.h"

extern bool simulation_running;

//extern Matrix3D<bool> subgroupNotAvailableDayHour;
extern Matrix2D<bool> breakDayHour;
extern QHash<QString, QSet<QPair<int, int> > > studentsSetNotAvailableDayHour;

extern const int MINIMUM_WIDTH_SPIN_BOX_VALUE; //trick found on the internet, so that these two constants are visible in timetableviewteacherstimehorizontalform.cpp
extern const int MINIMUM_HEIGHT_SPIN_BOX_VALUE;
const int MINIMUM_WIDTH_SPIN_BOX_VALUE=9;
const int MINIMUM_HEIGHT_SPIN_BOX_VALUE=9;


TimetableViewStudentsTimeHorizontalForm::TimetableViewStudentsTimeHorizontalForm(QWidget* parent): QDialog(parent)
{
	setupUi(this);
	
	closePushButton->setDefault(true);
	
	detailsTextEdit->setReadOnly(true);

	//columnResizeModeInitialized=false;

	verticalSplitter->setStretchFactor(0, 20);
	verticalSplitter->setStretchFactor(1, 1);
	horizontalSplitter->setStretchFactor(0, 5);
	horizontalSplitter->setStretchFactor(1, 1);

	studentsTimetableTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
	
	connect(closePushButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(studentsTimetableTable, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)));
	connect(lockTimePushButton, SIGNAL(clicked()), this, SLOT(lockTime()));
	connect(lockSpacePushButton, SIGNAL(clicked()), this, SLOT(lockSpace()));
	connect(lockTimeSpacePushButton, SIGNAL(clicked()), this, SLOT(lockTimeSpace()));

	connect(helpPushButton, SIGNAL(clicked()), this, SLOT(help()));
	
	lockRadioButton->setChecked(true);
	unlockRadioButton->setChecked(false);
	toggleRadioButton->setChecked(false);

	centerWidgetOnScreen(this);
	restoreFETDialogGeometry(this);

	//restore vertical splitter state
	QSettings settings;
	if(settings.contains(this->metaObject()->className()+QString("/vertical-splitter-state")))
		verticalSplitter->restoreState(settings.value(this->metaObject()->className()+QString("/vertical-splitter-state")).toByteArray());

	//restore horizontal splitter state
	//QSettings settings(COMPANY, PROGRAM);
	if(settings.contains(this->metaObject()->className()+QString("/horizontal-splitter-state")))
		horizontalSplitter->restoreState(settings.value(this->metaObject()->className()+QString("/horizontal-splitter-state")).toByteArray());

	if(settings.contains(this->metaObject()->className()+QString("/lock-radio-button")))
		lockRadioButton->setChecked(settings.value(this->metaObject()->className()+QString("/lock-radio-button")).toBool());
	if(settings.contains(this->metaObject()->className()+QString("/unlock-radio-button")))
		unlockRadioButton->setChecked(settings.value(this->metaObject()->className()+QString("/unlock-radio-button")).toBool());
	if(settings.contains(this->metaObject()->className()+QString("/toggle-radio-button")))
		toggleRadioButton->setChecked(settings.value(this->metaObject()->className()+QString("/toggle-radio-button")).toBool());

	LockUnlock::assertIsUpdated(&gt.rules);

	/*if(gt.rules.nInternalTeachers!=gt.rules.teachersList.count()){
		QMessageBox::warning(this, tr("FET warning"), tr("Cannot display the timetable, because you added or removed some teachers. Please regenerate the timetable and then view it"));
		return;
	}*/

	//Commented on 2018-07-20
	//LockUnlock::increaseCommunicationSpinBox();
	
	usedStudentsSet.clear();
	for(int i=0; i<gt.rules.nInternalActivities; i++){
		const Activity* act=&gt.rules.internalActivitiesList[i];
		for(const QString& students : qAsConst(act->studentsNames)){
			if(!usedStudentsSet.contains(students))
				usedStudentsSet.insert(students);
		}
	}
	
	QHash<QString, QSet<QPair<int, int> > >::const_iterator it=studentsSetNotAvailableDayHour.constBegin();
	while(it!=studentsSetNotAvailableDayHour.constEnd()){
		if(!usedStudentsSet.contains(it.key()))
			usedStudentsSet.insert(it.key());
			
		it++;
	}
	
	QSet<QString> studentsSet2;
	usedStudentsList.clear();
	for(StudentsYear* year : qAsConst(gt.rules.augmentedYearsList)){
		if(usedStudentsSet.contains(year->name) && !studentsSet2.contains(year->name)){
			usedStudentsList.append(year->name);
			studentsSet2.insert(year->name);
		}
		for(StudentsGroup* group : qAsConst(year->groupsList)){
			if(usedStudentsSet.contains(group->name) && !studentsSet2.contains(group->name)){
				usedStudentsList.append(group->name);
				studentsSet2.insert(group->name);
			}
			for(StudentsSubgroup* subgroup : qAsConst(group->subgroupsList)){
				if(usedStudentsSet.contains(subgroup->name) && !studentsSet2.contains(subgroup->name)){
					usedStudentsList.append(subgroup->name);
					studentsSet2.insert(subgroup->name);
				}
			}
		}
	}

	studentsTimetableTable->setRowCount(usedStudentsList.count());
	studentsTimetableTable->setColumnCount(gt.rules.nDaysPerWeek*gt.rules.nHoursPerDay);
	
	oldItemDelegate=studentsTimetableTable->itemDelegate();
	newItemDelegate=new TimetableTimeHorizontalItemDelegate(NULL, studentsTimetableTable->rowCount(), gt.rules.nHoursPerDay);
	studentsTimetableTable->setItemDelegate(newItemDelegate);
	
	bool min2letters=false;
	for(int d=0; d<gt.rules.nDaysPerWeek; d++){
		if(gt.rules.daysOfTheWeek[d].size()>gt.rules.nHoursPerDay){
			min2letters=true;
			break;
		}
	}
	for(int d=0; d<gt.rules.nDaysPerWeek; d++){
		QString dayName=gt.rules.daysOfTheWeek[d];
		int t=dayName.size();
		int q=t/gt.rules.nHoursPerDay;
		int r=t%gt.rules.nHoursPerDay;
		QStringList list;
		
		if(q==0)
			q=1;
		
		for(int i=0; i<gt.rules.nHoursPerDay; i++){
			if(!min2letters){
				list.append(dayName.left(1));
				dayName.remove(0, 1);
			}
			else if(i<r || q<=1){
				assert(q>=1);
				list.append(dayName.left(q+1));
				dayName.remove(0, q+1);
			}
			else{
				list.append(dayName.left(q));
				dayName.remove(0, q);
			}
		}
	
		for(int h=0; h<gt.rules.nHoursPerDay; h++){
			QTableWidgetItem* item=new QTableWidgetItem(list.at(h)+"\n"+gt.rules.hoursOfTheDay[h]);
			item->setToolTip(gt.rules.daysOfTheWeek[d]+"\n"+gt.rules.hoursOfTheDay[h]);
			studentsTimetableTable->setHorizontalHeaderItem(d*gt.rules.nHoursPerDay+h, item);
		}
	}
	for(int t=0; t<usedStudentsList.count(); t++){
		QTableWidgetItem* item=new QTableWidgetItem(usedStudentsList.at(t));
		item->setToolTip(usedStudentsList.at(t));
		studentsTimetableTable->setVerticalHeaderItem(t, item);
	}

	for(int t=0; t<usedStudentsList.count(); t++){
		for(int d=0; d<gt.rules.nDaysPerWeek; d++){
			for(int h=0; h<gt.rules.nHoursPerDay; h++){
				QTableWidgetItem* item= new QTableWidgetItem();
				item->setTextAlignment(Qt::AlignCenter);
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

				studentsTimetableTable->setItem(t, d*gt.rules.nHoursPerDay+h, item);
			}
		}
	}
	
	//resize columns
	//if(!columnResizeModeInitialized){
//	teachersTimetableTable->horizontalHeader()->setMinimumSectionSize(teachersTimetableTable->horizontalHeader()->defaultSectionSize());
	//	columnResizeModeInitialized=true;
	
	initialRecommendedHeight=studentsTimetableTable->verticalHeader()->sectionSizeHint(0);
	
	int h;
	int w;

	if(settings.contains(this->metaObject()->className()+QString("/vertical-header-size"))){
		h=settings.value(this->metaObject()->className()+QString("/vertical-header-size")).toInt();
		if(h==0)
			h=MINIMUM_HEIGHT_SPIN_BOX_VALUE;
	}
	else{
		h=MINIMUM_HEIGHT_SPIN_BOX_VALUE;
	}
//	if(h==0)
//		h=initialRecommendedHeight;

	if(settings.contains(this->metaObject()->className()+QString("/horizontal-header-size"))){
		w=settings.value(this->metaObject()->className()+QString("/horizontal-header-size")).toInt();
		if(w==0)
			w=MINIMUM_WIDTH_SPIN_BOX_VALUE;
	}
	else{
		w=MINIMUM_WIDTH_SPIN_BOX_VALUE;
	}
//	if(w==0)
//		w=2*initialRecommendedHeight;
		
	widthSpinBox->setSuffix(QString(" ")+tr("px", "Abbreviation for pixels"));
	widthSpinBox->setMinimum(MINIMUM_WIDTH_SPIN_BOX_VALUE);
#if QT_VERSION >= 0x050200
	widthSpinBox->setMaximum(studentsTimetableTable->verticalHeader()->maximumSectionSize());
#else
	widthSpinBox->setMaximum(maxScreenWidth(this));
#endif
	widthSpinBox->setValue(w);
	widthSpinBox->setSpecialValueText(tr("Automatic"));
	
	heightSpinBox->setSuffix(QString(" ")+tr("px", "Abbreviation for pixels"));
	heightSpinBox->setMinimum(MINIMUM_HEIGHT_SPIN_BOX_VALUE);
#if QT_VERSION >= 0x050200
	heightSpinBox->setMaximum(studentsTimetableTable->verticalHeader()->maximumSectionSize());
#else
	heightSpinBox->setMaximum(maxScreenWidth(this));
#endif
	heightSpinBox->setValue(h);
	heightSpinBox->setSpecialValueText(tr("Automatic"));
	
	widthSpinBoxValueChanged();
	heightSpinBoxValueChanged();
	
	connect(widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(widthSpinBoxValueChanged()));
	connect(heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(heightSpinBoxValueChanged()));
	
//	teachersTimetableTable->verticalHeader()->setDefaultSectionSize(h);
//	teachersTimetableTable->horizontalHeader()->setDefaultSectionSize(w);

#if QT_VERSION >= 0x050000
	studentsTimetableTable->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	studentsTimetableTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#else
	studentsTimetableTable->verticalHeader()->setResizeMode(QHeaderView::Interactive);
	studentsTimetableTable->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
#endif
	//}
	////////////////
	
	subjectsCheckBox->setChecked(true);
	teachersCheckBox->setChecked(false);
	
	if(settings.contains(this->metaObject()->className()+QString("/subjects-check-box-state"))){
		bool state=settings.value(this->metaObject()->className()+QString("/subjects-check-box-state")).toBool();
		subjectsCheckBox->setChecked(state);
	}
	if(settings.contains(this->metaObject()->className()+QString("/teachers-check-box-state"))){
		bool state=settings.value(this->metaObject()->className()+QString("/teachers-check-box-state")).toBool();
		teachersCheckBox->setChecked(state);
	}
	
	connect(subjectsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateStudentsTimetableTable()));
	connect(teachersCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateStudentsTimetableTable()));
	
	//added by Volker Dirr
	connect(&LockUnlock::communicationSpinBox, SIGNAL(valueChanged()), this, SLOT(updateStudentsTimetableTable()));
	
	updateStudentsTimetableTable();
}

void TimetableViewStudentsTimeHorizontalForm::newTimetableGenerated()
//Similar to the constructor
{
	//setupUi(this);
	
	//closePushButton->setDefault(true);
	
	//detailsTextEdit->setReadOnly(true);

	//columnResizeModeInitialized=false;

	/*verticalSplitter->setStretchFactor(0, 20);
	verticalSplitter->setStretchFactor(1, 1);
	horizontalSplitter->setStretchFactor(0, 5);
	horizontalSplitter->setStretchFactor(1, 1);

	studentsTimetableTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
	
	connect(closePushButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(studentsTimetableTable, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)));
	connect(lockTimePushButton, SIGNAL(clicked()), this, SLOT(lockTime()));
	connect(lockSpacePushButton, SIGNAL(clicked()), this, SLOT(lockSpace()));
	connect(lockTimeSpacePushButton, SIGNAL(clicked()), this, SLOT(lockTimeSpace()));

	connect(helpPushButton, SIGNAL(clicked()), this, SLOT(help()));*/
	
	/*lockRadioButton->setChecked(true);
	unlockRadioButton->setChecked(false);
	toggleRadioButton->setChecked(false);

	centerWidgetOnScreen(this);
	restoreFETDialogGeometry(this);

	//restore vertical splitter state
	QSettings settings(COMPANY, PROGRAM);
	if(settings.contains(this->metaObject()->className()+QString("/vertical-splitter-state")))
		verticalSplitter->restoreState(settings.value(this->metaObject()->className()+QString("/vertical-splitter-state")).toByteArray());

	//restore horizontal splitter state
	//QSettings settings(COMPANY, PROGRAM);
	if(settings.contains(this->metaObject()->className()+QString("/horizontal-splitter-state")))
		horizontalSplitter->restoreState(settings.value(this->metaObject()->className()+QString("/horizontal-splitter-state")).toByteArray());

	if(settings.contains(this->metaObject()->className()+QString("/lock-radio-button")))
		lockRadioButton->setChecked(settings.value(this->metaObject()->className()+QString("/lock-radio-button")).toBool());
	if(settings.contains(this->metaObject()->className()+QString("/unlock-radio-button")))
		unlockRadioButton->setChecked(settings.value(this->metaObject()->className()+QString("/unlock-radio-button")).toBool());
	if(settings.contains(this->metaObject()->className()+QString("/toggle-radio-button")))
		toggleRadioButton->setChecked(settings.value(this->metaObject()->className()+QString("/toggle-radio-button")).toBool());*/

	LockUnlock::assertIsUpdated(&gt.rules);

	/*if(gt.rules.nInternalTeachers!=gt.rules.teachersList.count()){
		QMessageBox::warning(this, tr("FET warning"), tr("Cannot display the timetable, because you added or removed some teachers. Please regenerate the timetable and then view it"));
		return;
	}*/

	//DON'T UNCOMMENT THIS CODE -> LEADS TO CRASH IF THERE ARE MORE VIEWS OPENED.
	//LockUnlock::increaseCommunicationSpinBox();
	
	usedStudentsSet.clear();
	for(int i=0; i<gt.rules.nInternalActivities; i++){
		Activity* act=&gt.rules.internalActivitiesList[i];
		for(const QString& students : qAsConst(act->studentsNames)){
			if(!usedStudentsSet.contains(students))
				usedStudentsSet.insert(students);
		}
	}
	
	QHash<QString, QSet<QPair<int, int> > >::const_iterator it=studentsSetNotAvailableDayHour.constBegin();
	while(it!=studentsSetNotAvailableDayHour.constEnd()){
		if(!usedStudentsSet.contains(it.key()))
			usedStudentsSet.insert(it.key());
			
		it++;
	}
	
	QSet<QString> studentsSet2;
	usedStudentsList.clear();
	for(StudentsYear* year : qAsConst(gt.rules.augmentedYearsList)){
		if(usedStudentsSet.contains(year->name) && !studentsSet2.contains(year->name)){
			usedStudentsList.append(year->name);
			studentsSet2.insert(year->name);
		}
		for(StudentsGroup* group : qAsConst(year->groupsList)){
			if(usedStudentsSet.contains(group->name) && !studentsSet2.contains(group->name)){
				usedStudentsList.append(group->name);
				studentsSet2.insert(group->name);
			}
			for(StudentsSubgroup* subgroup : qAsConst(group->subgroupsList)){
				if(usedStudentsSet.contains(subgroup->name) && !studentsSet2.contains(subgroup->name)){
					usedStudentsList.append(subgroup->name);
					studentsSet2.insert(subgroup->name);
				}
			}
		}
	}

	studentsTimetableTable->clear();
	studentsTimetableTable->setRowCount(usedStudentsList.count());
	studentsTimetableTable->setColumnCount(gt.rules.nDaysPerWeek*gt.rules.nHoursPerDay);
	
	newItemDelegate->nRows=studentsTimetableTable->rowCount();
	newItemDelegate->nColumns=gt.rules.nHoursPerDay;
	/*studentsTimetableTable->setItemDelegate(oldItemDelegate);
	delete newItemDelegate;
	//oldItemDelegate=studentsTimetableTable->itemDelegate();
	newItemDelegate=new TimetableViewStudentsTimeHorizontalDelegate(NULL, studentsTimetableTable->rowCount(), gt.rules.nHoursPerDay);
	studentsTimetableTable->setItemDelegate(newItemDelegate);*/
	
	bool min2letters=false;
	for(int d=0; d<gt.rules.nDaysPerWeek; d++){
		if(gt.rules.daysOfTheWeek[d].size()>gt.rules.nHoursPerDay){
			min2letters=true;
			break;
		}
	}
	for(int d=0; d<gt.rules.nDaysPerWeek; d++){
		QString dayName=gt.rules.daysOfTheWeek[d];
		int t=dayName.size();
		int q=t/gt.rules.nHoursPerDay;
		int r=t%gt.rules.nHoursPerDay;
		QStringList list;
		
		if(q==0)
			q=1;
		
		for(int i=0; i<gt.rules.nHoursPerDay; i++){
			if(!min2letters){
				list.append(dayName.left(1));
				dayName.remove(0, 1);
			}
			else if(i<r || q<=1){
				assert(q>=1);
				list.append(dayName.left(q+1));
				dayName.remove(0, q+1);
			}
			else{
				list.append(dayName.left(q));
				dayName.remove(0, q);
			}
		}
	
		for(int h=0; h<gt.rules.nHoursPerDay; h++){
			QTableWidgetItem* item=new QTableWidgetItem(list.at(h)+"\n"+gt.rules.hoursOfTheDay[h]);
			item->setToolTip(gt.rules.daysOfTheWeek[d]+"\n"+gt.rules.hoursOfTheDay[h]);
			studentsTimetableTable->setHorizontalHeaderItem(d*gt.rules.nHoursPerDay+h, item);
		}
	}
	for(int t=0; t<usedStudentsList.count(); t++){
		QTableWidgetItem* item=new QTableWidgetItem(usedStudentsList.at(t));
		item->setToolTip(usedStudentsList.at(t));
		studentsTimetableTable->setVerticalHeaderItem(t, item);
	}

	for(int t=0; t<usedStudentsList.count(); t++){
		for(int d=0; d<gt.rules.nDaysPerWeek; d++){
			for(int h=0; h<gt.rules.nHoursPerDay; h++){
				QTableWidgetItem* item= new QTableWidgetItem();
				item->setTextAlignment(Qt::AlignCenter);
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

				studentsTimetableTable->setItem(t, d*gt.rules.nHoursPerDay+h, item);
			}
		}
	}
	
	//resize columns
	//if(!columnResizeModeInitialized){
//	teachersTimetableTable->horizontalHeader()->setMinimumSectionSize(teachersTimetableTable->horizontalHeader()->defaultSectionSize());
	//	columnResizeModeInitialized=true;
	
	/*initialRecommendedHeight=studentsTimetableTable->verticalHeader()->sectionSizeHint(0);
	
	int h;
	int w;

	if(settings.contains(this->metaObject()->className()+QString("/vertical-header-size"))){
		h=settings.value(this->metaObject()->className()+QString("/vertical-header-size")).toInt();
		if(h==0)
			h=MINIMUM_HEIGHT_SPIN_BOX_VALUE;
	}
	else{
		h=MINIMUM_HEIGHT_SPIN_BOX_VALUE;
	}
//	if(h==0)
//		h=initialRecommendedHeight;

	if(settings.contains(this->metaObject()->className()+QString("/horizontal-header-size"))){
		w=settings.value(this->metaObject()->className()+QString("/horizontal-header-size")).toInt();
		if(w==0)
			w=MINIMUM_WIDTH_SPIN_BOX_VALUE;
	}
	else{
		w=MINIMUM_WIDTH_SPIN_BOX_VALUE;
	}
//	if(w==0)
//		w=2*initialRecommendedHeight;
		
	widthSpinBox->setSuffix(QString(" ")+tr("px", "Abbreviation for pixels"));
	widthSpinBox->setMinimum(MINIMUM_WIDTH_SPIN_BOX_VALUE);
#if QT_VERSION >= 0x050200
	widthSpinBox->setMaximum(studentsTimetableTable->verticalHeader()->maximumSectionSize());
#else
	widthSpinBox->setMaximum(maxScreenWidth(this));
#endif
	widthSpinBox->setValue(w);
	widthSpinBox->setSpecialValueText(tr("Automatic"));
	
	heightSpinBox->setSuffix(QString(" ")+tr("px", "Abbreviation for pixels"));
	heightSpinBox->setMinimum(MINIMUM_HEIGHT_SPIN_BOX_VALUE);
#if QT_VERSION >= 0x050200
	heightSpinBox->setMaximum(studentsTimetableTable->verticalHeader()->maximumSectionSize());
#else
	heightSpinBox->setMaximum(maxScreenWidth(this));
#endif
	heightSpinBox->setValue(h);
	heightSpinBox->setSpecialValueText(tr("Automatic"));
	
	widthSpinBoxValueChanged();
	heightSpinBoxValueChanged();
	
	connect(widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(widthSpinBoxValueChanged()));
	connect(heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(heightSpinBoxValueChanged()));
	
//	teachersTimetableTable->verticalHeader()->setDefaultSectionSize(h);
//	teachersTimetableTable->horizontalHeader()->setDefaultSectionSize(w);

#if QT_VERSION >= 0x050000
	studentsTimetableTable->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	studentsTimetableTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#else
	studentsTimetableTable->verticalHeader()->setResizeMode(QHeaderView::Interactive);
	studentsTimetableTable->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
#endif
	//}
	////////////////
	
	subjectsCheckBox->setChecked(true);
	teachersCheckBox->setChecked(false);
	
	if(settings.contains(this->metaObject()->className()+QString("/subjects-check-box-state"))){
		bool state=settings.value(this->metaObject()->className()+QString("/subjects-check-box-state")).toBool();
		subjectsCheckBox->setChecked(state);
	}
	if(settings.contains(this->metaObject()->className()+QString("/teachers-check-box-state"))){
		bool state=settings.value(this->metaObject()->className()+QString("/teachers-check-box-state")).toBool();
		teachersCheckBox->setChecked(state);
	}
	
	connect(subjectsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateStudentsTimetableTable()));
	connect(teachersCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateStudentsTimetableTable()));*/
	
	//added by Volker Dirr
	//connect(&communicationSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateStudentsTimetableTable()));
	
	updateStudentsTimetableTable();
}

TimetableViewStudentsTimeHorizontalForm::~TimetableViewStudentsTimeHorizontalForm()
{
	saveFETDialogGeometry(this);

	//save vertical splitter state
	QSettings settings;
	settings.setValue(this->metaObject()->className()+QString("/vertical-splitter-state"), verticalSplitter->saveState());

	//save horizontal splitter state
	//QSettings settings(COMPANY, PROGRAM);
	settings.setValue(this->metaObject()->className()+QString("/horizontal-splitter-state"), horizontalSplitter->saveState());

	settings.setValue(this->metaObject()->className()+QString("/lock-radio-button"), lockRadioButton->isChecked());
	settings.setValue(this->metaObject()->className()+QString("/unlock-radio-button"), unlockRadioButton->isChecked());
	settings.setValue(this->metaObject()->className()+QString("/toggle-radio-button"), toggleRadioButton->isChecked());

	if(heightSpinBox->value()<=MINIMUM_HEIGHT_SPIN_BOX_VALUE)
		settings.setValue(this->metaObject()->className()+QString("/vertical-header-size"), 0);
	else
		settings.setValue(this->metaObject()->className()+QString("/vertical-header-size"), heightSpinBox->value());
		
	if(widthSpinBox->value()<=MINIMUM_WIDTH_SPIN_BOX_VALUE)
		settings.setValue(this->metaObject()->className()+QString("/horizontal-header-size"), 0);
	else
		settings.setValue(this->metaObject()->className()+QString("/horizontal-header-size"), widthSpinBox->value());
		
	settings.setValue(this->metaObject()->className()+QString("/subjects-check-box-state"), subjectsCheckBox->isChecked());
	settings.setValue(this->metaObject()->className()+QString("/teachers-check-box-state"), teachersCheckBox->isChecked());
		
	studentsTimetableTable->setItemDelegate(oldItemDelegate);
	delete newItemDelegate;
	
	usedStudentsList.clear();
	usedStudentsSet.clear();
	//activitiesForStudentsSet.clear();
	
	//notAvailableHash.clear();
}

void TimetableViewStudentsTimeHorizontalForm::resizeRowsAfterShow()
{
//	studentsTimetableTable->resizeRowsToContents();
}

void TimetableViewStudentsTimeHorizontalForm::updateStudentsTimetableTable(){
	if(!CachedSchedule::isValid()){
		QMessageBox::warning(this, tr("FET warning"), tr("Timetable not available in view students timetable dialog - please generate a new timetable "
		"or close the timetable view students dialog"));
		return;
	}

	if(gt.rules.nInternalRooms!=gt.rules.roomsList.count()){
		QMessageBox::warning(this, tr("FET warning"), tr("Cannot display the timetable, because you added or removed some rooms. Please regenerate the timetable and then view it"));
		return;
	}

	assert(gt.rules.initialized);
	
	for(int t=0; t<usedStudentsList.count(); t++){
		assert(t<studentsTimetableTable->rowCount());
		
		int sbg = getStudentSetInternalIndexFromRow(t);
		if (sbg < 0)
			continue;
		
		QSet<QPair<int, int> > notAvailableDayHour=studentsSetNotAvailableDayHour.value(usedStudentsList.at(t), QSet<QPair<int, int> >());
		
		/*ConstraintStudentsSetNotAvailableTimes* ctr=notAvailableHash.value(usedStudentsList.at(t), NULL);
		if(ctr!=NULL){
			for(int i=0; i<ctr->days.count(); i++){
				int d=ctr->days.at(i);
				int h=ctr->hours.at(i);
				notAvailableDayHour.insert(QPair<int,int>(d,h));
			}
		}*/

		for(int k=0; k<studentsTimetableTable->columnCount(); k++){
			if (studentsTimetableTable->columnSpan(t,k) != 1)
				studentsTimetableTable->setSpan(t, k, 1, 1);
		}
		
		for(int d=0; d<gt.rules.nDaysPerWeek; d++){
			for(int h=0; h<gt.rules.nHoursPerDay; ){
				const int tableColumnIdx = d*gt.rules.nHoursPerDay+h;
				assert(tableColumnIdx<studentsTimetableTable->columnCount());

				QTableWidgetItem *item = studentsTimetableTable->item(t, tableColumnIdx);

				//begin by Marco Vassura
				// add colors (start)
				//if(USE_GUI_COLORS) {
					item->setBackground(studentsTimetableTable->palette().color(QPalette::Base));
					item->setForeground(studentsTimetableTable->palette().color(QPalette::Text));
				//}
				// add colors (end)
				//end by Marco Vassura

				QString s = "";
				
				int ai=CachedSchedule::students_timetable_weekly[sbg][d][h]; //activity index
				
				bool ok=true;
				if(ai==UNALLOCATED_ACTIVITY){
					ok=false;
				}
				else{
					if(!gt.rules.internalActivitiesList[ai].studentsNames.contains(usedStudentsList.at(t))){
						ok=false;
					}
				}
				
				//Activity* act=gt.rules.activitiesList.at(ai);
				if(ok){
					const Activity* act=&gt.rules.internalActivitiesList[ai];
					assert(act!=NULL);
					
					if(TIMETABLE_HTML_PRINT_ACTIVITY_TAGS){
						QString ats=act->activityTagsNames.join(", ");
						s += act->subjectName+" "+ats;
					}
					else{
						s += act->subjectName;
					}
					
					//teachers
					if(act->teachersNames.count()>0){
						//s+=" ";
						s+="\n";
						s+=act->teachersNames.join(", ");
					}
					
					if(act->studentsNames.count()==1){
						//Comment taken from the teachers view timetable time horizontal
						//Don't do the assert below, because it crashes if you change the teacher's name and view the teachers' timetable,
						//without generating again (as reported by Yush Yuen).
						//assert(act->teachersNames.at(0)==teachername);
					}
					else{
						assert(act->studentsNames.count()>=2);
						//Comment taken from the teachers view timetable time horizontal
						//Don't do the assert below, because it crashes if you change the teacher's name and view the teachers' timetable,
						//without generating again (as reported by Yush Yuen).
						//assert(act->teachersNames.contains(teachername));
						//s+=" ";
						s+="\n";
						s+=act->studentsNames.join(", ");
					}
					
					int r=CachedSchedule::getCachedSolution().room(ai);
					if(r!=UNALLOCATED_SPACE && r!=UNSPECIFIED_ROOM){
						//s+=" ";
						//s+=tr("R:%1", "Room").arg(gt.rules.internalRoomsList[r]->name);
						//s+=" ";
						s+="\n";
						s+=gt.rules.internalRoomsList[r]->name;
					}
					
					if(LockUnlock::isActivityTimeLocked(act->id)){
						QFont font(item->font());
						font.setBold(true);
						item->setFont(font);
					}
					else{
						QFont font(item->font());
						font.setBold(false);
						item->setFont(font);
					}
					
					if(LockUnlock::isActivitySpaceLocked(act->id)){
						QFont font(item->font());
						font.setItalic(true);
						item->setFont(font);
					}
					else{
						QFont font(item->font());
						font.setItalic(false);
						item->setFont(font);
					}

					s+=LockUnlock::getActivityLockTipString(act->id);

					//begin by Marco Vassura
					// add colors (start)
					if(USE_GUI_COLORS /*&& act->studentsNames.count()>0*/){
						QBrush bg(stringToColor(act->subjectName));
						item->setBackground(bg);
						double brightness = bg.color().redF()*0.299 + bg.color().greenF()*0.587 + bg.color().blueF()*0.114;
						if (brightness<0.5)
							item->setForeground(QBrush(Qt::white));
						else
							item->setForeground(QBrush(Qt::black));
					}
					// add colors (end)
					//end by Marco Vassura
				}
				else{
//					if(subgroupNotAvailableDayHour[sbg][d][h] && PRINT_NOT_AVAILABLE_TIME_SLOTS)
					if(notAvailableDayHour.contains(QPair<int,int>(d,h)) && PRINT_NOT_AVAILABLE_TIME_SLOTS)
						s+="-x-";
					else if(breakDayHour[d][h] && PRINT_BREAK_TIME_SLOTS)
						s+="-X-";
				}
				if(ok){
					QString s2;
					const Activity* act=&gt.rules.internalActivitiesList[ai];
					if(teachersCheckBox->isChecked() && !act->teachersNames.isEmpty()){
						s2+=act->teachersNames.join(", ");
					}
					if(subjectsCheckBox->isChecked()){
						if(!s2.isEmpty()){
							s2+=" ";
							//s2+="\n";
						}
						s2+=act->subjectName;
					}
					item->setText(s2);
				}
				else
					item->setText(s);
				item->setToolTip(s);

				int columnSpan = ai!=UNALLOCATED_ACTIVITY? gt.rules.internalActivitiesList[ai].duration : 1;
				if (columnSpan != studentsTimetableTable->columnSpan(t, tableColumnIdx))
					studentsTimetableTable->setSpan(t, tableColumnIdx, 1, columnSpan);
				h += columnSpan;
			}
		}
	}
	//	for(int i=0; i<gt.rules.nHoursPerDay; i++) //added in version 3_9_16, on 16 Oct. 2004
	//		teachersTimetableTable->adjustRow(i);

//	teachersTimetableTable->resizeRowsToContents();
	
	tableWidgetUpdateBug(studentsTimetableTable);
	
	detailActivity(studentsTimetableTable->currentItem());
}

/*void TimetableViewTeachersTimeHorizontalForm::resizeEvent(QResizeEvent* event)
{
	QDialog::resizeEvent(event);

//	teachersTimetableTable->resizeRowsToContents();
}*/

//begin by Marco Vassura
QColor TimetableViewStudentsTimeHorizontalForm::stringToColor(QString s)
{
	// CRC-24 Based on RFC 2440 Section 6.1
	unsigned long crc = 0xB704CEL;
	int i;
	QChar *data = s.data();
	while (!data->isNull()) {
		crc ^= (data->unicode() & 0xFF) << 16;
		for (i = 0; i < 8; i++) {
			crc <<= 1;
			if (crc & 0x1000000)
				crc ^= 0x1864CFBL;
		}
		data++;
	}
	return QColor::fromRgb((int)(crc>>16), (int)((crc>>8) & 0xFF), (int)(crc & 0xFF));
}
//end by Marco Vassura

void TimetableViewStudentsTimeHorizontalForm::currentItemChanged(QTableWidgetItem* current, QTableWidgetItem* previous)
{
	Q_UNUSED(previous);
	
	detailActivity(current);
}

void TimetableViewStudentsTimeHorizontalForm::detailActivity(QTableWidgetItem* item){
	if(item==NULL){
		detailsTextEdit->setPlainText(QString(""));
		return;
	}

	if(!CachedSchedule::isValid()){
		QMessageBox::warning(this, tr("FET warning"), tr("Timetable not available in view students timetable dialog - please generate a new timetable"));
		return;
	}

	if(item->row()>=usedStudentsList.count() || item->column()>=gt.rules.nDaysPerWeek*gt.rules.nHoursPerDay){
		QMessageBox::warning(this, tr("FET warning"), tr("Timetable not available in view students timetable dialog - please generate a new timetable "
		"or close the timetable view students dialog"));
		return;
	}

	if(gt.rules.nInternalRooms!=gt.rules.roomsList.count()){
		QMessageBox::warning(this, tr("FET warning"), tr("Cannot display the timetable, because you added or removed some rooms. Please regenerate the timetable and then view it"));
		return;
	}
	
	assert(item->row()>=0);
	assert(item->column()>=0);

	
	/*if(gt.rules.nInternalTeachers!=gt.rules.teachersList.count()){
		QMessageBox::warning(this, tr("FET warning"), tr("Cannot display the timetable, because you added or removed some teachers. Please regenerate the timetable and then view it"));
		return;
	}*/

	int d=item->column()/gt.rules.nHoursPerDay;
	int h=item->column()%gt.rules.nHoursPerDay;

	int t=item->row();
	int sbg = getStudentSetInternalIndexFromRow(t);

	if (sbg < 0) {
		QMessageBox::warning(this, tr("FET warning"), tr("The students set is invalid - please close this dialog and open a new view students timetable"));
		return;
	}
	
	QSet<QPair<int, int> > notAvailableDayHour=studentsSetNotAvailableDayHour.value(usedStudentsList.at(t), QSet<QPair<int, int> >());

	/*QSet<QPair<int, int> > notAvailableDayHour;
	QSet<ConstraintStudentsSetNotAvailableTimes*> cs=gt.rules.ssnatHash.value(usedStudentsList.at(t), QSet<ConstraintStudentsSetNotAvailableTimes*>());
	if(!cs.isEmpty()){
		assert(cs.count()==1);
		ConstraintStudentsSetNotAvailableTimes* ctr=*(cs.begin());
		
		for(int i=0; i<ctr->days.count(); i++){
			int d=ctr->days.at(i);
			int h=ctr->hours.at(i);
			notAvailableDayHour.insert(QPair<int,int>(d,h));
		}
	}*/

	/*int teacher=gt.rules.searchTeacher(gt.rules.internalTeachersList[t]->name);
	if(teacher<0){
		QMessageBox::warning(this, tr("FET warning"), tr("The teacher is invalid - please close this dialog and open a new view teachers timetable"));
		return;
	}*/
	QString s = "";
	if(d>=0 && d<gt.rules.nDaysPerWeek && h>=0 && h<gt.rules.nHoursPerDay){
		int ai=CachedSchedule::students_timetable_weekly[sbg][d][h]; //activity index

		bool ok=true;
		if(ai==UNALLOCATED_ACTIVITY){
			ok=false;
		}
		else{
			if(!gt.rules.internalActivitiesList[ai].studentsNames.contains(usedStudentsList.at(t))){
				ok=false;
			}
		}
		
		//Activity* act=gt.rules.activitiesList.at(ai);
		if(ok){
			const Activity* act=&gt.rules.internalActivitiesList[ai];
			assert(act!=NULL);
			//s += act->getDetailedDescriptionWithConstraints(gt.rules);
			s += act->getDetailedDescription();

			//int r=rooms_timetable_weekly[teacher][k][j];
			int r=CachedSchedule::getCachedSolution().room(ai);
			if(r!=UNALLOCATED_SPACE && r!=UNSPECIFIED_ROOM){
				s+="\n";
				s+=tr("Room: %1").arg(gt.rules.internalRoomsList[r]->name);
				if(gt.rules.internalRoomsList[r]->building!=""){
					s+="\n";
					s+=tr("Building=%1").arg(gt.rules.internalRoomsList[r]->building);
				}
				s+="\n";
				s+=tr("Capacity=%1").arg(gt.rules.internalRoomsList[r]->capacity);
			}

			s+=LockUnlock::getActivityLockDetailsString(act->id);
		}
		else{
			//if(subgroupNotAvailableDayHour[sbg][d][h]){
			if(notAvailableDayHour.contains(QPair<int,int>(d,h))){
				s+=tr("Students set is not available 100% in this slot");
				s+="\n";
			}
			if(breakDayHour[d][h]){
				s+=tr("Break with weight 100% in this slot");
				s+="\n";
			}
		}
	}
	detailsTextEdit->setPlainText(s);
}

void TimetableViewStudentsTimeHorizontalForm::lockTime()
{
	this->lock(true, false);
}
	
void TimetableViewStudentsTimeHorizontalForm::lockSpace()
{
	this->lock(false, true);
}

void TimetableViewStudentsTimeHorizontalForm::lockTimeSpace()
{
	this->lock(true, true);
}
			
void TimetableViewStudentsTimeHorizontalForm::lock(bool lockTime, bool lockSpace)
{
	if(simulation_running){
		QMessageBox::information(this, tr("FET information"),
			tr("Allocation in course.\nPlease stop simulation before this."));
		return;
	}

	if(!CachedSchedule::isValid()){
		QMessageBox::warning(this, tr("FET warning"), tr("Timetable not available in view students timetable dialog - please generate a new timetable"));
		return;
	}

	if(gt.rules.nInternalRooms!=gt.rules.roomsList.count()){
		QMessageBox::warning(this, tr("FET warning"), tr("Cannot display the timetable, because you added or removed some rooms. Please regenerate the timetable and then view it"));
		return;
	}

	const Solution* tc=&CachedSchedule::getCachedSolution();
	
	bool report=false; //the messages are annoying
	ErrorList errors;
	
	int addedT=0, unlockedT=0;
	int addedS=0, unlockedS=0;
	
	QSet<int> dummyActivitiesColumn; //Dummy activities (no students) column to be considered, because the whole column is selected.
	for(int col=0; col < studentsTimetableTable->columnCount(); col++) {
		bool wholeColumn=true;
		for (int row=0; row < studentsTimetableTable->rowCount(); row++) {
			if(!studentsTimetableTable->item(row, col)->isSelected()){
				wholeColumn=false;
				break;
			}
		}
		if(wholeColumn) {
			int d = col / gt.rules.nHoursPerDay;
			int h = col % gt.rules.nHoursPerDay;
			int time = d + h * gt.rules.nDaysPerWeek;
			dummyActivitiesColumn.insert(time);
		}
	}
	
	QSet<int> dummyActivities;
	for(int ai=0; ai<gt.rules.nInternalActivities; ai++){
		if(gt.rules.internalActivitiesList[ai].iSubgroupsList.count()==0){
			if(tc->time(ai)!=UNALLOCATED_TIME){
					if(dummyActivitiesColumn.contains(tc->time(ai)))
						dummyActivities.insert(ai);
			}
		}
	}

	QSet<int> realActivities;
	for (const QTableWidgetItem* item : studentsTimetableTable->selectedItems()) {
		int t = item->row();
		assert(t<usedStudentsList.count());

		int sbg = getStudentSetInternalIndexFromRow(t);
		if (sbg < 0)
			continue;

		int d = item->column() / gt.rules.nHoursPerDay;
		int h = item->column() % gt.rules.nHoursPerDay;
		int ai=CachedSchedule::students_timetable_weekly[sbg][d][h];

		if(ai==UNALLOCATED_ACTIVITY)
			continue;
		if(!gt.rules.internalActivitiesList[ai].studentsNames.contains(usedStudentsList.at(t)))
			continue;

		realActivities.insert(ai);
	}

	QSet<int> allSelectedActivities(realActivities);
	allSelectedActivities.unite(dummyActivities);

	for (int ai : qAsConst(allSelectedActivities)) {
			assert(tc->time(ai)!=UNALLOCATED_TIME);
			int day=tc->day(ai, gt.rules);
			int hour=tc->hour(ai, gt.rules);

			const Activity* act=&gt.rules.internalActivitiesList[ai];
			
			if(lockTime){
				bool lock = !LockUnlock::isActivityTimeLocked(act->id) && (lockRadioButton->isChecked() || toggleRadioButton->isChecked());
				if(lock){
					TimeConstraint* ctr = LockUnlock::lockTime(&gt.rules, act->id, day, hour);
					if (ctr != NULL) {
						errors << ErrorCode(ErrorCode::Info, tr("Added the following constraint:")+"\n"+ctr->getDetailedDescription(gt.rules));
						addedT++;
					}
					else{
						errors << ErrorCode(ErrorCode::Warning, tr("You may have a problem, because FET expected to add 1 constraint, but this is not possible. "
						 "Please report possible bug"));
					}
				}
				else{
					int nUnlocked = 0;
					errors << LockUnlock::unlockTime(&gt.rules, act->id, nUnlocked);
					unlockedT += nUnlocked;
				}
				if (errors.hasFatal())
					break;
			}
			
			int ri=tc->room(ai);
			if(ri!=UNALLOCATED_SPACE && ri!=UNSPECIFIED_ROOM && lockSpace){
				bool lock = !LockUnlock::isActivitySpaceLocked(act->id) && (lockRadioButton->isChecked() || toggleRadioButton->isChecked());

				if(lock){
					SpaceConstraint* ctr = LockUnlock::lockSpace(&gt.rules, act->id, gt.rules.internalRoomsList[ri]->name);
					if (ctr != NULL) {
						errors << ErrorCode(ErrorCode::Info, tr("Added the following constraint:")+"\n"+ctr->getDetailedDescription(gt.rules));
						addedS++;
					}
					else{
						errors << ErrorCode(ErrorCode::Warning, tr("You may have a problem, because FET expected to add 1 constraint, but this is not possible. "
						 "Please report possible bug"));
					}
				}
				else{
					int nUnlocked = 0;
					errors << LockUnlock::unlockSpace(&gt.rules, act->id, nUnlocked);
					unlockedS += nUnlocked;
				}
				if (errors.hasFatal())
					break;
			}
	}
	ErrorRenderer::renderErrorList(this, errors, report ? ErrorCode::Verbose : ErrorCode::Warning);

	QStringList added;
	QStringList removed;
	if(addedT>0){
		if(FET_LANGUAGE=="en_US"){
			if(addedT==1)
				added << QString("Added 1 locking time constraint.");
			else
				added << QString("Added %1 locking time constraints.").arg(addedT);
		} else {
			added << QCoreApplication::translate("TimetableViewForm", "Added %n locking time constraint(s).",
			 "See http://doc.qt.io/qt-5/i18n-plural-rules.html for advice on how to correctly translate this field."
			 "Also, see http://doc.qt.io/qt-5/i18n-source-translation.html, section 'Handling Plurals'."
			 "You have two examples on how to translate this field in fet_en_GB.ts and in fet_ro.ts"
			 "(open these files with Qt Linguist and see the translation of this field).",
#if QT_VERSION < 0x050000
			 QCoreApplication::CodecForTr,
#endif
			 addedT);
		}
	}
	if(addedS>0){
		if(FET_LANGUAGE=="en_US"){
			if(addedS==1)
				added << QString("Added 1 locking space constraint.");
			else
				added << QString("Added %1 locking space constraints.").arg(addedS);
		} else {
			added << QCoreApplication::translate("TimetableViewForm", "Added %n locking space constraint(s).",
			 "See http://doc.qt.io/qt-5/i18n-plural-rules.html for advice on how to correctly translate this field."
			 "Also, see http://doc.qt.io/qt-5/i18n-source-translation.html, section 'Handling Plurals'."
			 "You have two examples on how to translate this field in fet_en_GB.ts and in fet_ro.ts"
			 "(open these files with Qt Linguist and see the translation of this field).",
#if QT_VERSION < 0x050000
			 QCoreApplication::CodecForTr,
#endif
			 addedS);
		}
	}
	if(unlockedT>0){
		if(FET_LANGUAGE=="en_US"){
			if(unlockedT==1)
				removed << QString("Removed 1 locking time constraint.");
			else
				removed << QString("Removed %1 locking time constraints.").arg(unlockedT);
		} else {
			removed << QCoreApplication::translate("TimetableViewForm", "Removed %n locking time constraint(s).",
			 "See http://doc.qt.io/qt-5/i18n-plural-rules.html for advice on how to correctly translate this field."
			 "Also, see http://doc.qt.io/qt-5/i18n-source-translation.html, section 'Handling Plurals'."
			 "You have two examples on how to translate this field in fet_en_GB.ts and in fet_ro.ts"
			 "(open these files with Qt Linguist and see the translation of this field).",
#if QT_VERSION < 0x050000
			 QCoreApplication::CodecForTr,
#endif
			 unlockedT);
		}
	}
	if(unlockedS>0){
		if(FET_LANGUAGE=="en_US"){
			if(unlockedS==1)
				removed << QString("Removed 1 locking space constraint.");
			else
				removed << QString("Removed %1 locking space constraints.").arg(unlockedS);
		} else {
			removed << QCoreApplication::translate("TimetableViewForm", "Removed %n locking space constraint(s).",
			 "See http://doc.qt.io/qt-5/i18n-plural-rules.html for advice on how to correctly translate this field."
			 "Also, see http://doc.qt.io/qt-5/i18n-source-translation.html, section 'Handling Plurals'."
			 "You have two examples on how to translate this field in fet_en_GB.ts and in fet_ro.ts"
			 "(open these files with Qt Linguist and see the translation of this field).",
#if QT_VERSION < 0x050000
			 QCoreApplication::CodecForTr,
#endif
			 unlockedS);
		}
	}
	QStringList all;
	if(!added.isEmpty())
		all<<added.join("\n");
	if(!removed.isEmpty())
		all<<removed.join("\n");
	QString s=all.join("\n\n");
	if(s.isEmpty())
		s=QCoreApplication::translate("TimetableViewForm", "No locking constraints added or removed.");
	QMessageBox::information(this, tr("FET information"), s);

	LockUnlock::assertIsUpdated(&gt.rules);

	LockUnlock::increaseCommunicationSpinBox();
}

void TimetableViewStudentsTimeHorizontalForm::widthSpinBoxValueChanged()
{
	if(widthSpinBox->value()==MINIMUM_WIDTH_SPIN_BOX_VALUE)
		studentsTimetableTable->horizontalHeader()->setDefaultSectionSize(2*initialRecommendedHeight);
	else
		studentsTimetableTable->horizontalHeader()->setDefaultSectionSize(widthSpinBox->value());
}

void TimetableViewStudentsTimeHorizontalForm::heightSpinBoxValueChanged()
{
	if(heightSpinBox->value()==MINIMUM_HEIGHT_SPIN_BOX_VALUE)
		studentsTimetableTable->verticalHeader()->setDefaultSectionSize(initialRecommendedHeight);
	else
		studentsTimetableTable->verticalHeader()->setDefaultSectionSize(heightSpinBox->value());
}

void TimetableViewStudentsTimeHorizontalForm::help()
{
	QString s="";
	//s+=QCoreApplication::translate("TimetableViewForm", "You can drag sections to increase/decrease them.");
	//s+="\n\n";
	s+=QCoreApplication::translate("TimetableViewForm", "Lock/unlock: you can select one or more activities in the table and toggle lock/unlock in time, space or both.");
	s+=" ";
	s+=QCoreApplication::translate("TimetableViewForm", "There will be added or removed locking constraints for the selected activities (they can be unlocked only if they are not permanently locked).");
	s+="\n\n";
	s+=QCoreApplication::translate("TimetableViewForm", "Locking time constraints are constraints of type activity preferred starting time. Locking space constraints are constraints of type"
		" activity preferred room. You can see these constraints in the corresponding constraints dialogs. New locking constraints are added at the end of the list of constraints.");
	s+="\n\n";
	s+=QCoreApplication::translate("TimetableViewForm", "If a cell is (permanently) locked in time or space, it contains abbreviations to show that: PLT (permanently locked time), LT (locked time), "
		"PLS (permanently locked space) or LS (locked space).", "Translate the abbreviations also. Make sure the abbreviations in your language are different between themselves "
		"and the user can differentiate easily between them. These abbreviations may appear also in other places, please use the same abbreviations.");
	
	s+="\n\n";
	s+=tr("If a whole column (day+hour) is selected, there will be locked/unlocked also the dummy activities (activities with no students sets) from that column.");
	
	s+="\n\n";
	s+=tr("A bold font cell means that the activity is locked in time, either permanently or not.");
	s+=" ";
	s+=tr("An italic font cell means that the activity is locked in space, either permanently or not.");

	LongTextMessageBox::largeInformation(this, tr("FET help"), s);
}

int TimetableViewStudentsTimeHorizontalForm::getStudentSetInternalIndexFromRow(int row)
{
	int sbg=-1;

	if(!gt.rules.studentsHash.contains(usedStudentsList.at(row))){
		return -1;
	}
	assert(gt.rules.studentsHash.contains(usedStudentsList.at(row)));
	StudentsSet* ss=gt.rules.studentsHash.value(usedStudentsList.at(row), NULL);
	assert(ss!=NULL);
	if(ss->type==STUDENTS_YEAR){
		StudentsYear* year=(StudentsYear*)ss;
		sbg=year->groupsList.at(0)->subgroupsList.at(0)->indexInInternalSubgroupsList;
	}
	else if(ss->type==STUDENTS_GROUP){
		StudentsGroup* group=(StudentsGroup*)ss;
		sbg=group->subgroupsList.at(0)->indexInInternalSubgroupsList;
	}
	else if(ss->type==STUDENTS_SUBGROUP){
		StudentsSubgroup* subgroup=(StudentsSubgroup*)ss;
		sbg=subgroup->indexInInternalSubgroupsList;
	}
	else{
		assert(0);
	}

	assert(sbg>=0 && sbg<gt.rules.nInternalSubgroups);
	return sbg;
}
