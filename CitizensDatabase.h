/*AISHA IRFAN 20I-1851 CY-T*/
#ifndef CITIZENSDB_H
#define CITIZENSDB_H
#include<iostream>
#include <cstring>
#include<fstream>
#include<sstream>
using namespace std;

struct CCID_NODE;
struct CBID_NODE;

template <class T>
struct Data {/*Node for Queue that is used to read .txt files */

	T data;
	Data* next;
	Data()//Default Constructor
	{
		next = NULL;
	}
	Data(T d)//Parameterized Constructor
	{
		data = d;
		next = NULL;
	}
};
template <class T>
class DataPipeline {	//singly linked Queue to get data from .txt files
	Data<T>* head;
	Data<T>* tail;
public:
	DataPipeline() {//Default Constructor
		head = NULL;
		tail = NULL;
	}
	T front() {//returns data at head node
		return head->data;
	}
	T back() {//returns data at tail node
		return tail->data;
	}
	void enqueue(T d) {//adds element at tail
		Data <T>* x = new Data<T>(d);
		if (head == NULL)
		{
			head = x;
			tail = x;
			return;
		}
		tail->next = x;
		tail = x;
	}
	T dequeue() {//deletes node at head and returns value
		Data <T>* temp;
		temp = head;
		T tempD = head->data;
		head = head->next;
		delete temp;
		return tempD;
	}
	bool is_empty() {//checks whether queue is empty
		if (head == NULL)
			return true;
		else
			return false;
	}
	~DataPipeline()//Destuctor
	{
		while (is_empty() == false)
		{
			Data<T>* x;
			x = head;
			head = head->next;
			delete x;
		}
	}
};

struct CBID_NODE {

	int CNIC;
	string name;
	string FatherName;
	string gender;
	string Address;
	string Nationality;
	CBID_NODE* next, * prev;	//doubly linked list
	CCID_NODE* CCIDptr;//points to persons criminal record
	CBID_NODE()//Default Constructor
	{
		next = NULL;
		prev = NULL;
		CCIDptr = NULL;
	}
	CBID_NODE(int cnic, string n, string fname, string G, string addy, string nation)//Parameterized Constructor
	{
		CNIC = cnic;
		name = n;
		FatherName = fname;
		gender = G;
		Address = addy;
		Nationality = nation;
		CCIDptr = NULL;
	}
	string basicsRet()// returns string consisting of CBID data
	{
		string str = name + " " + FatherName + " " + gender + " " + Address + " " + Nationality;
		return str;
	}
};


template <class T>
class CBIDList {
public:
	CBID_NODE node;
	CBID_NODE* head;
	CBID_NODE* tail;
	CBIDList()//Default Constructor
	{
		head = NULL;
		tail = NULL;
	}
	void Insert(int cnic, T n, T fname, T G, T addy, T nation)//Inserts Node in CBID list in Ascending Order
	{
		CBID_NODE* x = new CBID_NODE(cnic, n, fname, G, addy, nation);
		if (head == NULL)//inserts at head if list is empty
		{
			head = x;
			tail = x;
		}
		else if (head->CNIC > cnic)//inserts at head if CNIC of head is greater 
		{
			head->prev = x;
			x->next = head;
			head = x;
			head->prev = NULL;
		}
		else if (tail->CNIC < cnic)//inserts at the end of list
		{
			tail->next = x;
			x->prev = tail;
			x->next = NULL;
			tail = x;
		}
		else	//inserts in the middle of list
		{
			CBID_NODE* iterator;
			iterator = head;
			while (iterator->next != NULL)
			{
				iterator = iterator->next;
				if (iterator->CNIC > cnic)
				{
					x->prev = iterator->prev;
					iterator->prev->next = x;
					iterator->prev = x;
					x->next = iterator;
					return;
				}
			}

		}
	}
	bool isEmpty()//checks whether list is empty or not
	{
		if (head == NULL)
			return 1;
		else
			return 0;
	}
	~CBIDList()	//destructor 
	{
		CBID_NODE* iterator;
		iterator = head;
		while (iterator->next != NULL)
		{
			CBID_NODE* temp;
			temp = iterator;
			iterator = iterator->next;
			delete temp;
		}
		delete iterator;
		head = NULL;
		tail = NULL;
	}

};

