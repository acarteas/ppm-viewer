#include "FileHelpers.hpp"

vector<string> readFile(ifstream& some_file)
{
	vector<string> result{};

	//make sure file is open
	if (some_file.is_open() == true)
	{
		string line;

		//loop while file is good (not EOF, not error, etc.)
		while (some_file.good() == true)
		{
			getline(some_file, line);

			//add to end of vector
			result.push_back(line);
		}
	}
	return result;
}

vector<string> readFile(const string& file_name)
{
	ifstream input{ file_name };
	vector<string> result = readFile(input);
	input.close();
	return result;
}
