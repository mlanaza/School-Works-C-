/*

ASMT01 Part 3 - Dictionary
Anne Lanaza
CSC 340
7/3/18
Professor Duc Ta

*/
#include <iostream>
#include <fstream> //file
#include <string>
#include <vector> 
#include <map> 
#include <sstream> //stringstream
#include <iomanip> //setw
#include <utility> //pair
#include <algorithm> // transform to upper/lowercase
#include <ctype.h> //char at

using namespace std;

string getInput();
void searchWord(map<string, vector<pair<string, string>>> *dictionary, 
	const string &key, bool &val);

int main() {
	fstream ioFile;
	string nextWord;
	map<string, vector< pair <string,string>>> dictionary;
	vector<string> tokens;
	
	cout << "! Opening data file... ./Data.CS.SFSU.txt" << endl;
	ioFile.open("Data.CS.SFSU.txt", ios::in);
	
	cout << "! Loading data..." << endl;
	while (getline(ioFile, nextWord)) {

		tokens.push_back(nextWord);
	}
	cout << "! Loading completed..." << endl;

	ioFile.close();
	cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
	cout << endl;

	//split the strings then populate the map
	for (string entry : tokens) {

		string title = entry.substr(0, entry.find("|")); //gets the title
		string define = entry.substr(title.length() + 1, title.find_last_of(".")); //splits the title from the definition
		
		stringstream test(define);
		string a, speech, definitions;
		vector<pair<string, string>> pairs;

		if (isdigit(title.at(3))) {
			transform(title.begin(), title.end(), title.begin(), ::toupper);
		}
		else {
			title[0] = toupper(title.at(0));
		}
		//further splitting into multiple definitions of one title
		while (getline(test, a, '|')) {

			stringstream test2(a);
			speech = a.substr(0, a.find_first_of(" "));
			definitions = a.substr(a.find_first_of(">") + 2, a.length());
			definitions[0] = toupper(definitions.at(0));

			pairs.push_back(make_pair(speech, definitions));
	
		}
		dictionary.emplace(title, pairs);
	}

	bool quit = false;
	string key;

	cout << "----- DICTIONARY 340 C++-----" << endl;
	cout << " " << endl;

	while (!quit) {
		
		key = getInput();
		searchWord(&dictionary, key, quit);
		
	}
	cout << endl;
	cout << "-----THANK YOU-----" << endl;

	return 0;
}

//gets input from user
string getInput() {
	string input;

	cout << "Search: ";
	getline(cin, input);

	while (input.empty()) {
		cout << setw(9) << "|" << endl;
		cout << "         " << "<Please enter a search key (and a part of speech).>" << endl;
		cout << setw(9) << "|" << endl;
		cout << "Search: ";
		getline(cin, input);
	}
	return input;

}

//checks if the word is in the dictionary
void searchWord(map<string, vector<pair<string, string>>> *dictionary, 
	const string &key, bool &val) {

	vector<string> searchKeys;
	string s;
	stringstream str(key);
	bool found = false;

	while(getline(str, s, ' ')) {
		searchKeys.push_back(s);
	}

	switch (searchKeys.size())
	{

	case 1: //when the input is one keyword
		if (searchKeys[0] == "!Q") {
			val = true;
			return;
		}
		else {
			cout << setw(9) << "|" << endl;
			for (map<string, vector< pair<string, string>>>::iterator itr = dictionary->begin();
				itr != dictionary->end(); ++itr) {
				auto first = itr->first;
				transform(first.begin(), first.end(), first.begin(), ::tolower);
				transform(searchKeys[0].begin(), searchKeys[0].end(), searchKeys[0].begin(), ::tolower);
				if (searchKeys[0] == first) {
					found = true;
					auto pairs = itr->second;
					for (vector<pair<string, string>>::iterator itr2 = pairs.begin(); itr2 != pairs.end(); ++itr2) {
						cout << "         " << itr->first << " [" << itr2->first << "] : "
							<< itr2->second << endl;
					}
					cout << setw(9) << "|" << endl;
					break;
				}
			}
		}
		break;
			case 2: //the input has two keywords
				cout << setw(9) << "|" << endl;
				//validates if second keyword is valid
				if (searchKeys[1] == "noun" || searchKeys[1] == "verb" || searchKeys[1] == "adjective") {
					//145-160 iterates through the map
					for (map<string, vector< pair<string, string>>>::iterator itr = dictionary->begin();
						itr != dictionary->end(); ++itr) {
						auto title = itr->first;
						transform(title.begin(), title.end(), title.begin(), ::tolower);
						transform(searchKeys[0].begin(), searchKeys[0].end(), searchKeys[0].begin(), ::tolower);
						//matches the first keyword
						if (searchKeys[0] == title) {
							auto pairs = itr->second;
							for (vector<pair<string, string>>::iterator itr2 = pairs.begin(); itr2 != pairs.end(); ++itr2) {
								auto speech = itr2->first;
								transform(speech.begin(), speech.end(), speech.begin(), ::tolower);
								transform(searchKeys[0].begin(), searchKeys[0].end(), searchKeys[0].begin(), ::tolower);
								//matches the second keyword
								if(searchKeys[1] == speech){
									found = true;
									cout << "         " << itr->first << " [" << itr2->first << "] : "
										<< itr2->second << endl;
								}
							} 
							if(found) cout << setw(9) << "|" << endl;
						}
					}
				}	else {
					cout << "         " << "<2nd argument must be a part of speech.>" << endl;
					cout << setw(9) << "|" << endl;
					return;
				}
				break;

	default:
		cout << setw(9) << "|" << endl;
		cout << "         " << "<Please enter a search key (and a part of speech).>" << endl;
		cout << setw(9) << "|" << endl;
		return;
	}

	if (!found) {
		cout << "         " << "<Not found.>" << endl;
		cout << setw(9) << "|" << endl;
	}
}