struct CrimeNode { //node for crimes list present in each CCID node
	string fine;
	string details;
	string punishment;
	CrimeNode* next;//singly linked list
	CrimeNode()//Default Constructor
	{
		fine = "\0";
		details = "\0";
		punishment = "\0";
	}
	CrimeNode(string f, string D, string P) //Parameterized Constructor
	{
		fine = f;
		details = D;
		punishment = P;
	}
};

struct CrimesList {	//stores Crime history of an individual
	CrimeNode node;
	CrimeNode* head = NULL;
	void Append(string f, string Details, string P)
	{
		if (head == NULL)//in case of no previous criminal record
		{
			CrimeNode* x = new CrimeNode(f, Details, P);
			head = x;
			x->next = NULL;
		}
		else //in case of previous criminal record present
		{
			CrimeNode* iterator;
			iterator = head;
			while (iterator->next != NULL)
			{
				iterator = iterator->next;
			}
			CrimeNode* x = new CrimeNode(f, Details, P);
			iterator->next = x;
			x->next = NULL;
		}
	}
	bool Remove(string f, string det, string punish)//deletes crime present if details match;
	{
		if (head == NULL)//no crime record present for given person
		{
			return 0;
		}
		else //crime record present
		{
			CrimeNode* iterator;
			iterator = head;
			if (iterator->fine == f && iterator->details == det && iterator->punishment == punish) /*checks crime for head */
			{
					delete iterator;
					head = NULL;
					return 1;
			}
			else /*checks crime present at any node after head*/
			{
				while (iterator->next != NULL)
				{
					if (iterator->next->fine == f && iterator->next->details == det && iterator->next->punishment == punish)
					{
						CrimeNode* temp;
						temp = iterator->next;
						iterator = iterator->next->next;
						delete temp;
						return 1;
					}
					iterator = iterator->next;
				}
			}
			return false;
		}
	}
	bool isEmpty()/*checks whether crime list is empty*/
	{
		if (head == NULL)
			return 1;
		else
			return 0;
	}
};

struct CCID_NODE {
	int CNIC; /*common element to link CBID and CCID*/
	CrimesList Crimes; /*previously constructed list to store crime records*/
	CCID_NODE* next, * prev;/*for bi-directional link*/
	CBID_NODE* CBIDptr;
	CCID_NODE()/*default constructor*/
	{
		next = NULL;
		prev = NULL;
		CBIDptr = NULL;
	}
	CCID_NODE(int cnic, string f, string det, string pun)/*parameterized constructor*/
	{
		CNIC = cnic;
		Crimes.Append(f, det, pun);
		CBIDptr = NULL;
	}
	string criminalRet()	/*returns crime details in string form*/
	{
		CrimeNode* iterator = Crimes.head;
		string str = "\0";
		while (iterator != NULL)
		{
			str = str + " " + iterator->details + " " + iterator->punishment + " " + iterator->fine;
			iterator = iterator->next;

		}
		return str;
	}
};

template <class T>
class CCIDList {	/*doubly linked circular list for criminal record*/
public:
	CCID_NODE node;
	CCID_NODE* head;
	CCID_NODE* tail;
	CCIDList()/*default constructor*/
	{
		head = NULL;
		tail = NULL;
	}
	void Insert(int cnic, T f, T det, T pun)/*inserts node in list in ascending order*/
	{
		CCID_NODE* x = new CCID_NODE(cnic, f, det, pun);
		if (head == NULL)/*inserts at head if list is empty*/
		{
			head = x;
			tail = x;
		}
		else if (head->CNIC > cnic)/*inserts at head if head CNIC is greater*/
		{
			head->prev = x;
			x->next = head;
			head = x;
			head->prev = NULL;
		}
		else if (tail->CNIC < cnic)/*inserts at tail*/
		{
			tail->next = x;
			x->prev = tail;
			x->next = NULL;
			tail = x;
		}
		else	/*inserts in the middle of list*/
		{
			CCID_NODE* iterator;
			iterator = head;
			while (iterator->next != NULL)
			{
				iterator = iterator->next;
				if (iterator->CNIC > cnic)
				{
					iterator->prev->next = x;
					x->prev = iterator->prev;
					iterator->prev = x;
					x->next = iterator;
					break;
				}
			}

		}
		head->prev = tail;/*ensures that list stays circular*/
		tail->next = head;
	}
};

