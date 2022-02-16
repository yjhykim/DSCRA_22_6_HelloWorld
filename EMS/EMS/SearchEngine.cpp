#include "SearchEngine.h"

list<Employee*> SearchEngine::search(list<Employee>& db, int employeeNum) const
{
	list<Employee*> result;

	for (auto& item : db) {
		if (item.employeeNum != employeeNum) continue;
		result.emplace_back(&item);
	}
	return result;
}

list<Employee*> SearchEngine::search(list<Employee>& db, Name& name) const
{
	list<Employee*> result;

	for (auto& item : db) {
		if (name.first != "" && name.first != item.name.first) continue;
		if (name.last != "" && name.last != item.name.last) continue;

		result.emplace_back(&item);
	}

	return result;
}

list<Employee*> SearchEngine::search(list<Employee>& db, CL cl) const
{
	list<Employee*> result;

	for (auto& item : db) {
		if (item.cl != cl) continue;
		result.emplace_back(&item);
	}

	return result;
}

list<Employee*> SearchEngine::search(list<Employee>& db, PhoneNum& phoneNum) const
{
	list<Employee*> result;

	for (auto& item : db) {
		if (phoneNum.mid != -1 && phoneNum.mid != item.phoneNum.mid) continue;
		if (phoneNum.last != -1 && phoneNum.last != item.phoneNum.last) continue;

		result.emplace_back(&item);
	}

	return result;
}

list<Employee*> SearchEngine::search(list<Employee>& db, Birthday& birthDay) const
{
	list<Employee*> result;

	for (auto& item : db) {
		if (birthDay.year != -1 && birthDay.year != item.birthDay.year) continue;
		if (birthDay.month != -1 && birthDay.month != item.birthDay.month) continue;
		if (birthDay.day != -1 && birthDay.day != item.birthDay.day) continue;

		result.emplace_back(&item);
	}

	return result;
}

list<Employee*> SearchEngine::search(list<Employee>& db, CERTI certi) const
{
	list<Employee*> result;

	for (auto& item : db) {
		if (certi != item.certi) continue;
		result.emplace_back(&item);
	}

	return result;
}