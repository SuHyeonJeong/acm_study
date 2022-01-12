#include <iostream>
#define MAX 1000
using namespace std;
int arr[MAX] = { 1, 1, };
int fac(int n)
{
	if (arr[n])
		return arr[n];
	
	arr[n] = n * fac(n - 1);
	return arr[n];
}
int main()
{
	cout << fac(3) << endl;
	return 0;
}