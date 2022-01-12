#include <iostream>
#define MAX 1000
using namespace std;
int arr[MAX] = { 1, 1, 2, };
int fibo(int n)
{
	if (arr[n])
		return arr[n];
	arr[n] = fibo(n - 1) + fibo(n - 2);
	return arr[n];
}
int main()
{
	cout << fibo(3) << endl;
	return 0;
}