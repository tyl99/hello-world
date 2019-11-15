/*------------------------------------------------------------------------
*
*This project reads in words from a text file and outputs the most similar
*words based on length and comparing the letters directly at their 
*direct indicies. To accomplish this task we used a helper function along
*with a map to itterate through the file and store all the words as keys and their
*differences as values
* Tyler Gyulveszi  // Project 2  // 11/15/19
----------------------------------------------------------------------------*/



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
 
using std::string; using std::cin; using std::cout;
using std::endl; using std::istream; using std::ifstream;
using std::vector; using std::map;


int Compare(const string a, const string b)   ///writing a helper function to compare the differences of each word in the text file to the word chosen
{
	int dif = 0;
	if (a.length() <= b.length())   ///deciding which is bigger to itterate through the length of the SMALLER word
	{
		dif += (static_cast<int>(b.length() - a.length()));
		for (int i = 0; i < static_cast<int>(a.length()); ++i)
		{
			if (a[i] != b[i])   ///adding to the difference for each letter that doesnt match
			{
				dif += 1;
			}			
		}
	}
	if (b.length() < a.length())
	{
		dif += (static_cast<int>(a.length() - b.length()));
		for (int i = 0; i < static_cast<int>(b.length()); ++i) ///had to static_cast to get rid of errors
		{	
			if (a[i] != b[i])
			{
				dif += 1;				
			}
		}
	}
	return dif;
}


int main()
{
	ifstream myfile("common_passwords.txt");
	cout << "Give me a password:" << endl;
	string password;
	string line;
	map<string, int>differences_map; ///this will be a map that we put each word into with its value as the difference, using a map becau
	vector<string>similar_words;
	int dif_counter = 0;
	int lowest_dif = INT32_MAX;    ///this is the largest possible int in c++, we will change its value later
	cin >> password;
	cout << "You provided a password of " << password << endl;
	if (myfile.is_open()) /// checking if the file is open (had some errors actually getting the information into visual studios)
	{
		while (std::getline(myfile, line))
		{
			dif_counter = Compare(line, password);   ///calling the helper function to give us the word's difference
			differences_map.insert(std::pair<string, int>(line, dif_counter));  ///putting pair into map 
			if (lowest_dif > dif_counter)	///this is how we find the words with the least amount of difference
			{
				lowest_dif = dif_counter;   
			}
		}

		for (std::map<string, int>::iterator it = differences_map.begin(); it != differences_map.end(); ++it)
		{
			if (it->second == lowest_dif)
			{
				similar_words.push_back(it->first);   ///after we complete our map we itterate through looking for the lowest difference values
			}
		}
	}
	cout << "The most similar passwords to " << password<< " are:" << endl;   ///mimir's expected output
	for (string i : similar_words)
	{
		cout << i << ',' << " ";
	}
	cout << "\n";
	cout << "All of which are " << lowest_dif << " character(s) different." << endl;
}


