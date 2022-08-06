/*
El Hadji Omar Bane
Header and Source
8/1/2022
*/

#include<iostream>
#include <stdlib.h> // gives me access to rand
#include <time.h> // gets access to time
#include "utility_functions.h" // my header
#include<string>

using namespace std;


int main() {
	srand(time(NULL)); // initializes randomness

	const int MISTAKES_LIMIT = 4; // the maximum amount of mistakes the user can make in the binding strength prediction
	const int AUTO_ACCEPT_PERCENT = 75; // the value at which the customer will automatically be content with the predicted binding strength

	string Model;
	string materialWord;
	string moldedWord;

	int usersResponse;
	int Score = 0; // tracks the satisfied customers the user has had
	int mistakes = 0; // tracks the amount of mistakes the user has made

	bool Running = true;

	display_intro();

	cout << "\nYou can fail " << MISTAKES_LIMIT << " times\n\n";
	while (MISTAKES_LIMIT > mistakes) {
		Model = get_random_model(); // stores a random model
		materialWord = get_random_material_word(); // stores a random material word

		// a request is made
		display_binding_request(Model, materialWord); // displays a binding request
		cout << "1.accept request\n2.decline request\n";
		usersResponse = get_integer_input(1, 2); // get the users response to the request

		if (usersResponse == 2) { cout << "They grumble while making their exit" << endl; } // the customers response

		else { // the user accepts the request
			cout << "They ask how strong you can make the binding\nenter a percent:";
			usersResponse = get_integer_input(0, 100); // gets the user's predicted percentage

			if ((rand() % AUTO_ACCEPT_PERCENT) > usersResponse) { // if the customer doesn't like the prediction
				mistakes++;
				cout << "The potential customer begins to complain about your prediction and makes their exit\n";
			}

			// the customer is alright with the prediction
			else { 
				cout << "You and the customer come to an agreement. They pay you for the binding and leave you to your craft\n";
				system("pause");
				cout << endl;
				moldedWord = get_molded_word(Model, materialWord);
				cout << "the link's strength: " << get_molds_accuracy_percentage(Model, moldedWord) << endl << endl;

				if(get_molds_accuracy_percentage(Model, moldedWord) < usersResponse){ // the binding strength was lower than what was agreed apon
					mistakes ++;
					cout << "The customer is displeased with the " << materialWord << "'s link. \nThey stomp out and never return to your store.";
				}
				// the user successfully binds the two objects
				else {
					Score++;
					cout << "The customer appears to be ecstatic about the results\nYour score is now " << Score << endl;
				}
			}
			cout << " You have " << MISTAKES_LIMIT - mistakes << " errors left\n"; // reminds the user how many mistakes they can make
		}
		system("pause");
		system("CLS");
	}

	cout << "GAME OVER\nYour score is:" << Score << endl;
	system("pause");

	return 0;
}
