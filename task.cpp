#include "task.hpp"

int Task::next_id_ = 0;

QDate Task::getEnd()
{
	QDate end = begin_;
	int remaining_days = duration_;
	while (remaining_days > 0){
		end.addDays(1);
		if ((end.dayOfWeek()) < 6 && (stop_days_.checkDate(end) == false))
			remaining_days--;
	}
	return end;
}
