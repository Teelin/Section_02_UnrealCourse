/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interactions. For game logic see the FBullCowGame class 

*/
#pragma once
#include<iostream>
#include<string>
#include"FBullCowGame.h"

//Make the syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void SetDifficulty();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main(){
	do 
	{
		PrintIntro();
		SetDifficulty();
		PlayGame();
	} 
	while (AskToPlayAgain());

	std::cout << std::endl;
	return 0;
}

void PlayGame()
{

	BCGame.Reset();

	//loop for num of guesses
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows<< std::endl;
		std::cout << std::endl;
	}

	std::cout << BCGame.PrintGameSummary() << std::endl;
	return;
}

void PrintIntro() 
{
	std::cout << "                                                 WELCOME TO " << std::endl; 
	std::cout << std::endl;
	std::cout << "    *************************************************************************************************" << std::endl;
	std::cout << "     __________      .__  .__              _____              .___ _________                        " << std::endl;
	std::cout << "     \\______   \\__ __|  | |  | ________   /  _  \\   ____    __| _/ \\_   ___ \\  ______  _  __________" << std::endl;
	std::cout << "      |    |  _/  |  \\  | |  | \\___   /  /  /_\\  \\ /    \\  / __ |  /    \\  \\/ /  _ \\ \\/ \\/ /\\___   /" << std::endl;
	std::cout << "      |    |   \\  |  /  |_|  |__/    /  /    |    \\   |  \\/ /_/ |  \\     \\___(  <_> )     /  /    / " << std::endl;
	std::cout << "      |______  /____/|____/____/_____ \\ \\____|__  /___|  /\\____ |   \\______  /\\____/ \\/\\_/  /_____ \\" << std::endl;
	std::cout << "             \\/                      \\/         \\/     \\/      \\/          \\/                     \\/" << std::endl;
	std::cout << "    *************************************************************************************************" << std::endl;
	std::cout <<  std::endl;
	std::cout << "What Length word do you want to play with? (3-10) ";
	return;
}

void SetDifficulty()
{
	FString Length = "";
	int32 WLength = 0;
	std::getline(std::cin, Length);
	WLength = std::stoi(Length);
	BCGame.SetHiddenWord(WLength);
	std::cout << "Great. Try to guess the " << WLength << " word." << std::endl;
	std::cout << std::endl;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do
	{
		// Get the users guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries()<< " : What is your Guess? ";
		getline(std::cin, Guess);
		
		//Check validity of the guess
		Status = BCGame.IsGuessValid(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetMyWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid Isogram. For Example: planet\n\n";
			break;
		case EGuessStatus::Numbers_Used:
			std::cout << "Please enter a word without any numbers.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in lowercase.\n\n";
			break;
		default:
			break;
		}
		
	} while (Status != EGuessStatus::OK);
	return(Guess);
}


bool AskToPlayAgain()
{
	std::cout << "do you want to play again (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}
