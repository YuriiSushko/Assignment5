#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Tokenizator
{
private:
	string* token_list;  

public:
	Tokenizator() : token_list(nullptr) {}

	~Tokenizator() {
		delete[] token_list; 
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

				while (pos < input.length() && (isdigit(input[pos]) || input[pos] == ',')) {
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

			if (input[pos] != ',') {
				token_list[iterator] = input[pos];
				iterator++;
			}

			pos++;
		}
		return token_list;
	}
};


int main()
{
	string input;
	getline(cin, input); 

	Tokenizator tokenizator = Tokenizator();
	string* tokens = tokenizator.Tokenize(input);

	for (int i = 0; i < input.length(); i++) {
		if (tokens[i].empty()) {
			break;
		}
		cout << "Token: " << tokens[i] << endl;
	}
	
	return 0;
}
