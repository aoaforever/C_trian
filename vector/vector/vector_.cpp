#include <iostream>
#include <vector>	
using namespace std;





//��������arr��Ԫ�ص�ƽ��ֵ
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

	////�����������
	//vector<double> arr(n);
	//cout << "please input " << n << " real numbers: " << endl;
	//for (unsigned i = 0; i < n; i++) cin >> arr[i];

	//cout << "average = " << average(arr) << endl;


	//���ڷ�Χ��forѭ�����auto����
	vector<int> a = { 1,2,3 };
	for (auto i = a.begin(); i != a.end(); i++) {//ָ��	
		cout << *i << endl;

	}

	for (auto i : a) {
		cout << i << endl;
	}





	return 0;
}