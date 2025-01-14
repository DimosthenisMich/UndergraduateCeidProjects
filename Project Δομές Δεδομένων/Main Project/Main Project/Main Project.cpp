#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

void Merge(int input_array[], int left_border, int  middle, int right_border)
{
	{
		int right_array_counter, left_array_counter, index;
		int left_size = middle - left_border + 1;
		int right_size = right_border - middle;

		/* create temp arrays */
		int *Temp_Left_array = new int[left_size];
		int *Temp_Right_array = new int[right_size];

		/* Copy data to temp arrays Temp_Left_array[] and Temp_Right_array[] */
		for (right_array_counter = 0; right_array_counter < left_size; right_array_counter++)
		{
			Temp_Left_array[right_array_counter] = input_array[left_border + right_array_counter];
		}
		for (left_array_counter = 0; left_array_counter < right_size; left_array_counter++)
		{
			Temp_Right_array[left_array_counter] = input_array[middle + 1 + left_array_counter];
		}
		/* Merge the temp arrays back into input_array[left_border..right_border]*/
		right_array_counter = 0; // Initial index of first subarray
		left_array_counter = 0; // Initial index of second subarray
		index = left_border; // Initial index of merged subarray
		while (right_array_counter < left_size && left_array_counter < right_size)
		{
			if (Temp_Left_array[right_array_counter] <= Temp_Right_array[left_array_counter])
			{
				input_array[index] = Temp_Left_array[right_array_counter];
				right_array_counter++;
			}
			else
			{
				input_array[index] = Temp_Right_array[left_array_counter];
				left_array_counter++;
			}
			index++;
		}

		/* Copy the remaining elements of Temp_Left_array[], if there
		are any */
		while (right_array_counter < left_size)
		{
			input_array[index] = Temp_Left_array[right_array_counter];
			right_array_counter++;
			index++;
		}

		/* Copy the remaining elements of Temp_Right_array[], if there
		are any */
		while (left_array_counter < right_size)
		{
			input_array[index] = Temp_Right_array[left_array_counter];
			left_array_counter++;
			index++;
		}
	}
	/* left_border is for left index and right_border is right index of the
	sub-array of input_array to be sorted */
}

void MergeSort(int input_array[], int left_border, int right_border)
{
	int middle;
	if (left_border < right_border)
	{
		middle = (left_border + right_border) / 2;
		MergeSort(input_array, left_border, middle);
		MergeSort(input_array, middle + 1, right_border);
		Merge(input_array, left_border, middle, right_border);
	}
}

bool LinearSearch(vector<int>& input_vector, int element_for_search)
{
	int counter = 0, position = -1;
	for (counter = 0; counter<input_vector.size(); counter++)
	{
		if (input_vector[counter] == element_for_search)
		{
			cout << "The integer " << element_for_search << " was found at the [" << counter << "]." << endl;
			return true;
		}
	}
	cout << "The integer " << element_for_search << " wasn't found." << endl;
	return false;
}

bool BinarySearch(vector<int>& input_vector, int element_for_search, int left_border, int right_border)
{
	if (right_border <= left_border)
	{
		cout << "The integer " << element_for_search << " wasn't found." << endl;
		return false;
	}
	else
	{
		int middle = left_border + (right_border - left_border) / 2;
		if (element_for_search == input_vector[middle])
		{

			cout << "The integer " << element_for_search << " was found at the [" << middle << "]." << endl;
			return true;
		}
		else
		{
			if (element_for_search > input_vector[middle])
			{
				middle++;
				BinarySearch(input_vector, element_for_search, middle, right_border);
			}
			else
			{
				BinarySearch(input_vector, element_for_search, left_border, middle);
			}
		}
	}
}

bool InterpolationSearch(vector<int>& input_vector, int element_for_search, int right_border)
{
	int possible_position, left_border = 0;
	while (element_for_search >= input_vector[left_border] && element_for_search <= input_vector[right_border] && left_border <= right_border)
	{
		possible_position = left_border + abs((element_for_search - input_vector[left_border])*(right_border - left_border) / (input_vector[right_border] - input_vector[left_border]));
		if (input_vector[possible_position] == element_for_search)
		{
			cout << "The integer " << element_for_search << " was found at the [" << possible_position << "]." << endl;
			return true;
		}
		else
		{
			if (input_vector[possible_position] < element_for_search)
			{
				left_border = ++possible_position;
			}
			else
			{
				right_border = --possible_position;
			}
		}
	}
	cout << "The integer " << element_for_search << " wasn't found." << endl;
	return false;
}

