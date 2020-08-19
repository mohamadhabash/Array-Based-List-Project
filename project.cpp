#include<iostream>
#include<string>
using namespace std;
struct record {
	int id;
	string firstname;
	string lastname;
	char grade;
};
class Students {
	int length;
	record* Record;
	int maxSize;
public:
	Students(int size) {
		length = 0;
		(size > 0) ? maxSize = size : maxSize = 100;
		Record = new record[maxSize];
	}
	~Students() {
		delete[] Record;
	}
	int getMaxSize() {
		return maxSize;
	}
	void increaseLength() { 
		length++; 
	}
	void decreaseLength() { 
		length--; 
	}
	int getLength() { 
		return length;
	}
	record getRecord(int i) { 
		return Record[i];
	}
	void setRecord(int i,record r) {
		Record[i] = r;
	}
};
int Search(Students &s, int id) {
	for (int i = 0; i < s.getLength(); i++) {
		if (id == s.getRecord(i).id)
			return i;
	}
	return -1;
}
bool noDuplicate(Students &s,record r) {
	int flag = Search(s, r.id);
	if (flag == -1) {
		return true;
	}
	return false;
}
void insertSorted(Students &s,record r) {
	if (noDuplicate(s,r)) {
		int loc = 0;
		for (int i = 0; i < s.getLength(); i++) {
			if (r.id > s.getRecord(i).id) {
				loc++;
			}
		}
		for (int i = s.getLength(); i > loc; i--) {
			s.setRecord(i, s.getRecord(i - 1));
		}
		s.setRecord(loc,r);
		s.increaseLength();
	}
	else {
		cout << "Student already exists\n";
	}
}
void Insert(Students &s,record r) {
	if (s.getLength() == s.getMaxSize()) {
		cout << "list if full\n";
	}
	else if (s.getLength() == 0) { 
		s.setRecord(s.getLength(), r);
		s.increaseLength();
	}
	else {
		insertSorted(s, r);
	}
}
void Delete(Students &s,int id) {
	int loc = Search(s, id);
	if (loc == -1) {
		cout << "Student with This id number is not found" << endl;
	}
	else if(loc == s.getLength()) {
		s.decreaseLength(); 
	}
	else {
		for (int i = loc; i < s.getLength() - 1; i++) {
			s.setRecord(i, s.getRecord(i + 1));
		}
		s.decreaseLength();
	} }
void Retrieve(Students &s,int id) {
	for (int i = 0; i < s.getLength(); i++) {
		if (id == s.getRecord(i).id) {
			cout << "Information of the Student with this ID : " << endl;
			cout << "Student Name : " << s.getRecord(i).firstname << " " << s.getRecord(i).lastname << endl;
			cout << "Student Grade : " << s.getRecord(i).grade << endl;
		}
	}
}
void Print(Students &s) {
	cout << "\nThe records of the Students : " << endl;
	for (int i = 0; i < s.getLength(); i++) {
		cout << "Student ID : " << s.getRecord(i).id << endl;
		cout << "Student Name : " << s.getRecord(i).firstname << " " << s.getRecord(i).lastname << endl;
		cout << "Student Grade : " << s.getRecord(i).grade << endl;
		cout << "------------------------------------------------" << endl;
	}
}
int main() {
	Students s(30);
	record r1 = { 111111,"Feras","Mohammed",'A'}
	, r2 = { 111112,"Suhaib","Mohammed",'A' }
	, r3 = {111113,"Yahya","Mohammed",'B'}
	, r4 = {111114,"Mohammed","Ahmed",'D'};
	Insert(s, r1);
	Insert(s, r2);
	Insert(s, r3);
	Insert(s, r4);
	Delete(s, 111112);
	record r5 ={132801,"Mohammed","Habash",'A'}//this is me
		, r6={111115,"Mahmoud","Hasan",'C'}
	, r7 = { 111116,"Hasan","Hosni",'B' };
	Insert(s, r5);
	Insert(s, r6);
	Insert(s, r7);
	Delete(s, 123456); //this does not exist
	cout << "Location of Student with ID 132801 : " << Search(s, 132801) << endl;
	Retrieve(s, 132801);
	Print(s);
	return 0;
}