template <class T>
class Database { //driver class

	CBIDList<T> CBID; //CBID Database
	CCIDList<T> CCID; //CCID Database
	DataPipeline<T> dataPipeline;

public:
	void recordCorrespondence() /*forms a bi-directional relationship using node pointers to link people in CBID list to their criminal records */
	{
		CBID_NODE* iterator1 = CBID.head;
		CCID_NODE* iterator2;
		while (iterator1 != NULL)
		{
			iterator2 = CCID.head;
			do
			{
				if (iterator1->CNIC == iterator2->CNIC)/*checking whether CNICs match*/
				{
					iterator1->CCIDptr = iterator2;
					iterator2->CBIDptr = iterator1;
					break;
				}
				iterator2 = iterator2->next;/*incrementing CCID pointer*/
			} while (iterator2 != CCID.head);
			iterator1 = iterator1->next;/*incrementing CBID pointer*/
		}
	}
	Database(const T& filename, const T& filename1) {/*parameterized constructor that reads .txt files into the Queue,
													 we further read data from a queue and inserts in CBID and CCID list*/
		fstream ifile(filename, ios::in);
		string temp;
		while (!ifile.eof())/*enqueues strings till end of file*/
		{
			getline(ifile, temp);
			dataPipeline.enqueue(temp);
		}
		while (dataPipeline.is_empty() == 0) {/*transfers data into list till data pipeline is itself empty*/
			string str = dataPipeline.dequeue();
			stringstream var;
			int CNIC;
			T name;
			T fname;
			T gen;
			T addy = "\0";
			T nation;
			var << str;
			var >> CNIC;
			var.clear();
			var << str;
			var >> name;
			var.clear();
			var << str;
			var >> fname;
			var.clear();
			var << str;
			var >> gen;
			for (int i = 0; i < 3; i++)//appends entire address in 1 string
			{
				temp = "\0";
				var.clear();
				var << str;
				var >> temp;
				if (i == 0)
				{
					addy = temp;
				}
				else
					addy = addy + " " + temp;

			}
			var.clear();
			var << str;
			var >> nation;
			for (int i = 0; i < 4 && nation.length()>0; i++)
				nation.pop_back();
			CBID.Insert(CNIC, name, fname, gen, addy, nation);
		}
		ifile.close();//closes CBID.txt
		ifile.open(filename1);  //opening CCID.txt
		temp = "\0";
		while (ifile.eof() == 0)/*reads till end of file*/
		{
			getline(ifile, temp);
			dataPipeline.enqueue(temp);
		}
		while (dataPipeline.is_empty() == 0) {/*transfers data till data pipeline is empty*/
			string str = dataPipeline.dequeue();
			stringstream var;
			int CNIC;
			T details;
			T punishment = "\0";
			T fine;
			var << str;
			var >> CNIC;
			var.clear();
			var << str;
			var >> details;
			for (int i = 0; i < 4; i++)//appends punshment in 1 string
			{
				temp = "\0";
				var.clear();
				var << str;
				var >> temp;
				if (i == 0)
				{
					punishment = temp;
				}
				else
					punishment = punishment + " " + temp;
				if (temp == "prison")
					break;
			}

			var << str;
			var >> fine;
			var.clear();
			for (int i = 0; i < 4 && fine.length()>0; i++)
				fine.pop_back();
			CCID.Insert(CNIC, fine, details, punishment);
		}
		ifile.close();//closing CCID.txt
		recordCorrespondence();
	}