typedef struct red_black_tree_node
{
	bool colour;
	struct red_black_tree_node *right_pointer, *left_pointer, *parent_pointer;
	int value;
}red_black_tree_node;

void Red_Black_Tree_Left_Rotation(red_black_tree_node* &root_node, red_black_tree_node* input_node, red_black_tree_node* &null_node)
{
	red_black_tree_node* active_node = input_node->right_pointer;
	input_node->right_pointer = active_node->left_pointer;
	if (active_node->left_pointer != null_node)
	{
		active_node->left_pointer->parent_pointer = input_node;
	}
	active_node->parent_pointer = input_node->parent_pointer;
	if (input_node->parent_pointer == null_node)
	{
		root_node = active_node;
	}
	else
	{
		if (input_node == input_node->parent_pointer->left_pointer)
		{
			input_node->parent_pointer->left_pointer = active_node;
		}
		else
		{
			input_node->parent_pointer->right_pointer = active_node;
		}
	}
	active_node->left_pointer = input_node;
	input_node->parent_pointer = active_node;
}

void Red_Black_Tree_Right_Rotation(red_black_tree_node* &root_node, red_black_tree_node* active_node, red_black_tree_node* &null_node)
{
	red_black_tree_node* input_node = active_node->left_pointer;
	active_node->left_pointer = input_node->right_pointer;
	if (input_node->right_pointer != null_node)
	{
		input_node->right_pointer->parent_pointer = active_node;
	}
	input_node->parent_pointer = active_node->parent_pointer;
	if (active_node->parent_pointer == null_node)
	{
		root_node = input_node;
	}
	else
	{
		if (active_node == active_node->parent_pointer->left_pointer)
		{
			active_node->parent_pointer->left_pointer = input_node;
		}
		else
		{
			active_node->parent_pointer->right_pointer = input_node;
		}
	}
	input_node->right_pointer = active_node;
	active_node->parent_pointer = input_node;
}

bool Red_Black_Tree_Search(red_black_tree_node* &root_node, int element_for_search, red_black_tree_node* &null_node)
{
	red_black_tree_node* Node_For_Search = root_node;
	while (Node_For_Search != null_node)
	{
		if (Node_For_Search->value == element_for_search)
		{
			cout << "The integer " << element_for_search << " was found." << endl;
			return true;
		}
		else
		{
			if (element_for_search < Node_For_Search->value)
			{
				Node_For_Search = Node_For_Search->left_pointer;
			}
			else
			{
				if (element_for_search > Node_For_Search->value)
				{
					Node_For_Search = Node_For_Search->right_pointer;
				}
			}
		}
	}
	cout << "The integer " << element_for_search << " wasn't found." << endl;
	return false;
}

