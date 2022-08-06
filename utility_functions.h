#include<iostream>
#include <iomanip> // allows me to manipulate cin
#include<string> // allows me to to store strings
#include <algorithm> // improves the manipulation of vectors
#include <time.h> // access time
#include <vector> // accesses vectors

using namespace std;

int get_integer_input(const int MIN = INT_MIN, const int MAX = INT_MAX); // gets valid integer inputs

string get_exclusive_string_input(const string PERMITTED_CHARS, const int MIN = 0, const int MAX = 20); // gets an string input that's made up of a specific list of characters

bool has_char_in_string(const char CHARACTER, const string STRING); // determines if the string contains a specific character

bool has_listed_characters_only(const string LIST, const string STRING); // determines if a string only contains a specific list of characters

bool is_upper_case(char character); // determines if the passed character is an uppercase letter

string get_molded_word(const string MODEL, const string MATERIAL); // gets the users 'mold' of a 'model' word

float get_molds_accuracy_percentage(const string MODEL, const string MOLD); // gets the percentage that represents how accurate the 'mold' is to the 'model' word

bool diff_chars_look_similar(const char A, const char B); // determines if two characters are similar

string get_random_model(); // gets a random model

string get_random_material_word(); // gets a random material word

void display_binding_request(const string MODEL, const string MATERIAL); // displays an interaction between the user and a customer

string get_presentable_string(string material_word); // gets a string that is alphabatized and dones not have redundant characters

void display_intro(); // prints the information needed to play the game


// declaration and definition divider

int get_integer_input(const int MIN, const int MAX) {
	int input = 0;

	cin >> setw(1) >> input;

	while (cin.good() == false || input < MIN || input > MAX) {// while input was not valid
		cout << "invalid input. Try again" << endl;

		// clears stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		// retries retreiving input
		cin >> setw(1) >> input;
	}

	return input;
}

string get_exclusive_string_input(const string PERMITTED_CHARS, const int MIN, const int MAX) { 
	string input;

	cin >> setw(MAX) >> input;

	while (cin.good() == false || input.size() < MIN || input.size() > MAX || has_listed_characters_only(PERMITTED_CHARS, input) == false) {// while input was not valid
		cout << "invalid input. Try again" << endl;

		// clears stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		// retries retreiving input
		cin >> setw(MAX) >> input;
	}
	return input;
}

bool has_listed_characters_only(const string LIST, const string STRING) {
	bool condition = true;

	for (string::const_iterator character = STRING.begin(); character < STRING.end() && condition == true; character++) { // goes through STR's characters until it finds a character outside of the list or until they're no more characters
		if (has_char_in_string(*character, LIST) == false) { condition = false; } // found a character that's not in the list
	}

	return condition;
}

bool has_char_in_string(const char CHARACTER, const string STRING) {
	if ((STRING.find(CHARACTER)) != string::npos) { return true; } // if the character is in the string
	return false;
}

bool is_upper_case(char character) {
	if (character >= 'A' && character <= 'Z') { return true; }
	return false;
}

void display_intro() {
	cout << "You are a warlock that owns a 'linking' business. You are making magical 'links' between two objects so that one can affect the other, like a voodoo doll's link to its victim.\n\n"; // explains your business
	cout << "You have a limited amount of failiures you can make with your custommers. Refusing to create the customer's link out right will not count as a failiure\n\n"; // explaining how you can loose
	cout << "If you aggree to create their link, they would want to know how strong of a link you can create. Because they came to your shop for a decent linking, there is a chance they will get upset over how low of a link you can make. They will also get upset by if the link you made for them is weaker than they agreed to\n\n"; // explains what makes customers upset
	cout << "To link one object to another, you need to make the word of the object you are forming the link with, the 'material word', resemble the word of the object you are linking it too, the 'model'. The act of rearranging the material word to resemble the model is 'molding' the word\n\n"; // establishes how bindings are made
	cout << "for example, you are linking a doll to a rock. To make the word doll resemble rock, you can mold it into 'lood'.\n\n"; // binding example
	cout << "Because the mold and the model are the same size, the link automatically becomes stronger. Because the letters 'l' and 'r' both have a single vertical line, the letters will somewhat make a link. The model and the mold both have 'o' as a second letter, creating a strong link. 'c' and 'o' are circular so it makes a weak link. 'd' and 'k' have a verticle line so it makes a weak link. If the two letters do not resemble at all, the letters will not link. The resulting link strength of the two objects is be 80%.\n\n"; // How the links strength is determined
	cout << "You know everything that you need to know. Good luck.";
	system("pause");
	return;
}

