#include <iostream>
#include <vector>	
using namespace std;





//计算数组arr中元素的平均值
double average(const vector<double>& arr) {
	double sum = 0;
	for (unsigned i = 0; i < arr.size(); i++) {
		sum += arr[i];

	}
	return sum / arr.size();
}




int main()
{
	//unsigned n;
	//cout << "n= ";
	//cin >> n;

	////创建数组对象
	//vector<double> arr(n);
	//cout << "please input " << n << " real numbers: " << endl;
	//for (unsigned i = 0; i < n; i++) cin >> arr[i];

	//cout << "average = " << average(arr) << endl;


	//基于范围的for循环配合auto举例
	vector<int> a = { 1,2,3 };
	for (auto i = a.begin(); i != a.end(); i++) {//指针	
		cout << *i << endl;

	}

	for (auto i : a) {
		cout << i << endl;
	}





	return 0;
}