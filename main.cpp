//--------------------------------------
//      CS 315 - Markov Algorithm
//--------------------------------------
// Reads in a set of rules and 
// evaluates strings based on the rules
//--------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// contains the parts for the rules: left pattern, right pattern, and next rule
struct rule {
        string left;
        string right;
        int nextRule;
};

// gets the number of productions from the input string
int getProductions(string in) {
	int returnProductions;
	// if the ASCII value for the 1st symbol in the string is a number
	if ((int)in[0] >= 48 && (int)in[0] <= 57) {
		// if 2nd symbol is also a number
                if ((int)in[1] >= 48 && (int)in[1] <= 57) {
			// creates a temporary string holder and converts to int
                        string tempJoin = string() + in[0] + in[1];
                        returnProductions = stoi(tempJoin);
                }
		else {
			// converts the first char to an int
			returnProductions = in[0] - '0';
		}
        }
	return returnProductions;
}

// gets the start of the loop for reading in the rules
int getStart(int productions) {
	int returnStart;
	// if the production was only a single digit
	if (productions <= 9) {
                returnStart = 1;
        }
	// if the production was two digits
        else {
                returnStart = 2;
        }
	return returnStart;
}

// simply returns the portion of the string that was specified by the indices
string subString(string oString, int start, int end) {
        string returnStr = "";
	// appends chars between start and end indices to the returnStr
        for (int i = start; i <= end; i++) {
                returnStr += oString[i];
        }
        return returnStr;
}

// improved brute force search: if all characters of a pattern are different, increments the search index by the entire pattern knowing none of the characters can work in current part of the string being searched
void IBFsearch(string patStr, string srchStr, string replaceStr, string &backStr) {
	// gets sizes of strings, computes difference, sets first search index
	int patStrLen = patStr.size();
	int srchStrLen = srchStr.size();
	int lengthDiff = srchStrLen - patStrLen;
	int i = 0;

	// while the search can still operate with needed number of characters
	while (i <= lengthDiff) {
		int j; // second search index

		// goes length of patStr, if the srchStr char doesn't match then breaks out of for loop
		for (j = 0; j < patStrLen; j++) {
			if (srchStr[i + j] != patStr[j]) {
				break;
			}
		}

		// if the search went all the way through and was a match
		if (j == patStrLen) {
			// creates a new string with the right pattern
			string front = subString(srchStr, 0, i - 1);
			front += replaceStr; // the right pattern
			front += subString(srchStr, i + j, srchStrLen);
			backStr = front; // passes back string by reference
			return;
		}
		// if the search didn't get past the first character
		else if (j == 0) {
			i++;
		}
		// increments search by the proper amount
		else {
			i += j;
		}		
	}
	return;
}

// small UI to get user's choice of file
string chooseFile() {
        string fileChoice; // string for getting user's choice of file

        // outputs instructions for user
        cout << "Please enter the text file you would like to use." << endl;
        cout << "For my data, enter myMarkov.txt." << endl;
        cout << "For Dr. Finkel's data, enter finkelMarkov.txt." << endl;
        cout << "Choice: ";

        cin >> fileChoice; // gets user input for the file

        // outputs more instructions
        cout << endl;
        cout << "Thank you for choosing. To continue, press enter." << endl;
        cin.get();
        cin.get();

        return fileChoice; // sends back the file choice
}
	
