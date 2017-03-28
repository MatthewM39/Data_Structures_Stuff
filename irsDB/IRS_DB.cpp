#include "IRS_DB.h"

ostream & operator<<(ostream & out, const IRS_DB::W2 &myW2) {
	out << myW2.id << " " << myW2.salary; // output the id and salary
	return out;	
}

IRS_DB::~IRS_DB()
{
	map<int, person*>::iterator myItr = ssnMap.begin(); // iterate through mapped values
	while (myItr != ssnMap.end()) {
		person * temp = myItr->second; // create a temporary person pointer
		myItr++;
		delete temp; // nuke the person
	}
}

void IRS_DB::print() const
{
	map<int, person*>::const_iterator myIt = ssnMap.begin();
	while (myIt != ssnMap.end()) { //iterate through
		cout << myIt->first << ": " << myIt->second->name; // output the social and name
		vector<W2>::const_iterator wIt = myIt->second->myW2s.begin(); // iterate through one's w2s
		while (wIt != myIt->second->myW2s.end()) {
			cout << ",(" << *wIt << " " << companyNames.find(wIt->id)->second << ")"; // out the w2 and id
			wIt++;
		}
		cout << endl;
		myIt++;
	}
}

bool IRS_DB::getInfo(int ssn, string & name, vector<W2>& w2s) const
{
	map<int, person*>::const_iterator myIt = ssnMap.find(ssn); // make sure ssn is valid
	if(myIt == ssnMap.end())
		return false;
	person * temp = myIt->second; // temp person
	name = temp->name;
	vector<W2>::iterator w2It = temp->myW2s.begin(); // iterate through temp's w2s
	while (w2It != temp->myW2s.end()) {
		w2s.emplace_back(*w2It); // place them in the vector
		w2It++;
	}
	return true;
}

bool IRS_DB::getCompnayName(int id, string & name) const
{
	map<int, string>::const_iterator myIt = companyNames.find(id); // attempt to find a company
	if (myIt == companyNames.end())
		return false;
	name = myIt->second; // set name equal to the company's name
	return true;
}

bool IRS_DB::findSSN(const string & name, vector<int>& ids) const
{
	multimap<string, person*>::const_iterator myBottom = nameMap.lower_bound(name); // lower bound to search through
	if (myBottom == nameMap.end())
		return false;
	multimap<string, person*>::const_iterator myTop = nameMap.upper_bound(name); // upper bound to search
	while (myBottom != myTop) { // navigate through
		ids.emplace_back(myBottom->second->ssn); // emplace the current ssn
		myBottom++;
	}
	return true;
}

bool IRS_DB::getTotalSalary(int ssn, double & salary) const
{
	salary = 0; // need to set to 0 in case it wasnt passed as 0
	map<int, person*>::const_iterator myIt = ssnMap.find(ssn);
	if (myIt == ssnMap.end())
		return false;
	vector<W2>::const_iterator wIt = myIt->second->myW2s.begin();
	while (wIt != myIt->second->myW2s.end()) {
		salary = salary + wIt->salary; // continuously add to salary until out of w2s
		wIt++;
	}
	return true;
}

bool IRS_DB::insert(int ssn, const string & name)
{
	if (ssnMap.find(ssn) != ssnMap.end()) // bail out of ssn is already used
		return false;
	person * temp = new person(); // this new is deleted later
	temp->name = name;
	temp->ssn = ssn;
	ssnMap[ssn] = temp;
	nameMap.insert({name, temp});
	return true;
}

bool IRS_DB::insertCompany(int id, const string & name)
{
	map<int, string>::const_iterator myIt = companyNames.find(id); // only insert when id is unique
	if (myIt == companyNames.end()) {
		companyNames[id] = name;
		return true;
	}
	return false;
}

bool IRS_DB::addW2(int ssn, const W2 & w2Info)
{
	map<int, person*>::iterator myIt = ssnMap.find(ssn); // find a person
	if (myIt == ssnMap.end()) return false;

	vector<W2>::iterator vIt = myIt->second->myW2s.begin(); // make sure they dont have the w2 already and add it
	while (vIt != myIt->second->myW2s.end()) {
		if (vIt->id == w2Info.id)
			return false;
		vIt++;
	}
	myIt->second->myW2s.emplace_back(w2Info);
	return true;
}

