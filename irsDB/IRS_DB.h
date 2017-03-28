#ifndef IRSDB
#define IRSDB

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class IRS_DB {
public:
	struct W2 {
		int id;
		double salary;
	};

	struct person {
		vector<W2> myW2s;
		string name;
		int ssn;
	};

	~IRS_DB();
	bool empty() const { return ssnMap.empty(); }  //returns true iff there are no Person entries
	int sizePerson() const { return ssnMap.size(); }  //returns number of people
	int sizeCompany() const { return companyNames.size(); } //returns number of companies
	void print() const; //prints out all person data, details below

	bool getInfo(int ssn, string &name, vector<W2> &w2s) const;
	//if ssn exists then sets name and w2s to that persons data and returns true, else returns false
	bool getCompnayName(int id, string &name) const;//if company id exists set name to its name and return true, else return false

	bool findSSN(const string &name, vector<int> &ids) const;//return false if name isn't a person
															 //else sets ids to be vector of all ssns that have name and returns true
															 //more than one person can have the same name
	bool getTotalSalary(int ssn, double &salary) const; //if ssn exists then
														//set salary = sum of all W2s for ssn and return true else return false

	bool insert(int ssn, const string &name);//insert person with ssn and name, return false if ssn already present
	bool insertCompany(int id, const string &name);//insert company with id and name, return false if id already present

	bool addW2(int ssn, const W2 &w2Info);//add a W2 form for ssn, return false if ssn doesn't exist, w2Info.id doesn't exist, or ssn already has a w2 for w2Info.id
	bool updateW2(int ssn, const W2 &w2info);//return true iff ssn exists and w2info.id is already a w2 of ssn and update salary
	bool removeW2(int ssn, int id); //remove W2 with id from person ssn, return true iff ssn exists and has a W2 with that id 

	bool removePerson(int ssn);  //delete ssn from database, return true iff ssn exist, make sure findSSN(name) no longer lists ssn for name

	bool changeName(int ssn, const string &name); //change name of person to name, return true iff ssn exists, make sure findSSN(name) no longer lists ssn for name
	//bool removeCompany(int id);  //Bonus, remove company from database, remove all W2s that reference it, return true iff id exists

	void testMaps() {
		map<int, person*>::iterator myIt = ssnMap.begin();
		while (myIt != ssnMap.end()) {
			cout << myIt->second->name << " ";
			myIt++;
		}
		cout << endl;
		cout << "ssn's" << endl;
		multimap<string, person*>::iterator mIt = nameMap.begin();
		while (mIt != nameMap.end()) {
			cout << mIt->second->name << " ";
			mIt++;
		}
		cout << endl;
	}

private:
	map<int, person*> ssnMap; // map people by social
	map<int, string> companyNames; // map companies by ID
	multimap<string, person*> nameMap;
};

#endif