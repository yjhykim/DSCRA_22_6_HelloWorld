#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

static vector<string> split(const string& data, const char delimiter = ' ') {
	vector<string> result;
	string token;
	stringstream ss(data);

	while (getline(ss, token, delimiter)) result.push_back(token);

	return result;
}
