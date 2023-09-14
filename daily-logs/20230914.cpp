#include <iostream>
#include <string>
#include<map>
using namespace std;
string Trans(string str) {
	string result = "";
	//阿拉伯数字转化为中文数字
	if (str[0] >= '0' && str[0] <= '9') {
		int num = stoi(str);
		if (num == 0) {
			return "零";
		}

		string chineseNumbers[] = { "零", "一", "二", "三", "四", "五", "六", "七", "八", "九" };
		string unit[] = { "", "十", "百", "千" };
		string bigUnit[] = { "万", "亿", "万亿" };
		string result = "";

		int unitIndex = 0;
		int bigUnitIndex = 0;
		bool needZero = false;

		bool needBigUnit = false;

		while (num > 0) {
			int digit = num % 10;

			if (digit == 0) {
				if (needZero) {
					result = chineseNumbers[0] + result;
					needZero = false;
				}
			}
			else {
				if (unitIndex == 4) {
					needBigUnit = true;
					unitIndex = 0;
				}

				if (needBigUnit) {
					result = bigUnit[bigUnitIndex] + result;
					needBigUnit = false;
					bigUnitIndex++;
				}

				result = chineseNumbers[digit] + unit[unitIndex] + result;
				needZero = true;
			}

			num /= 10;
			unitIndex++;
		}

		return result;
	}

	//中文数字转化为阿拉伯数字
	else if (str[0] == '一'|| str[0] == '二' || str[0] || '三' && str[0] == '四' || str[0] == '五' || str[0] == '六' || str[0] == '七' || str[0] == '八' || str[0] == '九' || str[0] == '十' || str[0] == '零')
	{
		map<char, int> chineseDigitMap = {
		{'零', 0}, {'一', 1}, {'二', 2}, {'三', 3}, {'四', 4},
		{'五', 5}, {'六', 6}, {'七', 7}, {'八', 8}, {'九', 9}
		};

		
			int res=0;
			int currentNumber = 0;

			for (char c : str) {
				if (c == '亿') {
					result += currentNumber * 100000000;
					currentNumber = 0;
					
				}
				else if (c == '万') {
					res += currentNumber * 10000;
					currentNumber = 0;
					
				}
				else {
					currentNumber = currentNumber * 10 + chineseDigitMap[c];
				}
				
			}

			

			return to_string(res);

		}
	else return"please input correctly!";
	}


int main(){
	string InputStr;
	
	cout << "请输入一串钱";
	cin >> InputStr;
	cout << Trans(InputStr);


}



