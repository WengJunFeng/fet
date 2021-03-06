#include "maxdaysbetweenactivities.h"

#include "generate_pre.h"

MaxDaysBetweenActivities::MaxDaysBetweenActivities()
{

}

bool MaxDaysBetweenActivities::prepare(const Rules &rules)
{
	activities.resize(rules.nInternalActivities);
	maxDays.resize(rules.nInternalActivities);
	weightPercentages.resize(rules.nInternalActivities);

	int errorGroupId = ErrorCode::nextGroupId();
	errors.clear();

	bool ok=true;

	for(int j=0; j<rules.nInternalActivities; j++){
		activities[j].clear();
		maxDays[j].clear();
		weightPercentages[j].clear();
	}

	QSet<const ConstraintMaxDaysBetweenActivities*> mdset;

	for(int i=0; i<rules.nInternalTimeConstraints; i++)
		if(rules.internalTimeConstraintsList[i]->type==CONSTRAINT_MAX_DAYS_BETWEEN_ACTIVITIES){
			const ConstraintMaxDaysBetweenActivities* md=
			 (const ConstraintMaxDaysBetweenActivities*)rules.internalTimeConstraintsList[i];

			for(int j=0; j<md->_n_activities; j++){
				int ai1=md->_activities[j];
				for(int k=0; k<md->_n_activities; k++)
					if(j!=k){
						int ai2=md->_activities[k];
						if(ai1==ai2){
							ok=false;

							if(!mdset.contains(md)){
								mdset.insert(md);

								errors.append(ErrorCode(ErrorCode::Error,
											GeneratePreTranslate::tr("Cannot optimize, because you have a constraint max days between activities with duplicate activities. The constraint "
											"is: %1. Please correct that.").arg(md->getDetailedDescription(rules)), errorGroupId)
											);
								continue;
							}
						}
						int m=md->maxDays;

						activities[ai1].append(ai2);
						maxDays[ai1].append(m);
						assert(md->weightPercentage >=0 && md->weightPercentage<=100);
						weightPercentages[ai1].append(md->weightPercentage);
					}
			}
		}

	return ok;
}
