#pragma once
#include<string>

//Make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;

};


enum class EGuessStatus 
{
	Invalid,
	OK,
	Not_Isogram,
	Numbers_Used,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame 
{

public:
	FBullCowGame();
	void Reset();
	int32 GetMaxTries()const;
	void SetHiddenWord(int32);
	int32 GetCurrentTry()const;
	int32 GetMyWordLength() const;
	bool IsGameWon() const;
	EGuessStatus IsGuessValid(FString) const;
	// check number of Bulls and Cows, Increment Try num
	FBullCowCount SubmitValidGuess(FString);
	FString PrintGameSummary();
	



private:
	int32 MyCurrentTry;
	int32 WLength;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsNumber(FString Guess) const;
	
};