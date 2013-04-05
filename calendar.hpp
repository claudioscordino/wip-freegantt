#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include<QDate>
#include<vector>

class Calendar
{
public:
	Calendar(){}
	~Calendar();

	inline bool addDate(const QDate& date){
		return addDate(date, "");
	}

	bool addDate(const QDate& date, const std::string& name);

	bool removeDate(const QDate& date);

	bool checkDate(const QDate& date);

private:
	struct Date {
		std::string name_;
		QDate date_;
	};

	std::vector<Date*> dates_;
};

#endif // CALENDAR_HPP
