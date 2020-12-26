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
	//Constructor initializes a new record for each new student
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

//Returns location in the list of student with a specific ID, returns -1 if student does not exist
int Search(Students &s, int id) {
	for (int i = 0; i < s.getLength(); i++) {
		if (id == s.getRecord(i).id)
			return i;
	}
	return -1;
}

//Guarantees no two students get the same ID
bool noDuplicate(Students &s,record r) {
	int flag = Search(s, r.id);
	if (flag == -1) {
		return true;
	}
	return false;
}

//Adds a new student to the list and keeping the list sorted by IDs
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

//Removes a student with specific ID from the list
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
	} 
}

//Gets student with specific ID from the list
void Retrieve(Students &s,int id) {
	for (int i = 0; i < s.getLength(); i++) {
		if (id == s.getRecord(i).id) {
			cout << "Information of the Student with this ID : " << endl;
			cout << "Student Name : " << s.getRecord(i).firstname << " " << s.getRecord(i).lastname << endl;
			cout << "Student Grade : " << s.getRecord(i).grade << endl;
		}
	}
}

//Prints records of all students in the list
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
	
	//Declaring Students object with a size of 30 records 
	Students s(30);
	
	//Declaring 4 new records
	record  r1 = { 111111,"Feras", "Mohammed", 'A'},
		r2 = { 111112, "Suhaib", "Mohammed", 'A' },
		r3 = {111113, "Yahya", "Mohammed", 'B'},
		r4 = {111114, "Mohammed", "Ahmed", 'D'};
	
	//Adding 4 students records above to the list 
	Insert(s, r1);
	Insert(s, r2);
	Insert(s, r3);
	Insert(s, r4);
	
	//Removing student with ID 111112 from the list
	Delete(s, 111112);
	
	//Adding 3 more students
	record  r5 ={132801, "Mohammed","Habash", 'A'},
		r6 ={111115, "Mahmoud", "Hasan", 'C'},
	 	r7 = { 111116, "Hasan", "Hosni", 'B'};
	Insert(s, r5);
	Insert(s, r6);
	Insert(s, r7);
	
	
	Delete(s, 123456); //this student ID does not exist, gives a feedback that informs non-existence of student.
	
	cout << "Location of Student with ID 132801 : " << Search(s, 132801) << endl; //Returns student location in the list
	
	Retrieve(s, 132801); //Prints info of student with ID 132801
	
	Print(s); //Prints records of all students in the list
	
	return 0;
}
