#include "data.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::fstream;
using std::ios;
using std::cout;
using std::cin;
using std::getline;
using std::endl;

string MultipleChoice::get_questions(int question_number)
{
	return listExercise[question_number - 1].question;

}

string MultipleChoice::get_answer(int question_number)
{
	return listExercise[question_number - 1].answer;

}

string MultipleChoice::get_choices(int question_number, int choice_number)
{
	return listExercise[question_number - 1].choices[choice_number - 1];

}

void MultipleChoice::retrieve_data(string file_prompts, bool &status)
{
	fstream in_file(file_prompts, ios::in);
	string in_data;
	int count = 0; //the total index number of the vectors
	int total = 0; //the total number of questions
	if (in_file.fail())
	{
		cout << "The file is not found." << endl;
		status = false;
		return;
	}

	status = true;

	//read the total numbers of questions in the file
	in_file >> total;
	total_questions = total;
	
	
	in_file.ignore();

	listExercise.push_back(ExerciseData());
	while (!in_file.fail()) //read question and choices and answer
	{
		getline(in_file, in_data);
		listExercise[count].question = in_data; //read question


		for (int j = 0; j < 4; j++) //read choices
		{
			getline(in_file, in_data);
			listExercise[count].choices.push_back(in_data);
		}


		getline(in_file, in_data);
		listExercise[count].answer = in_data; //read answer
		count++;
		in_file.flush();
		listExercise.push_back(ExerciseData()); //next question
	}

	in_file.close();
}