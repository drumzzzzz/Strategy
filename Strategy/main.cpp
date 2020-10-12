// Strategy Design Pattern Project
// Iterates operations from file and executes the strategy on a randomly generated integer array.
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string.h>
#include "FileIO.h"
using namespace std;

// Array extents
#define ARRAY_SIZE 20
#define ARRAY_MAX 100

// Strategy abstract polymorphic base
class Strategy
{
public:
	virtual void doOperation(vector<int>* values) = 0;
};

// Iterate array and display it's contents with a message
void DisplayValues(const string msg, vector<int>* values)
{
	cout << msg << ": ";
	for (unsigned int i = 0; i < values->size(); i++)
	{
		cout << values->at(i) << " ";
	}
	cout << endl;
}

// Generate a random array by size and maximum values
class Operation_Generate : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		if (values->size() >= ARRAY_SIZE * 5)
		{
			DisplayValues("List Maximum Reached", values);
			return;
		}

		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			values->push_back((rand() % ARRAY_MAX));
		}

		DisplayValues("Added Random Values", values);
	}
};

// Clear values
class Operation_Clear : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		values->clear();
		DisplayValues("Cleared Values", values);
	}
};

// Randomly shuffle array
class Operation_Shuffle : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		random_shuffle(values->begin(), values->end());
		DisplayValues("Shuffled Results", values);
	}
};

// Sort array ascending
class Operation_Ascending : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		sort(values->begin(), values->end());
		DisplayValues("Sorted Ascending", values);
	}
};

// Sort array descending
class Operation_Descending : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		sort(values->begin(), values->end(), greater<>());
		DisplayValues("Sorted Descending", values);
	}
};

// Calculate and display all minimum values in array
class Operation_Minimum : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		int min = values->at(0);
		int value;
		vector<int>* min_values = new vector<int>();

		for (unsigned int i = 0; i < values->size(); i++)
		{
			value = values->at(i);

			if (value == min)
			{
				min_values->push_back(value);
			}
			else if (value < min)
			{
				min = value;
				min_values->clear();
				min_values->push_back(value);
			}
		}
		DisplayValues("Minimum Value(s)", min_values);
	}
};

// Calculate and display all maximum values in array
class Operation_Maximum : public Strategy
{
public:
	void doOperation(vector<int>* values)
	{
		int max = values->at(0);
		int value;
		vector<int>* max_values = new vector<int>();

		for (unsigned int i = 0; i < values->size(); i++)
		{
			value = values->at(i);

			if (value == max)
			{
				max_values->push_back(value);
			}
			else if (value > max)
			{
				max = value;
				max_values->clear();
				max_values->push_back(value);
			}
		}
		DisplayValues("Maximum Value(s)", max_values);
	}
};

// Strategy pattern context methods
class Context : public FileIO
{
private:
	Strategy* strategy;

public:
	Context()
	{}

	Context(Strategy* new_strategy)
	{
		strategy = new_strategy;
	}

	void changeStrategy(Strategy* new_strategy)
	{
		strategy = new_strategy;
	}

	void executeStrategy(vector<int>* values)
	{
		strategy->doOperation(values);
	}

	vector<string>* ReadOperations()
	{
		return fileRead("operations.txt");
	}
};

int main()
{
	// Init objects and array
	Context* context = new Context();
	Operation_Generate generate_strategy;
	Operation_Clear clear_strategy;
	Operation_Ascending ascending_strategy;
	Operation_Descending descending_strategy;
	Operation_Shuffle shuffle_strategy;
	Operation_Minimum minimum_strategy;
	Operation_Maximum maximum_strategy;
	srand(time(nullptr));
	vector<int>* values = new vector<int>();

	// Read the operations list from file
	vector<string>* operations = context->ReadOperations();

	// Exit if invalid
	if (operations == nullptr || operations->empty())
	{
		cerr << "No operations found!" << endl;
		return -1;
	}

	// Iterate operations and execute associated strategy if valid
	for (unsigned int i = 0; i < operations->size(); i++)
	{
		const char* operation = operations->at(i).c_str();
		bool AllowEmpty = false;

		if (strcmp(operation, "generate") == 0)
		{
			context->changeStrategy(&generate_strategy);
			AllowEmpty = true;
		}
		else if (strcmp(operation, "clear") == 0)
		{
			context->changeStrategy(&clear_strategy);
			AllowEmpty = true;
		}
		else if (strcmp(operation, "ascending") == 0)
			context->changeStrategy(&ascending_strategy);
		else if (strcmp(operation, "descending") == 0)
			context->changeStrategy(&descending_strategy);
		else if (strcmp(operation, "shuffle") == 0)
			context->changeStrategy(&shuffle_strategy);
		else if (strcmp(operation, "minimum") == 0)
			context->changeStrategy(&minimum_strategy);
		else if (strcmp(operation, "maximum") == 0)
			context->changeStrategy(&maximum_strategy);
		else // If an invalid operation found
		{
			cout << "Skipping invalid operation '" << operation << "'" << endl;
			continue;
		}

		// If operation requires a populated list and it's empty
		if (!AllowEmpty && values->empty())
		{
			cout << "Skipping operation '" << operation << "' -> list was empty" << endl;
			continue;
		}

		// Perform the strategy operation
		context->executeStrategy(values);
	}
	return 0;
}


