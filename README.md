# cli-quiz

## A simple command-line quiz written in C.

An attempt to produce a simple multiple-choice quiz program in C, reading questions from a file. Its small memory footprint makes it ideal for devices such as the Raspberry Pi. The question format is:

    total:[total number of questions]
    question1:answerchoice1
    question2:answerchoice2
    question...:answerchoice...[newline]

The first line contains a 'total' statement followed by the total number of questions. Each question is then set out on the following lines, and must contain the availabe choices. The 'answerchoice' for each question is a number corresponding to the correct answer. The last line must be a newline, if this is not the case the program will ask you if you want to add it.

*This program is* **experimental** *- there may be bugs*.

Also the code needs a bit of tidying up.
