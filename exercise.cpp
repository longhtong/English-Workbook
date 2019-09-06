#include "exercise.h"
#include <string>

using std::string;

Exercise::Exercise()
{
	head_ptr = NULL;
	traverse_ptr = head_ptr;
}

void Exercise::delete_head()
{
	if (head_ptr != NULL)
	{
		questionNode *temp_ptr = head_ptr;
		head_ptr = head_ptr->next;
		traverse_ptr = head_ptr;
		delete temp_ptr;
	}
}

void Exercise::add_question(string question_input, int ID_input)
{
	questionNode *temp_ptr = new questionNode;
 
	temp_ptr->question = question_input;
	temp_ptr->answer = "-1";
	temp_ptr->ID = ID_input;
	temp_ptr->next = head_ptr;
	head_ptr = temp_ptr;
	traverse_ptr = head_ptr;
	
}

void Exercise::clear_list()
{
	if (traverse_ptr != head_ptr)
		reset_traverseptr();

	while (head_ptr != NULL)
		delete_head();
}
Exercise::~Exercise()
{
	
	if (traverse_ptr != head_ptr)
		reset_traverseptr();
	while (head_ptr != NULL)
		delete_head();
}

