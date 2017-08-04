//============================================================================
// Name        : CryptKicker_C++.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// Modified !!!
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#define MAX_DIC_SIZE			1000
#define MAX_DIC_WORD_SIZE		16

ifstream problemFile("data.in");
ofstream solFile("data.out");

vector<string> makeDictionary(ifstream& inFile)
{
	vector<string> result;

	// 1. read a count of dictionary size
	int nDic;
	problemFile >> nDic;
	nDic = nDic > MAX_DIC_SIZE ? MAX_DIC_SIZE : nDic;

	// 2. read and save a word to dictionary
	for (int n = 0; n < nDic; n++)
	{
		string word;
		problemFile >> word;

		if (word.size() <= MAX_DIC_WORD_SIZE)
			result.push_back(word);
	}

	return result;
}

vector<vector<string> > readProblems(ifstream& inFile)
{
	vector<vector<string> > result;

	string aLine;
	while (std::getline(inFile, aLine))
	{
		if (aLine.size() != 0)
		{
			vector<string> aProblem;

			stringstream ss(aLine);
			string aWord;
			while (ss >> aWord)
			{
				aProblem.push_back(aWord);
			}

			result.push_back(aProblem);
		}
	}
	return result;
}

#define NOT_MATCHED		0xff

int main()
{
	cout << "Programming Challenges - hotfix2 << endl;

	vector<string> dictionary = makeDictionary(problemFile);
	vector<vector<string> > problems = readProblems(problemFile);

	for (vector<vector<string> >::iterator pInt = problems.begin();pInt != problems.end(); pInt++)
	{
		vector<string> problem = *pInt;

		// make a mapping table to use decryting
		map<char, char> transMap;	// 원본문자에 대한 암호문자 관계 정의
		for (int i = 0; i < dictionary.size(); i++)
		{
			for (int j = 0; j < problem.size(); j++)
			{
				if (dictionary[i].size() == problem[j].size())
				{
					// cout << i << ":" << j << " - " << dictionary[i] << " , " << problem[j] << endl;

					map<char, char> prevMap = transMap;
					for (int n = 0; n < dictionary[i].size(); n++)
					{
						// 정의되어 있지 않으면, 신규 정의
						if (transMap.count(dictionary[i][n]) == 0)
						{
							transMap[dictionary[i][n]] = (char) (problem[j][n]);
						}
						else
						{
							// 정의되어 있고, 충돌되면, 다음
							if (transMap[dictionary[i][n]] != (char) (problem[j][n]))
							{
								transMap = prevMap;
								break;
							}
							// 정의되어 있고, 일치되면, 다음
							else
							{
								// continue;
							}
						}
					}

				}
			}
		}

		bool isOK = true;
		map<char, char> revTransMap;
		for (int a = 0; a < 26; a++)
		{
			if (transMap.count('a' + a) != 0)
			{
				if (revTransMap.count(transMap['a' + a]) == 0)
				{
					revTransMap[transMap['a' + a]] = 'a' + a;
					// cout << transMap['a' + a] << " : " << revTransMap[transMap['a' + a]] << endl;
				}
				else
				{
					isOK = false;
					break;
				}
			}
		}

		// convert encryted text to decryted text using mapping table
		string result;
		for (int i = 0; i < problem.size(); i++)
		{
			for (int j = 0; j < problem[i].size(); j++)
			{
				if (isOK)
				{
					// cout << problem1[i][j] << " : " << revTransMap[problem1[i][j]] << endl;
					if (revTransMap.count(problem[i][j]) != 0)
					{
						result.push_back(revTransMap[problem[i][j]]);
					}
				}
				else
				{
					result.push_back('*');
				}
			}
			result.push_back(' ');
		}

		cout << result << endl;
		solFile << result << endl;
	}

	return 0;
}