bool IRS_DB::updateW2(int ssn, const W2 & w2info)
{
	map<int, person*>::iterator myIt = ssnMap.find(ssn);
	if (myIt == ssnMap.end()) return false;
	vector<W2>::iterator vIt = myIt->second->myW2s.begin();
	while (vIt != myIt->second->myW2s.end()) {
		if (vIt->id == w2info.id) // find the correct w2 and update its salary
			vIt->salary = w2info.salary;
			return true;
		vIt++;
	}
	return false;
}

bool IRS_DB::removeW2(int ssn, int id)
{
	map<int, person*>::iterator myIt = ssnMap.find(ssn);
	if (myIt == ssnMap.end()) return false;
	vector<W2>::iterator vIt = myIt->second->myW2s.begin();
	while (vIt != myIt->second->myW2s.end()) {
		if (vIt->id == id) {
			myIt->second->myW2s.erase(vIt); // find the w2 and erase
			return true;
		}
		vIt++;
	}
	return false;
}

bool IRS_DB::removePerson(int ssn)
{
	map<int, person*>::iterator myIt = ssnMap.find(ssn);
	if (myIt == ssnMap.end()) return false;
	string temp = myIt->second->name;
	ssnMap.erase(myIt); // remove person from the mapped socials to people
	multimap<string, person*>::const_iterator myBottom = nameMap.lower_bound(temp);
	multimap<string, person*>::const_iterator myTop = nameMap.upper_bound(temp);
	while (myBottom != myTop) {

		if (myBottom->second->ssn == ssn) {
			person * nuke = myBottom->second;
			nameMap.erase(myBottom); // remove person from mapped names to people
			delete nuke; // get rid of the new from insertion
			return true;
		}
		myBottom++;
	}
	return true;
}

bool IRS_DB::changeName(int ssn, const string & name)
{
	map<int, person*>::iterator myIt = ssnMap.find(ssn);
	if (myIt == ssnMap.end()) return false;
	string temp = myIt->second->name;
	multimap<string, person*>::const_iterator myBottom = nameMap.lower_bound(temp);
	multimap<string, person*>::const_iterator myTop = nameMap.upper_bound(temp);
	while (myBottom != myTop) {
		if (myBottom->second->ssn == ssn) {
			nameMap.erase(myBottom); // need to erase from name->person map
			myIt->second->name = name; // change name
			nameMap.insert({ name, myIt->second }); // need to insert the new name with the person
			return true;
		}
		myBottom++;
	}
	return true;
}

void main() {

	// begin testing
	IRS_DB myDB;
	vector<int> myV;
	cout << "Inserting 1,2,3,1 BOB should be 111: " << myDB.insert(1, "BOB") << myDB.insert(2, "BOB") << myDB.insert(3, "BOB") << endl;
	cout << "Attempt to insert another 1 BOB should be false: " << myDB.insert(1, "BOB") << endl;
	myDB.removePerson(2);
	myDB.print();
	cout << myDB.insertCompany(1, "SUPER COMPANY");
	cout << myDB.insertCompany(1, "MEGA COMPANY") << endl;
	IRS_DB::W2 temporary;
	temporary.id = 1;
	temporary.salary = 100;
	myDB.addW2(1, temporary);
	myDB.print();
	cout << myDB.removeW2(1, 1) << endl;
	myDB.addW2(1, temporary);
	cout << myDB.sizePerson();
	cout << myDB.sizeCompany();
	string temp;
	myDB.getCompnayName(1, temp);
	cout << endl << temp << endl;
	myDB.insertCompany(2, "MEGA COMPANY");
	temporary.id = 2;
	myDB.addW2(1, temporary);
	double x;
	temporary.salary = 10000;
	temporary.id = 1;
	myDB.updateW2(1, temporary);
	myDB.getTotalSalary(1, x);
	cout << x << endl;
	myDB.print();
}