int main() {
	// for the intake of the Markov rules
	string input;
	ifstream file;
	
	// gets choice of file
	string userChoice = chooseFile();

	// opens Finkel's rule set and reads it in
	if (userChoice == "finkelMarkov.txt") {
		file.open("finkelMarkov.txt");
		if (!file.fail()) {
			file >> input;
		}
	}
	// opens my rule set and reads it in
	else if (userChoice == "myMarkov.txt") {
		file.open("myMarkov.txt");
                if (!file.fail()) {
                        file >> input;
                }
	}
	file.close();
	
	// gets the number of productions, declares the needed rules, and gets the start position of the loop to read in the rules correctly
	int numProductions = getProductions(input);
	rule rules[numProductions];
	int startPos = getStart(numProductions);

	// variables to track the amount of ticks, 4 per rule
	int tickCount = 0;

	// keeps track of the current rule, increments when needed
        int currentRule = 0;

	// strings to store parts of unfinished rule parts
        string leftPart = "";
        string rightPart = "";
        string readInNextRule = "";

        // main read in loop for the rules
        for (int i = startPos; i < input.size(); i++) {
		// if at 0 ticks, checks to see what next two characters are
		// if there are two ticks in succession, sets left pattern of rule as empty
                if (tickCount == 0) {
                        if ((int)input[i] == 39) {
                                tickCount++;
                        }
                        if ((int)input[i+1] == 39) {
                                tickCount++;
                                i++;
                                rules[currentRule].left = "";
                                goto endLoop;
                        }
                        goto endLoop;
                }
		// if at 1 tick, keeps appending to current pattern if the current char is not a tick
		// if it is a tick, increments tick count and sets the left pattern
                else if (tickCount == 1) {
                        if ((int)input[i] == 39) {
                                tickCount++;
                                rules[currentRule].left = leftPart;
                                goto endLoop;
                        }
                        else {
                                leftPart = leftPart + input[i];
                        }
                }
		// same as 0 ticks but for right pattern
		 else if (tickCount == 2) {
                        if ((int)input[i] == 39) {
                                tickCount++;
                        }
                        if ((int)input[i+1] == 39) {
                                tickCount++;
                                i++;
                                rules[currentRule].right = "";
                                goto endLoop;
                        }
                        goto endLoop;
                }
		// same as 1 tick but for right pattern
                else if (tickCount == 3) {
                        if ((int)input[i] == 39) {
                                tickCount++;
                                rules[currentRule].right = rightPart;
                                goto endLoop;
                        }
                        else {
                                rightPart = rightPart + input[i];
                        }
                }
		// reads in the number for the nextRule part of the current rule
		// reads in two digits if needed
                else if (tickCount == 4) {
                        if ((int)input[i+1] == 39) {
                                readInNextRule = string() + input[i];
                        }
                        else {
                                readInNextRule = string() + input[i] + input[i+1];
                        }
                        rules[currentRule].nextRule = stoi(readInNextRule);
			
			// resets counts and parts and increments the current rule
                        tickCount = 0;
                        rightPart = "";
                        leftPart = "";
                        readInNextRule = "";
                        if (currentRule != numProductions) {
                                currentRule++;
                        }
                }
                endLoop:;
        }

	// outputs a table of the rules
	cout << "RULE    LEFT      RIGHT    NEXT RULE" << endl;
	for (int i = 0; i < numProductions; i++) {
		cout << i << "	" << setw(5) << left;
		cout << rules[i].left << setw(10) << right;
		cout << rules[i].right << "	" << setw(8);
		cout << rules[i].nextRule << endl;
	}

	// titles for columns
	cout << endl;
	cout << "Rule" << "\t\t" << "Execution";
	cout << endl;

	// creates a rule execution counter, the original string to search, and a bool to end the while loop
	int execCounter = 0;
	string oString;
	bool zeroReached = false;

	// while there haven't been 1000 rules executed and the initial string has only been input once
	while (execCounter < 1000 && zeroReached == false) {
		for (int i = 0; i < numProductions; i++) {
			if (i == 0) {
				zeroReached = true;
			}
			
			// used to compare the original string after it gets passed back
			string copyStr = oString;
			// searches the given string for the left pattern and replaces it with the right if found
			IBFsearch(rules[i].left, oString, rules[i].right, oString);
			
			// if the string has been changed, outputs the change
			// changes i to the value of the next rule and incrementes execution counter by one
			if (copyStr != oString) {
				cout << i << "\t\t" << oString << endl;
				i = rules[i].nextRule - 1;
				execCounter++;
			}
		}
	}

	if (execCounter == 1000) {
		cout << "Maximum number of rule executions made." << endl;
	}

	return 0;
}
