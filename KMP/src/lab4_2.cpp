#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <sstream>
#include <algorithm>


void print_v(std::vector<int>& p)
{
	for (int i = 0; i < p.size(); i++)
		if (i < p.size() - 1)
			std::cout << p[i] << ",";
		else
			std::cout << p[i];
	std::cout << std::endl;
}


void prefix_funk(std::string &t, std::vector<int>& p)
{
	int i = 1;
	int j = 0;

	while (i < t.size())
	{
		if (t[i] == t[j])
		{
			p[i] = j + 1;
			i += 1;
			j += 1;
		}
		else
		{
			if (j == 0)
			{
				p[i] = 0;
				i += 1;
			}
			else
				j = p[j - 1];
		}
	}
}



void find_template(std::string& s, std::string& t, std::vector<int>& p, std::vector<int>& res)
{

	int m = t.size();
	int n = s.size();
	int i = 0;
	int j = 0;
	bool f = false;

	while (i < n)
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
			if (j == m)
			{
				//std::cout << "finded" << std::endl;
				res.push_back(i - m);
				f = true;
				//break;
			}

		}
		else
		{
			if (j > 0)
			{
				j = p[j - 1];
			}
			else
			{
				i++;
			}
		}
	}

	if (f)
		print_v(res);
	else
		std::cout << -1;
}


int find_c(std::string& A, std::string& B) {
	if (A.length() != B.length()) return -1;

	std::vector<int> p1(A.length()*2+1);

	//std::vector<int> p2(A.length() * 2 + 1);

	std::string str = B + "|" + A;

	prefix_funk(str, p1);
	int a = p1.back();

	if (a == 0) return -1;
	if (a % A.length() == 0) return 0;


	std::string  str1 = A + "|" + B;
	


	prefix_funk(str1, p1);
	int b = p1.back();

	//std::cout << str <<" " << a << std::endl;
	//std::cout << str1 <<" " << b << std::endl;
	if (a + b >= A.length())
		return b;
	return -1;
}



int main()
{
	std::string s;
	std::string t;
	std::string a;
	std::string b = "";

	std::cin >> t;
	std::cin >> s;

	std::cout << find_c(t, s);
	
	return 0;
}
