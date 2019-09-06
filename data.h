#include <vector>
#include <string>

using std::string;
using std::vector;


class MultipleChoice
{
	private:
		struct ExerciseData
		{
			string question = "-1";
			vector<string> choices;
			string answer = "-1";
		};
		vector<ExerciseData> listExercise;
		int total_questions = 0;
		
	public:

		void retrieve_data(string file_name, bool &status);
		string get_questions(int question_number);
		string get_answer(int question_number);
		string get_choices(int question_number, int choice_number); //ONLY from 1-4 for choice_number, for displaying purposes
		int get_total_questions() { return total_questions; };
};

