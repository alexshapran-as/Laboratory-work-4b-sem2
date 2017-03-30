#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>
#include <thread>
#include <tchar.h>
#include <mutex>
#include <windows.h>

using namespace std;


class Subarea
{
protected: 
	
	char student[64];
	char subject[64];
	unsigned int size1 = 0;
	unsigned int size2 = 0;

public:
	Subarea ( char* student, char* subject )
	{
		this->size1 = strlen(student);
		this->size2 = strlen(subject);
		
		for ( unsigned int i = 0; i < size1; ++i ) 
			this->student[i] = student[i];

		for ( unsigned int i = 0; i < size2; ++i ) 
			this->subject[i] = subject[i];

	}

	virtual void tutor() = 0;
	virtual void  rating() = 0;
	virtual void  telephone() = 0;

	virtual void  print()
	{
		cout << endl << " Student: ";
		for ( unsigned int i = 0; i < size1; ++i ) cout << this->student[i];
		cout << endl << " Subject area: ";
		for ( unsigned int i = 0; i < size2; ++i ) cout << this->subject[i];
	}
	
	friend void ThreadFunction( Subarea* p );

};

class Tutor: public Subarea
{
protected:	

	char fio[64];
	unsigned int size3 = 0;

public:

	Tutor( char* student, char* subject, char* tutor ):
		Subarea( student, subject )
	{
		this->size3 = strlen(tutor);

		for ( unsigned int i = 0; i < size3; ++i ) 
			fio[i] = tutor[i];
	}

	virtual void print()
	{
		Subarea::print();
		cout << endl << " Tutor: ";
		for ( unsigned int i = 0; i < size3; ++i ) cout << fio[i];
	}

	void tutor() {}

};

class Rating: public Tutor
{
protected:	

	unsigned int mark = 0;

public:

	Rating( char* student, char* subject, char* tutor,  unsigned int mark):
		Tutor( student, subject, tutor )
		{
			this->mark = mark;
		}

	virtual void print()
	{
		Tutor::print();
		cout << endl << " Rating: " << this->mark;
	}

	void rating() {}
};

class Telephone: public Rating
{
protected:	

	char number[64];
	unsigned int size4 = 0;

public:

	Telephone( char* student, char* subject, char* tutor,  unsigned int mark, char* number):
		Rating( student, subject, tutor, mark )
		{
			this->size4 = strlen(number);

		for ( unsigned int i = 0; i < size4; ++i ) 
			this->number[i] = number[i];
			
		}

	void print()
	{
		Rating::print();
		cout << endl << " Student's phone number: ";
		for ( unsigned int i = 0; i < size4; ++i ) cout << this->number[i];
		cout << endl;
	}

	void telephone() {}

};

HANDLE hEvent; 
mutex mut;

void ThreadFunction ( Subarea* p )
{
	mut.lock();
	WaitForSingleObject(hEvent, INFINITE);
	p->print();
	SetEvent(hEvent);
	mut.unlock();
}

int main(void)
{
	hEvent=CreateEvent(0, 1, 0, "SubareaEvent");
	char student[64];
	char subject[64];
	char tutor[64];
	unsigned int rating = 0;
	char telephone[64];
	unsigned int size = 0;

	cout << endl << "Print the number of students: ";
	cin >> size;
	cout << endl;

	Subarea *p[size];

		for ( unsigned int i = 0; i < size; ++i )
		{
			cout << endl << " Student " << i+1 << " ";
			fflush(stdin); 
			cin.getline(student, 64); 
			cout << endl << " Subject area " << " ";
			fflush(stdin); 
			cin.getline(subject, 64);
			cout << endl << " Tutor: " << " ";
			fflush(stdin); 
			cin.getline(tutor, 64);
			fflush(stdin);
			cout << endl << " Student's rating: " << " ";
			cin >> rating;
			cout << endl << " Student's phone number: " << " ";
			fflush(stdin); 
			cin.getline(telephone, 64); 
			fflush(stdin);

			p[i] = new Telephone(student, subject, tutor, rating, telephone);

		} 
	
		for ( unsigned int i = 0; i < size; ++i ) 
		{
			

			thread th(ThreadFunction, *(p+i));
			th.join();
		}

	for (unsigned int i = 0; i < size; ++i) delete p[i];
	cout << endl << endl << "Press any button to exit the program" << endl;
	_getch();
	return 0;
}
