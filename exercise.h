#include <string>

using std::string;

class Exercise
{
	private:
		struct questionNode
		{
			string question = "-1";
			string answer = "-1"; //user's answer
			int ID = -1; //the order of the question in the question pool
			int question_number = -1; //the order of the question in the quiz.
			bool correct = false;
			questionNode *next = NULL;
		};
		
		questionNode *head_ptr;
		questionNode *traverse_ptr; //set traverse_ptr = head_ptr initially
		

	public:
		Exercise();
		//exercise(string question_input, string answer_input);
		string get_answer() { return traverse_ptr->answer; };
		void set_answer(string answer_input) { traverse_ptr->answer = answer_input; };
		void set_result(bool status) { traverse_ptr->correct = status; };
		bool get_result() { return traverse_ptr->correct; };
		string get_question() { return traverse_ptr->question; };
		int get_ID() { return traverse_ptr->ID; };
		void set_order(int order) { traverse_ptr->question_number = order; };
		int get_order() { return traverse_ptr->question_number; };
		

		void reset_traverseptr() { traverse_ptr = head_ptr; };
		void delete_head();
		void add_question(string question_input,int ID_input);
		void next_question() {traverse_ptr = traverse_ptr->next;};
		void clear_list();
		~Exercise();

		bool is_headptr()
		{
			if (head_ptr == NULL)
				return true;
			else
				return false;
		}
		bool is_traverse()
		{
			if (traverse_ptr == NULL)
				return true;
			else
				return false;
		}

		
};