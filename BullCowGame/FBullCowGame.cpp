#pragma once
#include "FBullCowGame.h"
#include<map>

//Make the syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame(){Reset();}

int32 FBullCowGame::GetCurrentTry()const { return MyCurrentTry; }
int32 FBullCowGame::GetMyWordLength()const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon()const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries()const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{ 4,6 },{ 5,10 },{ 6,15 },{ 7,20 },{ 8,25 } ,{ 9,27 } ,{ 10,30 } };
	return(WordLengthToMaxTries[GetMyWordLength()]);
}
void FBullCowGame::SetHiddenWord(int32 WLength)
{
	TMap<int32, FString> WordLengthToWord{ { 3,"ant" },{ 4,"gate" },{ 5,"light" },{ 6,"planet" },{ 7,"factoid" },{ 8,"organism" } ,{ 9,"hairstyle" } ,{ 10,"thumbscrew" } };
	MyHiddenWord = WordLengthToWord[WLength];
	return;
}

void FBullCowGame::Reset()
{
	//Reset the instance of the class
	MyCurrentTry = 1;
	bIsGameWon = false;
	
	return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess)const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsNumber(Guess))
	{
		return EGuessStatus::Numbers_Used;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetMyWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment the try number
	MyCurrentTry++;
	// setup a return variable
	FBullCowCount BullCowCount;
	int32 GuessWordLength = Guess.length();
	
	// loop through all letters in the guess and compare letters against the hidden word
	for (int32 GChar = 0; GChar < GuessWordLength;GChar++) 
	{
		for (int32 MHWChar = 0; MHWChar < GuessWordLength; MHWChar++) 
		{

			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (GChar == MHWChar) 
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	bIsGameWon = (BullCowCount.Bulls == MyHiddenWord.length());

	return BullCowCount;
}

FString FBullCowGame::PrintGameSummary()
{
	if ((MyCurrentTry > GetMaxTries()) && (bIsGameWon == false))
	{
		return( "Bad Luck Try again");
	}
	else
	{
		return("Well Done You Win");
	}
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() < 1) { return true; }
	TMap<char, bool> Letterseen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (Letterseen[Letter])
			return false;
		else
			Letterseen[Letter] = true;
	}
	return true;
}
bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length() < 1) { return true; }
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}
bool FBullCowGame::IsNumber(FString Guess) const
{
	if (Guess.length() < 1) { return true; }
	for (auto Letter : Guess)
	{
		if (isdigit(Letter))
			return false;
	}
	return true;
}