	T& CBID_Search_by_CNIC(int cnic) {
		CBID_NODE* iterator = CBID.head;/*points at start of list*/
		while (iterator != NULL)/*traverses through entire list*/
		{
			if (iterator->CNIC == cnic)/*finds matching CNIC*/
			{
				T str1;/*stores criminal record*/
				if (iterator->CCIDptr->Crimes.isEmpty() == 0)  //if crimes are empty...
				{
					str1 = iterator->CCIDptr->criminalRet();//crime record
				}
				else
					str1 = "\0";
				T str2 = T(iterator->basicsRet());//basics return
				T* s;
				s = new T;
				*s = (str2 + str1);
				return *s;
			}
		}
		T *temp = new T("RECORD NOT FOUND");
		return *temp;
	}
	T& CCID_Search_by_CNIC(int cnic) {
		CCID_NODE* iterator = CCID.head;/*points at start of CCID list*/
		while (iterator->next != CCID.head)/*traverses entire list*/
		{
			if (iterator->CNIC == cnic)/*looks for CNIC*/
			{
				T str1;
				if (iterator->Crimes.isEmpty() == 0)/*dearching for criminal record*/
				{
					str1 = iterator->criminalRet();/*returns criminal record in string form*/
				}
				else
					str1 = "\0";
				T str2 = iterator->CBIDptr->basicsRet();/*basic info is returned in string form*/
				T* s = new T;
				*s = str2 + str1;
				return	*s;/*string containing both basic info and criminal record*/
			}
			iterator = iterator->next;

		}
		T *temp = new T("RECORD NOT FOUND");
		return *temp;
	}

	bool updateCBIDName(T Name, int cnic) {
		CBID_NODE* iterator = CBID.head;
		if (CBID.isEmpty() == true)
			return false;/*empty list cannot be updated*/
		while (iterator != NULL)
		{
			if (iterator->CNIC == cnic)
			{
				iterator->name = Name;
				return true;/*CNIC is found and name is updated*/
			}
		}
		return false;
	}
	bool updateCBIDFName(T Father_Name, int cnic) {
		CBID_NODE* iterator = CBID.head;
		if (CBID.isEmpty() == true)
			return false;/*empty list cannot be updated*/
		while (iterator != NULL)
		{
			if (iterator->CNIC == cnic)
			{
				iterator->FatherName = Father_Name;
				return true;
			}
		}
		return false;
	}
	bool updateCBIDAddress(T Address, int cnic) {
		CBID_NODE* iterator = CBID.head;
		if (CBID.isEmpty() == true)
			return false;/*empty list cannot be updated*/
		while (iterator != NULL)
		{
			if (iterator->CNIC == cnic)
			{
				iterator->Address = Address;
				return true;
			}
		}
		return false;
	}
	bool updateCBIDNationality(T Nationality, int cnic) {
		CBID_NODE* iterator = CBID.head;
		if (CBID.isEmpty() == true)
			return false;/*empty list cannot be updated*/
		while (iterator != NULL)
		{
			if (iterator->CNIC == cnic)
			{
				iterator->Nationality = Nationality;
				return true;
			}
		}

		return false;
	}

	bool addCrime(int cnic, T charges, T punishment, T fine) {
		CBID_NODE* iterator = CBID.head;
		if (CBID.head == NULL)
		{
			return false;/*cannot add crime if person does not exist*/
		}
		while (iterator->next != NULL)/*traversing through list for CNIC*/
		{
			if (iterator->CNIC == cnic)//CNIC matched
			{
				if (iterator->CCIDptr != NULL)
				{
					iterator->CCIDptr->Crimes.Append(fine, charges, punishment);
				}
				else
				{
					CCID.Insert(cnic, fine, charges, punishment);
					recordCorrespondence();/*links newly created CCID node to its corresponding CBID node*/
				}
				return true;
			}
			iterator = iterator->next;
		}
		return false;
	}
	bool updateCrime(int cnic, T charges, T punishment, T fine) {
		CCID_NODE* iterator = CCID.head;
		if (CCID.head == NULL)
			return false;/*empty list cannot be updated*/
		while (iterator->next != CCID.head)
		{
			if (iterator->CNIC == cnic)
			{
				if (iterator->Crimes.isEmpty() == 1)
				{
					return false;
				}
				iterator->Crimes.head->fine = fine;//updating fine
				iterator->Crimes.head->details = charges;//updating details
				iterator->Crimes.head->punishment = punishment;//updating punishment
				return true;
			}
			iterator = iterator->next;
		}
		return false;
	}
	bool deleteCrime(int cnic, T charges, T punishment, T fine) {
		CCID_NODE* iterator = CCID.head;
		if (CCID.head == NULL)
			return false;/*Cannot delete item from empty list */
		while (iterator->next != CCID.head)
		{
			if (iterator->CNIC == cnic)
			{
				bool x= iterator->Crimes.Remove(fine, charges, punishment);
				cout << "        " << x << endl;
				return x;
			}
			iterator = iterator->next;
		}
		return false;
	}
	~Database() {

	}
};



#endif