void Red_Black_Tree_Fixing(red_black_tree_node* &root_node, red_black_tree_node* grandparent_node, red_black_tree_node* &null_node)
{
	while (grandparent_node->parent_pointer->colour == false)
	{
		if (grandparent_node->parent_pointer == grandparent_node->parent_pointer->parent_pointer->left_pointer)
		{
			red_black_tree_node* active_node = grandparent_node->parent_pointer->parent_pointer->right_pointer;
			if (active_node->colour == false)
			{
				grandparent_node->parent_pointer->colour = true;
				active_node->colour = true;
				grandparent_node->parent_pointer->parent_pointer->colour = false;
				grandparent_node = grandparent_node->parent_pointer->parent_pointer;
			}
			else 
			{
				if (grandparent_node == grandparent_node->parent_pointer->right_pointer)
				{
					grandparent_node = grandparent_node->parent_pointer;
					Red_Black_Tree_Left_Rotation(root_node, grandparent_node, null_node);

					grandparent_node->parent_pointer->colour = true;
					grandparent_node->parent_pointer->parent_pointer->colour = false;
					Red_Black_Tree_Right_Rotation(root_node, grandparent_node->parent_pointer->parent_pointer, null_node);
				}
				else
				{
					grandparent_node->parent_pointer->colour = true;
					grandparent_node->parent_pointer->parent_pointer->colour = false;
					Red_Black_Tree_Right_Rotation(root_node, grandparent_node->parent_pointer->parent_pointer, null_node);
				}
			}
		}
		else
		{
			red_black_tree_node* active_node = grandparent_node->parent_pointer->parent_pointer->left_pointer;
			if (active_node->colour == false)
			{
				grandparent_node->parent_pointer->colour = true;
				active_node->colour = true;
				grandparent_node->parent_pointer->parent_pointer->colour = false;
				grandparent_node = grandparent_node->parent_pointer->parent_pointer;
			}
			else
			{
				if (grandparent_node == grandparent_node->parent_pointer->left_pointer)
				{
					grandparent_node = grandparent_node->parent_pointer;
					Red_Black_Tree_Right_Rotation(root_node, grandparent_node, null_node);
					grandparent_node->parent_pointer->colour = true;
					grandparent_node->parent_pointer->parent_pointer->colour = false;
					Red_Black_Tree_Left_Rotation(root_node, grandparent_node->parent_pointer->parent_pointer, null_node);
				}
				else
				{
					grandparent_node->parent_pointer->colour = true;
					grandparent_node->parent_pointer->parent_pointer->colour = false;
					Red_Black_Tree_Left_Rotation(root_node, grandparent_node->parent_pointer->parent_pointer, null_node);
				}
			}
		}
	}
	root_node->colour = true;
}

void Red_Black_Tree_Insertion(red_black_tree_node* &root_node, red_black_tree_node* grandparent_node, red_black_tree_node* &null_node)
{
	cout << "The integer " << grandparent_node->value << " has been inserted successfully." << endl;
	red_black_tree_node* active_node = null_node;
	red_black_tree_node* input_node = root_node;
	while (input_node != null_node)
	{
		active_node = input_node;
		if (grandparent_node->value < active_node->value)
		{
			input_node = input_node->left_pointer;
		}
		else
		{
			input_node = input_node->right_pointer;
		}
	}
	
	grandparent_node->parent_pointer = active_node;

	if (active_node == null_node)
	{
		root_node = grandparent_node;
	}
	else
	{
		if (grandparent_node->value < active_node->value)
		{
			active_node->left_pointer = grandparent_node;
		}
		else
		{
			active_node->right_pointer = grandparent_node;
		}
	}
	grandparent_node->left_pointer = null_node;
	grandparent_node->right_pointer = null_node;
	grandparent_node->colour = false;
	Red_Black_Tree_Fixing(root_node, grandparent_node, null_node);
}

void UpdateCsvFile(float input_array[4][1000])
{
	int rows, columns;
	ofstream times_csvfile;
	times_csvfile.open("C:/Users/jimak/Desktop/Project Domes Dedomenon/Main Project/executiontimes.csv", ios::in | ios::out);
	if (times_csvfile.is_open())
	{
		for (rows = 0; rows < 4; rows++)
		{
			for (columns = 0; columns < 1000; columns++)
			{
				times_csvfile << input_array[rows][columns] << ";";
			}
			times_csvfile << "\n";
		}
		cout << "The execution times csv file has been updated successfully." << endl;
	}
	else
	{
		cout << "<executiontimes.csv> file not found." << endl;
		system("pause");
	}
	times_csvfile.close();
}

