#include "SearchEngine.h"

list<Employee*> SearchEngine::search(map<int, Employee>& db, int employeeNum) const {
	list<Employee*> result;

	auto item = db.find(employeeNum);
	if (item != db.end())
		result.emplace_back(&(item->second));
	return result;
}

list<Employee*> SearchEngine::search(map<int, Employee>& db, Name& name) const {
	list<Employee*> result;

	for (auto& item : db) {
		if (name.first != "" && name.first != item.second.name.first) continue;
		if (name.last != "" && name.last != item.second.name.last) continue;

		result.emplace_back(&item.second);
	}

	return result;
}

list<Employee*> SearchEngine::search(map<int, Employee>& db, CL cl) const {
	list<Employee*> result;

	for (auto& item : db) {
		if (item.second.cl != cl) continue;
		result.emplace_back(&item.second);
	}

	return result;
}

list<Employee*> SearchEngine::search(map<int, Employee>& db, PhoneNum& phoneNum) const {
	list<Employee*> result;

	for (auto& item : db) {
		if (phoneNum.mid != -1 && phoneNum.mid != item.second.phoneNum.mid) continue;
		if (phoneNum.last != -1 && phoneNum.last != item.second.phoneNum.last) continue;

		result.emplace_back(&item.second);
	}

	return result;
}

list<Employee*> SearchEngine::search(map<int, Employee>& db, Birthday& birthDay) const {
	list<Employee*> result;

	for (auto& item : db) {
		if (birthDay.year != -1 && birthDay.year != item.second.birthDay.year) continue;
		if (birthDay.month != -1 && birthDay.month != item.second.birthDay.month) continue;
		if (birthDay.day != -1 && birthDay.day != item.second.birthDay.day) continue;

		result.emplace_back(&item.second);
	}

	return result;
}

list<Employee*> SearchEngine::search(map<int, Employee>& db, CERTI certi) const {
	list<Employee*> result;

	for (auto& item : db) {
		if (certi != item.second.certi) continue;
		result.emplace_back(&item.second);
	}

	return result;
}