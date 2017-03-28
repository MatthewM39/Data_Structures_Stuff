#include <iostream>
#include <string>
using namespace std;

/* Time class with operator overloads for comparison, <<, and + int

The overload << for cout should print  hour:min
where hour and min are the current values including the : but no spaces or endl.
Should you pad them to print two digits wide so there are always 5 output characters.
Military time so 00:00 through 23:59 are the valid Times.
Eg.
Time t1 (10,17);
cout <<t1;  //should print exactly 5 characters: 10:17
Time t2 (5,7);
cout <<t2;  //should print exactly 5 characters: 05:07

The overload >> for cin should read two integers, the first as the hour the second the minute.

Addition of 2 Times t1 and t2 where t1 is hour1:min1 and t2 is hour2:min2 is defined as
(hour1+hour2):(min1+min2)
with the caveat that the result should be a valid time meaning you need to deal with crossing 60
and hours crossing 24

An integer i + a Time hour1:min1 is defined as  hour1, time1+i
so the integer is added to minutes, again watch the wrapping

Two times are == if they have the same hour and min values

t1 < t2 when hour1 < hour2 or hour1==hour2 and min1 < min2.  So compare hour first, then min.

You may add additional public methods as needed to Time.  You will also need
to add functions outside the class.

You should implement overloads for all 6 comparisons == != < <= > >=
Only == and < should have any mention of hour and min
(as we did inclass the other overloads should use == and < intelligently)
The other overloads must have exactly 1 and only 1 call to either == or <, but not both.
They shouldn't use the other overloaded comparisons.
*/

void fixTime(int &h, int &m) { // compatible with adding large amounts of minutes
	while (m > 59) { // while more than 59 minutes
		m = m - 60; // subtract 60 each time
		h++; // add an hour
	}
	if (h > 23)
		h = h % 24; // time exceeds 23, so mod by 24
}

class Time {
public:
	Time(int h, int m) :hour(h), min(m) {}
	Time(int m) : hour(0), min(m) {}
	int getHour() const { return hour; }
	int getMin() const { return min; }
	void setMin(int m) { min = m; }
	void setHour(int h) { hour = h; }

	bool operator== (const Time &right) const {
		if (hour == right.getHour() && min == right.getMin())
			return true;
		return false;
	}

	bool operator< (const Time &right) const {
		if (hour < right.getHour() || (hour <= right.getHour() && min < right.getMin()))
			return true;
		return false;
	}

	bool operator!= (const Time &right) const {
		return !(*this == right);
	}

	bool operator>= (const Time &right) const {
		return !(*this < right);
	}

	bool operator<= (const Time &right) const {
		return !(right < *this);
	}

	bool operator> (const Time &right) const {
		return (right < *this);
	}

	Time operator+ (const Time &right) {
		hour = hour + right.getHour();
		min = min + right.getMin();
		fixTime(hour, min);
		return *this;
	}

	Time operator+(int mins)
	{
		min = min + mins;
		fixTime(hour, min);
		return *this;
	}
private:
	int hour, min;
};

Time operator+(int i, Time &t) {
	int min = t.getMin() + i;
	int hr = t.getHour();
	fixTime(hr, min);
	t.setHour(hr);
	t.setMin(min);
	return t;
}


ostream & operator<<(ostream & out, const Time &time) {
	int m = time.getMin();
	int h = time.getHour();
	if (h < 10)
		out << 0;
	out << h << ":";
	if (m < 10)
		out << 0;
	out << m;
	return out;	//must have this
}

istream & operator>>(istream & in,  Time &time) {
	int h;
	int m;
	in >> h;
	in >> m;
	fixTime(h, m);
	time.setHour(h);
	time.setMin(m);
	return in;	//must have this
} 


void compare(const Time &lhs, const Time &rhs) {//just saves some space and typing for my tests
	if (lhs < rhs) cout << "less\n";
	else if (lhs == rhs) cout << "equal\n";
	else if (lhs > rhs) cout << "greater\n";
}

void compare2(const Time &lhs, const Time &rhs) {//just saves some space and typing for my tests
	if (lhs != rhs) cout << "not equal and  ";
	else cout << "equal and ";

	if (lhs >= rhs) cout << "greater=\n";
	else if (lhs <= rhs) cout << "less=\n";
}
void main() {
	Time current(12, 3), previous(11, 50), later(12, 45), later2(12, 45);
	cout << current << endl;  //12:03
	cout << later << endl;	  //12:45
	cout << previous << endl; //11:50
	cout << endl;
	compare(current, later);
	compare(current, previous);
	compare(later, current);
	compare(previous, current);
	cout << endl;

	compare(later, later2);
	compare2(later, later2);
	compare2(previous, current);
	compare2(later, current);

	cout << endl;

	current = current + 240;
	cout << current << endl;//12:43
	current = 20 + current;
	cout << current << endl;//13:03
	current = current + previous;
	cout << current << endl;//00:53

	cin >> current;
	cout << current << endl;//00:53
}