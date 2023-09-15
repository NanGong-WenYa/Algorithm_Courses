#include<iostream>
#include<queue>
#include<stack>
#include<string>
using namespace std;
bool isMatched(char c,char check){
	switch (c) {
	case ')':if (check == '(')return true;
			else return false;
	case ']':if (check == '[')return true;
			else return false;
	
	}
}

int main() {
	string str;
	cin >> str;
	stack<char>in;
	stack<char>out;
	queue<stack<char>>res;
	for (char c : str) {
		if (in.empty())//输入栈为空时
		{	
			if (!out.empty()) {//如果之前已经有一组out了，把这组out放入res中
				res.push(out);
				while(!out.empty())
					out.pop();
			}
			
				if (c == ')') {
					out.push(')');
					out.push('(');

				}
				else if (c == ']') {
					out.push(']');
					out.push('[');

				}
				else if (c == '(' || c == '[')in.push(c);
			
		}

		else {
			char check = in.top();
			if (c == ']' || c == ')') {//输入栈不为空时，如果输入右括号
				if (isMatched(c, check)) {//如果右括号和栈顶的左括号匹配成功
					if (c == ')') {
						in.pop();
						out.push(')');
						out.push('(');
						
					}
					else if (c == ']') {
						in.pop();
						out.push(']');
						out.push('[');
						
					}
				}
				else {//如果匹配不成功，把c变成匹配的对并放入out
					if (c == ']') {
						out.push(']');
						out.push('[');
						
					}
					else {
						out.push(')');
						out.push('(');
						
					}
				}
			}
			else {//如果匹配的是左括号,入栈
				in.push(c);
			}


		}
	}
	
	//开始清理in中剩余括号,剩下的一定要不全是左括号，要不只有一个右括号
	while (!in.empty()) {
		switch (in.top()) {
			case '(': {
				out.push(')');
				out.push('(');
				 break;
			}
			case ')':{
				out.push(')');
				out.push('(');
				 break;
			}
			case ']':{
				out.push(']');
				out.push('[');
				 break;
			}
			case'[': {
				out.push(']');
				out.push('[');
				 break;
			}
		}
		in.pop();
	}
	//把最后一组out入res栈
	res.push(out);
	while (!out.empty())
	out.pop();
	//开始输出
	while (!res.empty()) {
		while (!res.front().empty())
		{
			cout << res.front().top();
			res.front().pop();
		}
		res.pop();
	}
	return 0;
}