#include <iostream>
#include <string>
#include <map>
using namespace std;

class DateConverter {
public:
	DateConverter() {
		str2Month["January"] = 1;	str2Month["February"] = 2;	str2Month["March"] = 3; // map name of months from string to int
		str2Month["April"] = 4;		str2Month["May"] = 5;		str2Month["June"] = 6;
		str2Month["July"] = 7;		str2Month["August"] = 8;	str2Month["September"] = 9;
		str2Month["October"] = 10;	str2Month["November"] = 11;	str2Month["December"] = 12;

		monthToDays[1] = 31;		monthToDays[2] = 28;		monthToDays[3] = 31; // map month number to day number
		monthToDays[4] = 30;		monthToDays[5] = 31;		monthToDays[6] = 30;
		monthToDays[7] = 31;		monthToDays[8] = 31;		monthToDays[9] = 30;
		monthToDays[10] = 31;		monthToDays[11] = 30;		monthToDays[12] = 31;
	}
	bool convert(const string &date, int &month, int &day, int &year, string &format) const {

		int chopper;
		chopper = date.find(' ');
		day = stoi(date.substr(chopper, date.find(','))); // find day
		map<string, int>::const_iterator myIt;
		myIt = str2Month.find(date.substr(0, chopper));
		chopper = date.find(',');

		int yrLen = date.substr(chopper + 1).length() - 1; // make sure the input year is 2 or 4 digits
		if (yrLen == 3 || yrLen == 1 || yrLen > 4)	return false;

		year = stoi(date.substr(chopper + 1)); // find the year
		if (myIt == str2Month.end())	return false; // see if the word matches to a numbered month
		month = myIt->second; // if so, set it to that number
		
		map<int, int>::const_iterator myIntIt; 
		myIntIt = monthToDays.find(month); // get the mapped number of days for a month

		if (month == 2 && year % 4 == 0) { // leap year has an extra day
			if (day > myIntIt->second + 1)	return false;
		}
		else if (day > myIntIt->second)	return false; // make sure it's a valid day

		if (month < 10)	format = "0"; // pad  lower months and days with 0
		format += (to_string(month) + "/");
		if (day < 10)	format += "0";
		format += (to_string(day) + "/");

		if (year < 1000) { 
			format += "20"; // no millenia  given, so add it
			if (year < 10) 
				format += "0";
		}
		format += to_string(year); // put the rest of the year in the string
		return true;
	}

private:
	map<string, int> str2Month; // maps a string to a numeric month
	map<int, int> monthToDays; // maps a numeric month to a number of days

};

void test(const DateConverter &dc, const string &str) {
	int m, d, y;
	string out;
	bool ret;
	ret = dc.convert(str, m, d, y, out);
	if (ret) cout << str << ":  out=" << out << ", m=" << m << ", d=" << d << ", y=" << y << endl;
	else cout << str << ":  is invalid\n";
}

void main() {
	DateConverter dc;
	test(dc, "January 5, 2004");
	test(dc, "December 15, 09");
	test(dc, "adfadsf 1, 2004");
	test(dc, "January 32, 2005");
	test(dc, "February 29, 2004");
	test(dc, "February 29, 2005");
	test(dc, "January 3, 1888");
	test(dc, "January 3, 188");
}