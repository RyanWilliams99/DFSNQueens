/*
 * File:   main.cpp
 * Author: j4-smith
 *N-Queens example in C
 * First Created on 25 April 2014, 18:42
 * Modified in light of student progress 
 
 * Rewritten Oct 2015 to use more generic solution structures 
 * and functions with NQueens-specific names that call the functions that modify the
 */
 #pragma warning(disable:4996)
 
 #ifdef _WIN32 
 #include <Windows.h> 
 #define sleep(x) Sleep(1000*x)
 #else 
 #include <unistd.h> 
 #endif 
 #include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"

candidateSolution workingCandidate; //this one will hold the soltion we are currently considering
candidateList currentListOfCandidates; // this list will store all the soltion weve created but not examined yet
candidateList listOfExaminedCandidates; // this is where we will store all the ones we're done with

//************************ don't edit anything above this line***********************//

int main(int argc, const char * argv[])
{

    int numberOfCompleteSolutionsFound = 0; //simple flag to let us know whether we have stopped
    int numberOfSolutionsExamined = 0; //simple counter
    int indexOfSolutionWeAreLookingAt; //index in list of current solution being examined
	int newLength = 0;
	int valueToAdd; // used when we extend the working candidate
	int queensPlaced = 0;
	int allQueensPlacedAndSafe = 0;


    CleanListsOfSolutionsToStart();
	CleanWorkingCandidate();

    valueToAdd = 0;
    if(argc==2)
    {
        valueToAdd = atoi(argv[1]);
		if (valueToAdd >= N || valueToAdd < 0)
		{
			PrintThisMessageAndExit("Invalid Input");
		}
    }
	
	AddQueenToNextRowInColumn(valueToAdd);
	AddWorkingCandidateToCurrentList();
	queensPlaced = 1;
    numberOfSolutionsExamined = 1;
	PrintWorkingCandidate(); sleep(1);

	while (queensPlaced <= 8 )
	{


		CalculateNumberOfVulnerableQueensForWorkingCandidate();
		if (workingCandidate.score < 1)  //SOLUTION IS FEASABLE
		{
			AddQueenToNextRowInColumn(0);
			AddWorkingCandidateToCurrentList();
			PrintWorkingCandidate(); sleep(1);
			
			for (int i = 1; i < 8; i++)
			{
				ChangeWorkingCandidateByReplaceValueinPlaceParam1_WithValueParam2(queensPlaced, i);
				PrintWorkingCandidate(); sleep(1);
				AddWorkingCandidateToCurrentList();	
				
			}
			queensPlaced++;
		}
		else                             //SOLUTION INFEASABLE
		{
			queensPlaced--;

			while (workingCandidate.score >= 1)
			{
				int temp = 0;
				printf("invalid");
				AddWorkingCandidateToExaminedList();
				numberOfSolutionsExamined++;
				CopySolutionFromCurrentListIntoWorkingCandidate(currentListOfCandidates.indexOfLastEntryAdded-temp);
				PrintWorkingCandidate(); sleep(1);
				temp++;
				CalculateNumberOfVulnerableQueensForWorkingCandidate();
			}		
		
		}
		
		if (queensPlaced == 8 && workingCandidate.score == 0)
		{
			printf("FINAL SOLUTION FOR STARTING POSITION %d\n\n\n\n\n", atoi(argv[1]));
			PrintWorkingCandidate();
			sleep(100);
		}
	}

	if (allQueensPlacedAndSafe == 1)
	{
		PrintFinalSolutionAndExit();
	}
}

