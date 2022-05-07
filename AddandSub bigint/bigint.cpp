#include <iostream>
#include<algorithm>
#include <sstream>
#include <string>
using namespace std;


class bigint {
public:
	string num;
	int sign;
	bigint();
	bigint(string decStr);
	bigint(int decInt);

	friend ostream& operator<<(ostream& o, bigint n);
	friend bool checkvalid(bigint& a);
	bigint operator+(bigint v2);
	bigint operator-(bigint v2);


};
bigint::bigint() {
	num = "";
	sign = 1;
}
bigint::bigint(int decInt) {
	num = to_string(decInt);
}
int checksign(string& a) {
	int c = 0;
	if (a[0] == '-')
		c = 0;
	else if (a[0] == '+')
		c = 1;
	else
		c = 2;
	return c;
}

bool isvalid(string& str)
{
	if (str[0] == '+' || str[0] == '-')
		str.erase(str.begin() + 0);
	for (char& c : str) {//in range
		if (isdigit(c) == 0)
			return 0;
	}
	return 1;
}
void removeleftzeroes(string& a) {
	int c = 0;
	while (true) {

		if (a[0] == '0') {
			a.erase(a.begin() + 0);
		}
		else
			break;
	}
}

bigint::bigint(string stnum) {
	num = stnum;
	sign = checksign(stnum);
	if (isvalid(num)) {
		removeleftzeroes(num);

		return;
	}
	else {
		cout << "The number is not valid\n";
		return;
	}

}
int newsign(bigint v1, bigint v2) {
	if (v1.num.length() > v2.num.length())
		return v1.sign;
	else if (v2.num.length() > v1.num.length())
		return v2.sign;
	else {
		for (int i = 0; i < v1.num.length(); i++)
		{
			if (v1.num[i] - 48 > v2.num[i] - 48)
				return v1.sign;
			else if (v2.num[i] - 48 > v1.num[i] - 48)
				return v2.sign;

		}


	}
}
int isbigger(bigint v1, bigint v2) {
	if (v1.num.length() > v2.num.length())
		return 0;
	else if (v2.num.length() > v1.num.length())
		return 1;
	else {
		for (int i = 0; i < v1.num.length(); i++)
		{
			if (v1.num[i] - 48 > v2.num[i] - 48)
				return 0;
			else if (v2.num[i] - 48 > v1.num[i] - 48)
				return 1;

		}


	}
}
ostream& operator<< (ostream& output, bigint n)
{

	if (!n.sign) {
		n.num.insert(n.num.begin(), '-');

	}
	cout << n.num;
	return output;
}

string add(bigint v1, bigint v2) {

	bigint v3;
	int carry = 0;
	string str = "";
	if (v1.num.length() > v2.num.length())
		swap(v1.num, v2.num);
	int n1 = v1.num.length(), n2 = v2.num.length();
	reverse(v1.num.begin(), v1.num.end());
	reverse(v2.num.begin(), v2.num.end());
	int i = 0;
	while (i < n1)
	{

		int sum = ((v1.num[i] - 48) + (v2.num[i] - 48) + carry);
		str.push_back(sum % 10 + 48);


		carry = sum / 10;
		i++;
	}
	while (i < n2)
	{
		int sum = ((v2.num[i] - 48) + carry);
		str.push_back(sum % 10 + 48);
		carry = sum / 10;
		i++;
	}
	if (carry)
		str.insert(str.end(), carry + 48);
	reverse(str.begin(), str.end());
	v3.num = str;
	return v3.num;

}
bool isequal(string v1, string v2) {
	if (v1.length() != v2.length())
		return false;
	for (int i = 0; i < v1.length(); i++) {
		if (v1[i] == v2[i]) {
			continue;
		}
		else
			return false;
	}
	return true;
}
string sub(bigint v1, bigint v2) {

	bigint v3;
	int carry = 0;
	if (v1.num.length() < v2.num.length() || isbigger(v1, v2))
		swap(v1.num, v2.num);
	string str = "";
	int n1 = v1.num.length(), n2 = v2.num.length();

	reverse(v1.num.begin(), v1.num.end());
	reverse(v2.num.begin(), v2.num.end());




	for (int i = 0; i < n2; i++) {


		int sub= ((v1.num[i] - 48) - (v2.num[i] - 48) - carry);
		if (sub < 0) {
			sub += 10;
			carry = 1;

		}
		else {
			carry = 0;

		}
		str.insert(str.end(), sub + 48);
	}

	for (int i = n2; i < n1; i++) {
		int sub = ((v1.num[i] - 48) - carry);
		if (sub < 0) {
			sub += 10;
			carry = 1;
		}
		else {
			carry = 0;

		}
		str.insert(str.end(), sub + 48);

		}
	reverse(str.begin(), str.end());
	v3.num = str;
	return v3.num;

}
bigint bigint ::operator+(bigint v2) {
	bigint v3;

	if (sign && v2.sign ) {

		v3 = add(*this, v2);

	}
	else if (!sign && !v2.sign) {

		v3 = add(*this, v2);
		v3.sign = 0;
	}
	else if (sign && !v2.sign|| !sign && v2.sign) {
		if (isequal(num, v2.num)) {
			v3.num = "0";

		}
		else {
			v3 = sub(*this, v2);
			v3.sign = newsign(*this, v2);
		}
	}


	return v3;
}

bigint bigint ::operator-(bigint v2) {
	bigint v3;
	if (sign && v2.sign) {
		if (isequal(num, v2.num)) {
			v3.num = "0";
			return v3;
		}
		else {
			v3 = sub(*this, v2);
			if (isbigger(*this, v2))
				v3.sign = 0;
			else
				v3.sign = 1;


			}

	}
	else if (!sign && v2.sign) {
		v3=add(*this, v2);
		v3.sign = 0;
	}
	else if (sign && !v2.sign) {
		v3 = add(*this, v2);
		v3.sign = 1;
	}
	else if (!sign && !v2.sign) {
		if (isequal(num, v2.num)) {
			v3.num = "0";
			return v3;
		}
		else {
			v3 = sub(v2, *this);
			if (isbigger(v2, *this))
				v3.sign = 0;
			else
				v3.sign = 1;


		}

	}
	return v3;
}

int main()
{
	bigint intnum1(3333);
	bigint intnum2(3333);
	cout << "intnum1 + intnum2= " << intnum1 + intnum2 << endl;//6666
	cout << "intnum1 - intnum2= " << intnum1 - intnum2 << endl << endl;//0
	bigint num1("123456789012345678901234567890");
	bigint num2("113456789011345678901134567890");
	cout << "num1 = " << num1 << endl ;//123456789012345678901234567890
		cout << "num2 = " << num2 << endl << endl;//113456789011345678901134567890

	bigint num3 = num2 + num1;
	cout << "num2 + num1 = " << num3 << endl ;//236913578023691357802369135780

	bigint num4 = num2 - num1;
	cout << "num2 - num1 = " << num4 << endl<<endl;//-10000000001000000000100000000

	bigint num5= num1 - num2;
	cout << "num1 - num2 = " << num5 << endl << endl;//10000000001000000000100000000

	bigint num6("5555555555555555555555555555555");
	bigint num7("-2222222222222222222222222222222");
	bigint num8 = num6 + num7;
	bigint num9 = num6 - num7;
	//3333333333333333333333333333333
	cout << "num6 + num7 = " << num8 << endl;
	//7777777777777777777777777777777
	cout << "num6 - num7 = " << num9 << endl << endl;
	return 0;
}
