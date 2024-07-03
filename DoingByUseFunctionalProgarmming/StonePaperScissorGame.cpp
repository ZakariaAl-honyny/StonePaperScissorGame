#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameInfo
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;

};

int RandomNumber(int From, int To)
{
	// This Function genrator random number fron 1 to N
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

string WinnerName(enWinner Winner)
{

	string Choises[3] = { "Player1", "Computer", "[No Winner]" };
	return Choises[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{

	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	//if you reach here then player1 is the winner
	return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{

	string arrGameChoises[3] = { "Stone", "Paper", "Scissor" };
	return arrGameChoises[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");// turn screen to green
		break;
	case enWinner::Computer:
		system("color 4F");// turn screen to red
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6F");// turn screen to yellow
		break;
	}
}

void printRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n______________Round [" << RoundInfo.RoundNumber << "] _________\n\n";
	cout << "Player1 choice : " << ChoiceName(RoundInfo.Player1Choice) << "\n";//
	cout << "Computer choice: " << ChoiceName(RoundInfo.ComputerChoice) << "\n";//
	cout << "round Winner   : " << RoundInfo.WinnerName << endl;
	cout << "_________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Playrt1WinTimes, short ComputerWinTimes)
{
	if (Playrt1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Playrt1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameInfo FillGameReslts(short GameRounds, short Playrt1WinTimes, short ComputerWinTimes, short DrawTimes)
{

	stGameInfo GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Playrt1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(GameResults.Player1WinTimes, GameResults.ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour choise [1]:Stone, [2]:Paper, [3]:Scissor ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);
	
	return (enGameChoice)Choice;

}

enGameChoice GetComputerChoice()
{
	return (enGameChoice) RandomNumber(1, 3);
}

stGameInfo PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Playrt1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
	{

		cout << "\nRound [" << GameRounds << "] bigans: \n";
		RoundInfo.RoundNumber = GameRounds;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		//Icrease win/Draw counters
		if (RoundInfo.Winner == enWinner::Player1)
			Playrt1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		printRoundResults(RoundInfo);

	}

	 return FillGameReslts(HowManyRounds, Playrt1WinTimes, ComputerWinTimes, DrawTimes);

}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (short i = 0; i < NumberOfTabs; i++)
	{
		t += "\t";
		
	}
	return t;
}

void showGameOverScreen()
{
	cout << Tabs(2) << "______________________________________________\n\n";
	cout << Tabs(2) << "          +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "______________________________________________\n\n";
}

void ShowFinlGameResults(stGameInfo GameInfo)
{

	cout << Tabs(2) << "___________________ [ Game results ] _______________________\n\n";
	cout << Tabs(2) << "Player1 Winner Times : " << GameInfo.Player1WinTimes << "\n";
	cout << Tabs(2) << "Computer Winner Times: " << GameInfo.ComputerWinTimes << "\n";
	cout << Tabs(2) << "Draw Times           : " << GameInfo.DrawTimes << "\n";
	cout << Tabs(2) << "End Winner           : " << GameInfo.WinnerName << "\n";
	cout << Tabs(2) << "____________________________________________________________\n";

	SetWinnerScreenColor(GameInfo.GameWinner);
}

short ReadHowmanyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << "How many rounds do you want to play from 1 to 10 ? ";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;

}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameInfo GameResults =  PlayGame(ReadHowmanyRounds());

		showGameOverScreen();
		ShowFinlGameResults(GameResults);

		cout << endl << Tabs(2) <<"Do you want to play again ? Y/N ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	StartGame();

	system("pause");
	return 0;
}