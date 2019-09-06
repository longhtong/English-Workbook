#include "exercise.h"
#include "data.h"
#include <iostream>
#include <string>
#include <stdlib.h>     
#include <time.h>
#include <iomanip>


using std::string;	using std::setw;
using std::cout;	using std::right;
using std::cin;		using std::left;
using std::endl;
using std::getline;

string get_response(string prompt);
void display_MC(string question, MultipleChoice questions, int id);
void MC_quiz(Exercise &test, MultipleChoice questions);
void get_MC_answers(Exercise &test, string &user_response);
int MC_grading(Exercise &test, MultipleChoice question_pool);
void display_MC_result(Exercise &quiz, MultipleChoice question_pool, int grade);
bool get_yes_no(char &input);
int randomnize_ID(int total_questions, int ID_list[], int current_index);

const int MC_SIZE = 10; //total multiple-choice questions
const int MIN_MC_OPTIONS = 4;
const string MC_FILE = "questions-ADJvADV.dat";

int main()
{

	Exercise MC_test; //contains multiple-choice questions for the test
	MultipleChoice adv_adj; //the question pool
	int	question_ID = 0, //store question's ID in the pool
		MC_grade = 0,  //score of the multiple-choice portion
		total_MC = 0;  //the total questions in the pool/text file
	bool file_status = false, //check whether is present
		loop_status = false;  //check if user wants to take the quiz again
	char user_input;  //response from the user
	int ID_list_MC[MC_SIZE]; //this array contains all ID of selected questions. It is used for identical questions checking
	unsigned seed = time(0); //randomnize number
	srand(seed);
	

	adv_adj.retrieve_data(MC_FILE, file_status);
	total_MC = adv_adj.get_total_questions();


	do {
		
		if (file_status == false)
		{
			break; //if the text file cannot be opened. Stop the program
		}

		for (int i = 0; i < MC_SIZE; i++)//randomly select questions from the pool and assign them to the MC_test object 
		{
			question_ID = randomnize_ID(total_MC, ID_list_MC, i);

			MC_test.add_question(adv_adj.get_questions(question_ID), question_ID);
		}


		MC_quiz(MC_test, adv_adj); //display questions, gather and store user's answers in MC_test


		MC_grade = MC_grading(MC_test, adv_adj); // grade the quiz

		display_MC_result(MC_test, adv_adj, MC_grade); // display the result and correction

		//Clear list 
		MC_test.clear_list();
		

		cout << " Would you like to retake the quiz? (Y for yes, N for no) ";
		cin >> user_input;
		loop_status = get_yes_no(user_input);

		if (loop_status)
		{
			cout << "*************************************************************" << endl;
			cout << endl << endl << endl;
		}

		
		
	} while (loop_status == true);


	system("pause");
}

string get_response(string prompt)
{
	string response;

	cout << endl;
	cout << prompt;
	getline(cin, response);
	cout << endl;

	return response;
}

void display_MC(string question, MultipleChoice questions, int id)
{

	cout << question << endl;
	for (int i = 1; i <= MIN_MC_OPTIONS; i++)
	{
		switch (i)
		{
		case 1:
			cout << "a." << left << setw(30) << questions.get_choices(id, i);
			break;
		case 2:
			cout << right << setw(10) << "b." << questions.get_choices(id, i);
			cout << endl;
			break;
		case 3:
			cout << "c." << left << setw(30) << questions.get_choices(id, i);
			break;
		case 4:
			cout << right << setw(10) << "d." << questions.get_choices(id, i);
			cout << endl;
			break;

		}
	}
}

void MC_quiz(Exercise &test, MultipleChoice questions)
{
	test.reset_traverseptr();

	string response;
	for (int i = 0; i < MC_SIZE; i++)
	{
		//display question
		//display choices
		//gather answer. answers will be stored in "test"
		//next_question()


		test.set_order(i + 1);
		cout << i + 1 << ". ";
		display_MC(test.get_question(), questions, test.get_ID());
		cout << endl;
		//gather and store answer
		cout << "Your answer: ";
		cin >> response;

		get_MC_answers(test, response);

		
		test.next_question();
	}
	cout << endl;
}

void get_MC_answers(Exercise &quiz, string &user_response)
{
	if (user_response[0] >= 97 && user_response[0] <= 100)
	{
		quiz.set_answer(user_response);
	}
	else if (user_response[0] >= 65 && user_response[0] <= 68)
	{
		user_response[0] = user_response[0] + 32;
		quiz.set_answer(user_response);
	}
	else
	{
		cout << "Invalid input. ";
		cout << "Please try again: ";
		cin >> user_response;
		get_MC_answers(quiz, user_response);
	}
}

int MC_grading(Exercise &quiz, MultipleChoice question_pool)
{
	quiz.reset_traverseptr();
	int grade = 0;
	string answer,
		key;
	for (int i = 0; i < MC_SIZE; i++)
	{
		answer = quiz.get_answer(),
		key = question_pool.get_answer(quiz.get_ID());

		if (answer == key)
		{
			quiz.set_result(true);
			grade++;
		}
		else
		{
			quiz.set_result(false);
		}
		quiz.next_question();
	}

	return grade;
}

void display_MC_result(Exercise &quiz, MultipleChoice question_pool, int grade)
//display result of the multiple-choice portion and correct answers, if any
{
	cout << endl;
	cout << "**********************************************" << endl;
	cout << "Your score is " << grade << " out of " << MC_SIZE
		<< " for the multiple-choice portion." << endl;
	if (grade == 10)
	{
		cout << "Well done!!!" << endl;
	}
	else
	{
		cout << "Here are answers to questions that you missed: " << endl;

		quiz.reset_traverseptr();
		for (int i = 0; i < MC_SIZE; i++)
		{
			if (quiz.get_result() == false)
			{
				cout << quiz.get_order() << ". " << question_pool.get_answer(quiz.get_ID()) << endl;
			}
			quiz.next_question();
		}
	}
}

bool get_yes_no(char &input)
{
	
	if (input == 'Y' || input == 'y')
		return true;
	else if (input == 'N' || input == 'n')
		return false;
	else
	{
		cout << "Invalid input. Please try again: ";
		cin >> input;
		return get_yes_no(input);
	}

}

int randomnize_ID(int total_questions, int ID_list[], int current_index)
{
	
	int ID = 0;
	bool duplicate = false;
	

	do
	{
		ID = rand() % total_questions + 1;
		for(int i = 0; i < current_index;i++)
		{

			if (ID == ID_list[i])
			{
				duplicate = true;
				break;
			}
			else
				duplicate = false;
		}
		if (duplicate != true)
			ID_list[current_index] = ID;

		
	} while (duplicate == true);

	return ID;
}