string get_molded_word(const string MODEL, const string MATERIAL) {
	const string PRESENTED_MATERIAL = get_presentable_string(MATERIAL); // stores the letters of 'material' in alphabetical order
	string molded_word; // declares where the molded word is stored


	cout << "The model word:'" << MODEL << "'\n";

	// shows the user the letters they can use
	cout << "accepted letters:";
	for (auto letter : PRESENTED_MATERIAL) { cout << letter << " "; }
	cout << endl;

	//gets the molded words from the user
	cout << "Enter your molded word: ";
	molded_word = get_exclusive_string_input(MATERIAL, MODEL.size());


	return molded_word;
}

float get_molds_accuracy_percentage(const string MODEL, const string MOLD) {
	const float SAME_SIZE_POINTS = 1.0; // the points rewarded for having the mold the same size as the model
	const float MAX_POINTS = SAME_SIZE_POINTS + MODEL.size(); // the maximum amount of points the user can earn

	float accuracy_points = 0.0; // the amount of points the user has earned so far

	accuracy_points += (SAME_SIZE_POINTS + MODEL.size() - MOLD.size()); // adds the points depending on how similar the mold's size is to the model

	// compares the model to the mold
	for (int i = 0; i < MODEL.size(); i++) { // goes through all the model's characters
		if (MODEL[i] == MOLD[i]) { accuracy_points++; } // adds one point if the two characters are the same
		if (diff_chars_look_similar(MODEL[i], MOLD[i])) { accuracy_points += 0.5; } // adds half a point if two of the characters look similar
	}
	return (accuracy_points / MAX_POINTS) * 100;
}

bool diff_chars_look_similar(const char A, const char B) {
	bool condition = false;

	vector<string> const GROUPED_SIMILAR_CHARACTERS = { // stores groups of characters based on their similar characteristics
		"cenouCGOQU", // is circular
		"abcdgpquBDPR", // has hump
		"kuvwxyHKUVWX", // more than one points upward
		"ji", // has a dot
		"cegjlrstyCJSU", // has a hook
		"ftzEFLTZ", // has outward horizontal line
		"swzKMNSWZ", // has zigzag
		"hkmnwxAHKMNRWX", // has 'legs'
		"bdhikprBDFIKLPTY" // has one vertical line
	};

	// itterates through group until it finds similar characteristics between A and B or until the itterator ends
	for (vector<string>::const_iterator groups = GROUPED_SIMILAR_CHARACTERS.begin(); groups < GROUPED_SIMILAR_CHARACTERS.end() && condition == false; groups++) {
		if (has_char_in_string(A, *groups) && has_char_in_string(B, *groups)) { condition = true; }
	}
	return condition;
}

string get_random_model() {
	vector<string> const MODELS = { "William", "Henry", "Jonh", "boulder", "tree" }; // potential models

	return MODELS[rand() % MODELS.size()]; // returns one of the model
}

string get_random_material_word() {
	vector<string> const MATERIAL_WORD = { "apple", "rock", "doll", "stick", "broom" }; // potential material words

	return MATERIAL_WORD[rand() % MATERIAL_WORD.size()]; // returns one of the material words
}

void display_binding_request(const string MODEL, const string MATERIAL) {
	cout << "A person walks into your store with ";

	// corrects grammar
	if (is_upper_case(MATERIAL[0]) == false) {
		if (has_char_in_string(MATERIAL[0], "aeiou")) { cout << "an "; }
		else { cout << "a "; }
	}
	cout << MATERIAL << ". They request that you bind it to ";

	if (is_upper_case(MODEL[0]) == false) {
		if (has_char_in_string(MODEL[0], "aeiou")) { cout << "an "; }
		else { cout << "a "; }
	}
	cout << MODEL << ".\n";
	return;
}

string get_presentable_string(string str) {
	string presentable_string;
	sort(str.begin(), str.end()); // alphabatizes the word

	for (char letter : str) { if (has_char_in_string(letter, presentable_string) == false) { presentable_string += letter; } } // adds the string's letter if it isn't already within presentable_string
	return presentable_string;
}