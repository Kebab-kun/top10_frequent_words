#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "hashtable.h"
#include "linkedList.h"


linkedList<node> dividedText;   // PublicationsDataSet-> all lines to linkedList
linkedList<node> notTakenWords; // stopWords

hashtable<wordCount> storage(200011); // 150k key for %70 load factor size is = 210k + next prime number

void fileParserAndInserter() // file parsing and take words -> insert hashtable
{

    size_t firstCharFound, lastCharFound;

    int  newCount;

    std::string tempWord, tempLine;

    std::ifstream publicationsDataSetFile("PublicationsDataSet.txt"); // read file

    if (!publicationsDataSetFile.is_open())
    {
        std::cerr << "File can not be opened" << std::endl;
    }

    std::ifstream stopWordsFile("stopwords.txt"); // read file

    if (!stopWordsFile.is_open())
    {
        std::cerr << "File can not be opened" << std::endl;
    }

    while (std::getline(publicationsDataSetFile, tempLine)) //  read line after unigramCount
    {
        int notTakenPosition = (int)tempLine.find("\"unigramCount\":");
        tempLine = tempLine.substr((notTakenPosition + 16), tempLine.length() - (notTakenPosition + 18));
        dividedText.insert(tempLine);
    }

    while (std::getline(stopWordsFile, tempLine)) // insert stopwords to linkedList
    {
        notTakenWords.insert(tempLine);
    }

    size_t numeric; // wordCount position in line

    std::string wordCountButString;

    for (int i = 0; i < dividedText.getCount(); i++) // 1500 line
    {
        lastCharFound = 0;

        std::string text = dividedText.moveToNextAndGetData();

        while (lastCharFound <= text.length() - 2) // until find  "}}"
        {

            firstCharFound = text.find('\"', lastCharFound);

            if (firstCharFound + 1 != std::string::npos)
            {
                lastCharFound = text.find("\":", firstCharFound + 1);
            }

            while (!isdigit(text[lastCharFound + 2])) // find the word's last char position
            {
                lastCharFound = text.find("\":", lastCharFound + 1);

            }
            tempWord = text.substr(firstCharFound + 1, lastCharFound - firstCharFound - 1); // extract the word

            numeric = text.find(',', lastCharFound + 2);

            wordCountButString = text.substr(lastCharFound + 2, numeric - (lastCharFound + 2));

            newCount = std::stoi(wordCountButString); // change wordCount string to int
            lastCharFound = text.find('\"', lastCharFound + 1);


            bool flag1 = false; // for first char and last char of word
            bool flag0 = false; // for word to insert hashtable

            // checking Word to insert hashtable

            if (tempWord.length() > 2)
            {

                if (!std::isalpha(tempWord[0] || tempWord[tempWord.length() - 1]))
                {
                    flag1 = true;
                }

                if (flag1)
                {
                    for (int i = 0; !std::isalpha(tempWord[i]); i++)
                    {
                        if (tempWord.length() < 4)
                        {
                            flag0 = true; break;
                        }

                        else {
                            if (tempWord.length() < 4)
                            {
                                flag0 = true; break;
                            }
                            tempWord.erase(0, 1);

                        }
                    }
                    if (flag0) { continue; }
                    for (int i = tempWord.length() - 1; !std::isalpha(tempWord[i]); i--)
                    {
                        if (tempWord.length() < 3)
                        {
                            flag0 = true; break;
                        }
                        else {
                            tempWord.erase(i, i + 1);
                        }
                        if (tempWord.length() < 3)
                        {
                            flag0 = true; break;
                        }
                    }
                    if (flag0)
                    {
                        continue;
                    }
                }

                for (int i = 0; i < (int)tempWord.length() - 1; i++)
                {
                    if (!std::isalpha(tempWord[i]))
                    {
                        flag0 = true; break;
                    }
                }
                if (flag0)
                {
                    continue;
                }
            }
            else { continue; }

            for (int i = 0; i < tempWord.length() ; i++)
            {
                tempWord[i] = std::tolower(tempWord[i]); // all chars to lowercase
            }

            storage.insert(tempWord, newCount); // insert the word and its count

        }
    }

    for (int i = 0; i < notTakenWords.getCount(); i++)
    {
        storage.remove(notTakenWords.at(i)); // remove the stopwords from hashtable
    }
    return;
}



int main()
{
    const clock_t begin = clock();

    fileParserAndInserter();

    storage.winners(); // sort and print top 10

    const  clock_t end = clock();
    std::cout << "Total Elapsed Time " << (end - begin) << " miliseconds" << std::endl;

    return 0;
}