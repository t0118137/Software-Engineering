#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

// Member of class
class Map
{
public:
	int s = sequence, sequence = 0;
	string data;
	using KeyType = int;
	using ItemType = string;
	void insert(map<KeyType, ItemType>& value, ItemType& key); // insert with value and key
	void find_EastToWest(map<KeyType, ItemType>& value, map<KeyType, pair<ItemType, ItemType>>& symbol); // find all symbols from east to west
}great_map;

// Calling function insert(value, key)
void Map::insert(map<KeyType, ItemType>& value, ItemType& key)
{
	value[s] = key;
	s++;
}

// Calling function find(value, symbol)
void Map::find_EastToWest(map<KeyType, ItemType>& value, map<KeyType, pair<ItemType, ItemType>>& symbol)
{
	// Set "element1" as the pair of symbol
	for (auto element1 : symbol)
	{
		sequence = 0;
		// Set "element2" as another pair of symbol
		for (auto element2 : symbol)
		{
			sequence++;
			if (element1.second.first == element2.second.second)
			{
				break;
			}
			// Apply insertion when the sequence matches the size of the pair of symbol
			else if (sequence == symbol.size())
			{
				insert(value, element1.second.first);
				insert(value, element1.second.second);
				data = element1.second.second;
				break;
			}
		}
	}

	// Find all symbols of bricks
	// Stops when all correct sequence found
	sequence = 0;
	while (sequence != symbol.size() - 1)
	{
		for (auto element1 : symbol)
		{
			if (data == element1.second.first)
			{
				insert(value, element1.second.second);
				data = element1.second.second;
				sequence++;
				break;
			}
		}
	}
}

// Execute as argument 0
int main(int argc, char const* argv[])
{
	// Commend-line-arguments
	cout << argc << " argument(s) found." << endl;
	for (int i = 0; i != argc; i++)
	{
		cout << "(" << i << ") " << argv[i] << endl << endl;
	}

	using KeyType = int;
	using ItemType = string;
	map<KeyType, pair<ItemType, ItemType>> symbol;
	map<KeyType, ItemType> value;

	int sequence = 0;
	unsigned int row_num = 0;
	string row, first_element, second_element;

	// Output file (argument 1)
	ifstream dataFile(argv[1]);

	// Functions of opening file using commend-line
	dataFile.open("");
	if (!dataFile)
	{
		cout << "WARNING: Unable to open text file, please try again." << endl;
		exit(EXIT_FAILURE);
	}
	else if (dataFile.is_open())
	{
		// Read every element from the text file
		while (getline(dataFile, row))
		{
			stringstream ss(row);
			getline(ss, first_element, ',');
			getline(ss, second_element);
			symbol[sequence] = make_pair(first_element, second_element);
			sequence++;
		}
	}
	
	// Calling the find_EastToWest function
	great_map.find_EastToWest(value, symbol);

	// To observe the container's element by rows
	// "value" is the iterator
	for (const auto& element : value)
	{
		row_num++;
		cout << setw(8) << row_num << ":	" << element.second << endl;
	}

	// Flush and close file
	dataFile.close();

	cout << endl;
	system("pause");
	return 0;
}