#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <conio.h>

using namespace std;

int main(void)
{
	HANDLE hEvent; 

	hEvent=OpenEvent( EVENT_ALL_ACCESS,  TRUE, "SubareaEvent" ); 
	if (hEvent==0)
	{
		cout<<"Error opening an event object created in another application!!!";
		_getch();
		return 0;
	}

	cout<<"To start threads in another application, press TAB"<<endl;
	while(!GetAsyncKeyState( VK_TAB )) { }
	_getch();

	SetEvent(hEvent); 
	cout<<"To stop threads in another application, press BACKSPACE"<<endl;
	while(!GetAsyncKeyState( VK_BACK )) { }
	_getch();

	ResetEvent(hEvent); 
	cout<<"To end threads in another application, press ESC"<<endl;
	while(!GetAsyncKeyState( VK_ESCAPE )) { }
	_getch();

	return 0;
}