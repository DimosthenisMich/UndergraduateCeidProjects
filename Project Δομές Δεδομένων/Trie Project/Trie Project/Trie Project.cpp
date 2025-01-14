#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>

using namespace std;

typedef struct Digital_Tree_Node
{
	Digital_Tree_Node* letters[26];//1 for each of the 26 latin alphabet letters.
	bool end_of_word;
}Digital_Tree_Node;

Digital_Tree_Node* Create_Digital_Tree_Node(void)//Create and initialize the Trie node.
{
	Digital_Tree_Node *DTNode = new Digital_Tree_Node;

	DTNode->end_of_word = false;

	for (int counter = 0; counter < 26; counter++)
	{
		DTNode->letters[counter] = NULL;
	}
	return DTNode;
}

void Digital_Tree_Insert(Digital_Tree_Node* root, string word)
{
	Digital_Tree_Node* next_node = root;

	for (int counter = 0; counter < word.length(); counter++)
	{
		int letter_position = tolower(word[counter]) - 97;//int value of the letter
		if (next_node->letters[letter_position] == NULL)
		{
			next_node->letters[letter_position] = Create_Digital_Tree_Node();
		}
		next_node = next_node->letters[letter_position];
	}
	next_node->end_of_word = true;
	cout << "The word << " << word << " >> has been inserted successfully." << endl;
}

bool Digital_Tree_Search(Digital_Tree_Node* root, string word)
{
	Digital_Tree_Node* next_node = root;

	for (int counter = 0; counter < word.length(); counter++)
	{
		int letter_position = tolower(word[counter]) - 97;//int value of the letter
		if (next_node->letters[letter_position] != NULL)
		{
			next_node = next_node->letters[letter_position];
		}
		else
		{
			cout << "The word << " << word << " >> wasn't found." << endl;
			return false;
		}
	}
	if (next_node->end_of_word == true)
	{
		cout << "The word << " << word << " >> was found." << endl;
		return true;
	}
	else
	{
		cout << "The word << " << word << " >> wasn't found." << endl;
		return false;
	}
}

bool Is_Leaf_Node(Digital_Tree_Node* node)//Check if a node is a leaf node.
{
	int counter;
	for (counter = 0; counter < 26; counter++)
	{
		if (node->letters[counter])
			return false;
	}
	return true;
}

bool Is_Fork_Node(Digital_Tree_Node* node)
{
	int counter, NULL_counter = 0;
	for (counter = 0; counter < 26; counter++)
	{
		if (node->letters[counter] != NULL)
		{
			NULL_counter++;
		}
	}
	if (NULL_counter > 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Digital_Tree_Node_Delete(Digital_Tree_Node* node, int current_letter_position, string word)
{
	if (current_letter_position < word.length())
	{
		int letter_position = tolower(word[current_letter_position]) - 97;//int value of the letter
		node = node->letters[letter_position];
		current_letter_position++;
		Digital_Tree_Node_Delete(node, current_letter_position, word);
		delete node;
		node = nullptr;

	}
	return;
}

bool Digital_Tree_Delete(Digital_Tree_Node* root, string word)
{
	Digital_Tree_Node* temp_node = Create_Digital_Tree_Node();
	Digital_Tree_Node* next_node = root;
	int letter_position, previous_word_letter_position = 0;
	for (int counter = 0; counter < word.length(); counter++)
	{
		letter_position = tolower(word[counter]) - 97;//int value of the letter
		if (next_node->letters[letter_position] != NULL)
		{
			if ((Is_Fork_Node(next_node) == true) || (next_node->end_of_word == true))
			{
				previous_word_letter_position = counter;
				temp_node = next_node;
			}
			next_node = next_node->letters[letter_position];
		}
		else
		{
			cout << "The word << " << word << " >> ,that you were trying to delete, wasn't found." << endl;//Key may not be there in trie. Delete operation should not modify trie.
			return false;
		}
	}
	if (next_node->end_of_word == true)
	{
		if (Is_Leaf_Node(next_node) == false)//Key is prefix key of another long key in trie.Unmark the leaf node.
		{
			cout << "The word << " << word << " >> was found and was deleted." << endl;
			next_node->end_of_word = false;
			return true;
		}
		if (Is_Leaf_Node(next_node) == true)
		{
			if (previous_word_letter_position == 0)//Key present as unique key (no part of key contains another key (prefix), nor the key itself is prefix of another key in trie). Delete all the nodes.
			{
				Digital_Tree_Node_Delete(root, 0, word);
				letter_position = tolower(word[0]) - 97;//int value of the letter
				root->letters[letter_position] = NULL;
			}
			else//Key present in trie, having at least one other key as prefix key. Delete nodes from end of key until first leaf node of longest prefix key.
			{
				Digital_Tree_Node_Delete(temp_node, previous_word_letter_position, word);
				letter_position = tolower(word[previous_word_letter_position]) - 97;//int value of the letter
				temp_node->letters[letter_position] = NULL;
			}
			cout << "The word << " << word << " >> was found and was deleted." << endl;
			return true;
		}
	}
}

int main()
{
	vector <string> words_vector;
	int counter, choice = 0;
	string word;
	Digital_Tree_Node *DTRoot = Create_Digital_Tree_Node();
	fstream wordsfile;
	wordsfile.open("C:/Users/jimak/Desktop/Project Domes Dedomenon/Trie Project/words.txt", ios::in | ios::out);
	if (wordsfile.is_open())
	{
		cout << "Opening words file and filling words vector.Pleaze wait." << endl;
		string line;
		while (getline(wordsfile, line))
		{
			words_vector.push_back(line);
		}
		wordsfile.close();
	}
	else
	{
		cout << "<words.txt> file not found." << endl;
		system("pause");
	}
	for (counter = 0; counter < words_vector.size(); counter++)
	{
		Digital_Tree_Insert(DTRoot, words_vector[counter]);
	}
	cout << "The Digital Tree was created successfully." << endl;
	while (choice != 4)
	{
		cout << "For inserting a word in the Digital Tree, choose 1." << endl << "For searching a word in the Digital Tree, choose 2." << endl << "For deleting a word in the Digital Tree, choose 3." << endl << "To exit the search menu, choose 4." << endl;
		do
		{
			cin >> choice;
		} while (choice <= 0 || choice > 5);
		if (choice == 4)
		{
			cout << "Exiting search menu." << endl;
		}
		else
		{
			switch (choice)
			{
			case 1:
			{
				cout << "Enter the word you want to insert." << endl;
				cin >> word;
				Digital_Tree_Insert(DTRoot, word);
				break;
			}
			case 2:
			{
				cout << "Enter the word you want to search for." << endl;
				cin >> word;
				Digital_Tree_Search(DTRoot, word);
				break;
			}
			case 3:
			{
				cout << "Enter the word you want to delete." << endl;
				cin >> word;
				Digital_Tree_Delete(DTRoot, word);
				break;
			}
			}
		}

	}
	return 0;
}