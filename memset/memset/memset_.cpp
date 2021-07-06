/* memset example */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main()
{
	char str[] = "almost every programmer should know memset!";
	memset(str, '-', 6);
	puts(str);
	cout << str << endl;




	return 0;


}