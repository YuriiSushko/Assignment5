#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class Calculator
{
private:
	string* token_list;

public:
	Calculator() : token_list(nullptr) {}

	~Calculator() {
		delete[] token_list; 
	}

	int priorities(const string& op) {
		if (op == "+" || op == "-")
			return 1;
		else if (op == "*" || op == "/")
			return 2;
		else if (op == "min" || op == "max")
			return 3;
		else if (op == "pow" || op == "abs")
			return 4;
		else
			return 0;
	}

	string* Tokenize(const string& input) {
		string* token_list = nullptr;

		token_list = new string[input.length()];
		int pos = 0;
		int iterator = 0;

		while (pos < input.length()) {
			if (isspace(input[pos])) {
				pos++;
				continue;
			}

			if (isdigit(input[pos])) {
				size_t start = pos;

				while (pos < input.length() && (isdigit(input[pos]) || input[pos] == '.')) {
					pos++;
				}

				token_list[iterator] = input.substr(start, pos - start);
				iterator++;
				continue;
			}

			if (isalpha(input[pos])) {
				size_t start = pos;

				while (pos < input.length() && (isalpha(input[pos]))) {
					pos++;
				}

				token_list[iterator] = input.substr(start, pos - start);
				iterator++;
				continue;
			}

			if (input[pos] == '+' || input[pos] == '-' || input[pos] == '*' || input[pos] == '/'
				|| input[pos] == '(' || input[pos] == ')' || input[pos] == ',') {
				token_list[iterator] = input.substr(pos, 1);
				iterator++;
				pos++;
				continue;
			}

			pos++;
		}
		return token_list;
	}

	queue<string> ShuntingYard(string* tokens) {
		stack<string> token_stack;
		queue<string> result;
		int iterator = 0;

		while (!tokens[iterator].empty()) {
			if (isdigit(tokens[iterator][0])) {
				result.push(tokens[iterator]);
			}
			else if (!isdigit(tokens[iterator][0]) && tokens[iterator] != "(" && tokens[iterator] != ")" && tokens[iterator] != ",")
			{
				while (!token_stack.empty() &&
					(priorities(token_stack.top()) >= priorities(tokens[iterator]))) 
				{
					result.push(token_stack.top());
					token_stack.pop();
				}
				token_stack.push(tokens[iterator]);
			}
			else if (tokens[iterator] == "(") 
			{
				token_stack.push(tokens[iterator]);
			}
			else if (tokens[iterator] == ")") {
				while (!token_stack.empty() && token_stack.top() != "(") 
				{
					result.push(token_stack.top());
					token_stack.pop();
				}
				if (!token_stack.empty()) 
				{
					token_stack.pop(); 
				}
			}
			else if (tokens[iterator] == ",") {
				while (!token_stack.empty() && token_stack.top() != "(")
				{
					result.push(token_stack.top());
					token_stack.pop();
				}
				
			}
			iterator++;
		}

		while (!token_stack.empty()) {
			result.push(token_stack.top());
			token_stack.pop();
		}

		return result;
	}

	string Calculate(queue<string>& sorted_tokens) 
	{
		stack<string> calculate_stack;
		while (!sorted_tokens.empty())
		{
			string token = sorted_tokens.front();
			sorted_tokens.pop();

			if (isdigit(token[0])) {
				calculate_stack.push(token);
			}
			else 
			{
				double secondDigit = stod(calculate_stack.top());
				calculate_stack.pop();
				double firstDigit = stod(calculate_stack.top());
				calculate_stack.pop();

				if (token == "+") {
					calculate_stack.push(to_string(firstDigit + secondDigit));
				}
				else if(token == "*") {
					calculate_stack.push(to_string(firstDigit * secondDigit));
				}
				else if (token == "/") {
					calculate_stack.push(to_string(firstDigit / secondDigit));
				}
				else if (token == "-") {
					calculate_stack.push(to_string(firstDigit - secondDigit));
				}
				else if (token == "min") {
					calculate_stack.push(to_string(min(firstDigit, secondDigit)));
				}
				else if (token == "max") {
					calculate_stack.push(to_string(max(firstDigit, secondDigit)));
				}
				else if (token == "pow") {
					calculate_stack.push(to_string(pow(firstDigit, secondDigit)));
				}
				else if (token == "abs") {
					calculate_stack.push(to_string(abs(firstDigit)));
				}
			}
		}
		return calculate_stack.top();
	}
};


int main()
{
	string input;
	getline(cin, input); 

	Calculator calculator;
	string* tokens = calculator.Tokenize(input);
	queue<string> sy = calculator.ShuntingYard(tokens);

	cout << calculator.Calculate(sy) << endl;

	delete[] tokens;
	
	return 0;
}
