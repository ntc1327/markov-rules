Author: Noah Cribelar
Date Completed: 4/22/19

PROGRAM SUMMARY

This program reads in commands from a pre-formatted text file to construct a rule set to alter strings with, and is able to use this rule set to alter strings.

INVOKING THE PROGRAM

After unzipping the zip file, the program can be run using make commands.

Use "make" to compile the program from the command line, and after running make, use "make run" to execute the program.

The program will ask the user to choose which file they want to use, if what the user types in does not match either of the file names, then an error message will be given asking the user to provide an appropriate file.

Use enter to progress through the program should it seem execution stops, the program will also prompt the user to press enter after they input the text file.

Use "make clean" to remove any object file after one is finished with executing the program. If one wants to execute after running make clean, simply enter "make" again and use "make run" again to execute.


PROGRAM INPUT

The only input necessary is the selection of the text file and pressing enter to advance after that point. Valid text file names are "myMarkov.txt" and "finkelMarkov.txt". It is also described in the program how to input the files.


PROGRAM OUTPUT

Output will be instructions showing the user how to enter in files, prompts to continue, and outputs describing the rule set and the execution of that rule set on the string. A sample of outputs when run on both files can be found in output1.txt and output2.txt, which are included in the zip file.


ADDITIONAL NOTES

To help implement the IBF Search, I refered to this article from GeeksForGeeks: https://www.geeksforgeeks.org/optimized-naive-algorithm-for-pattern-searching/

The substring method I implemented was suggested by classmate Jackson Danna to me in class when we were brainstorming a way to shorten the string if a right pattern did not have the same number of characters as the left pattern it was replacing. He suggested just adding the front and back ends of the original string to the right pattern instead of having to shorten the original. I implemented this by just using the substring function to go through the given indices.