int main()
{
	red_black_tree_node* null_node = new red_black_tree_node;
	null_node->colour = true;
	red_black_tree_node* root_node = null_node;
	int counter, choice = 0, element_for_search, searching_mode;
	clock_t begin, end;
	float execution_time;
	vector<int> integers_vector;
	fstream integersfile;
	integersfile.open("C:/Users/jimak/Desktop/Project Domes Dedomenon/Main Project/integers.txt", ios::in | ios::out);
	if (integersfile.is_open())
	{
		cout << "Opening integers file and filling vector.Pleaze wait." << endl;
		string line;
		while (getline(integersfile, line))
		{
			integers_vector.push_back(stoi(line));
		}
		integersfile.close();
	}
	else
	{
		cout << "<integers.txt> file not found." << endl;
		system("pause");
	}
	int* integers_array = &integers_vector[0];
	MergeSort(integers_array, 0, integers_vector.size() - 1);
	if (is_sorted(integers_vector.begin(), integers_vector.end()))
	{
		cout << "The file has been sorted." << endl;
	}
	else
	{
		cout << "The file hasn't been sorted.Pleaze try sorting it again." << endl;
	}
	for (int counter = 0; counter < integers_vector.size(); counter++)
	{
		red_black_tree_node* node_for_insertion = new red_black_tree_node;
		node_for_insertion->left_pointer = null_node;
		node_for_insertion->right_pointer = null_node;
		node_for_insertion->parent_pointer = null_node;
		node_for_insertion->colour = false;
		node_for_insertion->value = integers_vector[counter];
		Red_Black_Tree_Insertion(root_node, node_for_insertion, null_node);
	}
	cout << "The Red-Black Tree has been created and fixed." << endl;
	while (choice != 7)
	{
		cout << "For linear search, choose 1." << endl << "For binary search, choose 2." << endl << "For interpolation search, choose 3." << endl << "For searching the Red-Black tree, choose 4." << endl << "To insert a new node to the Red-Black Tree, choose 5." << endl << "To update the CSV file with new execution times, choose 6." << endl << "To exit the search menu, choose 7." << endl;
		do
		{
			cin >> choice;
		} while (choice <= 0 || choice > 7);
		if (choice == 6)
		{
			float times[4][1000];
			for (counter = 0; counter < 1000; counter++)
			{
				element_for_search = rand() % 1000000;
				for (searching_mode = 0; searching_mode < 4; searching_mode++)
				{
					switch (searching_mode)
					{
					case 0:
					{
						begin = clock();
						LinearSearch(integers_vector, element_for_search);
						end = clock();
						break;
					}
					case 1:
					{
						begin = clock();
						BinarySearch(integers_vector, element_for_search, 0, integers_vector.size() - 1);
						end = clock();
						break;
					}
					case 2:
					{
						begin = clock();
						InterpolationSearch(integers_vector, element_for_search, integers_vector.size() - 1);
						end = clock();
						break;
					}
					case 3:
					{
						begin = clock();
						Red_Black_Tree_Search(root_node, element_for_search, null_node);
						end = clock();
						break;
					}
					}
					execution_time = (float)(end - begin) * 1000 / (CLOCKS_PER_SEC);
					times[searching_mode][counter] = execution_time;
				}
			}
			cout << "Executed 1000 searches for each searching mode." << endl;
			UpdateCsvFile(times);
		}
		else
		{
			if (choice == 7)
			{
				cout << "Exiting search menu." << endl;
			}
			else
			{
				if (choice == 5)
				{
					cout << "Enter the integer you want to insert to the Red-Black Tree." << endl;
					cin >> element_for_search;
					red_black_tree_node* node_for_insertion = new red_black_tree_node;
					node_for_insertion->left_pointer = null_node;
					node_for_insertion->right_pointer = null_node;
					node_for_insertion->parent_pointer = null_node;
					node_for_insertion->colour = false;
					node_for_insertion->value = element_for_search;
					Red_Black_Tree_Insertion(root_node, node_for_insertion, null_node);
				}
				else
				{
					cout << "Enter the integer you want to search for." << endl;
					cin >> element_for_search;
					switch (choice)
					{
					case 1:
					{
						LinearSearch(integers_vector, element_for_search);
						break;
					}
					case 2:
					{
						BinarySearch(integers_vector, element_for_search, 0, integers_vector.size() - 1);
						break;
					}
					case 3:
					{
						InterpolationSearch(integers_vector, element_for_search, integers_vector.size() - 1);
						break;
					}
					case 4:
					{
						Red_Black_Tree_Search(root_node, element_for_search, null_node);
						break;
					}
					}
				}
			}
		}
	}
	return 0;
}