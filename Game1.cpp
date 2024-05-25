#include <iostream>

using namespace std;

struct Player {
    string Name;
    int Score = 0;
};

enum enChoice { Stone = 1, Scissors = 2, Paper = 3 };

int GetRandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

int TimesToPlay() {
    cout << "\t\t How Many times you want to play?";
    int Number; cin >> Number;
    return Number;
}

enChoice ShowPlayerOptions() {
    cout << "\n\t\t What will you play? [1] Stone. [2] Scissors. [3] Paper.? ";
    int Choice; cin >> Choice;
    return (enChoice)Choice;
}

string ChoiceName(enChoice Choice) {
    switch (Choice)
    {
    case enChoice::Paper:
        return "Paper";
        break;
    case enChoice::Scissors:
        return "Scissors";
        break;
    case enChoice::Stone:
        return "Stone";
        break;
    default:
        break;
    }

    return "";
}

void ShowActions(Player Winner, enChoice WinnerChoice, enChoice LoserChoice) {
    cout << "\t\t ==========================================================\n\n";

    if (Winner.Name == "Computer") {
        system("color 4f");
        cout << "\n\n\t\t Computer won!!\n";
        cout << "\t\t Your Choice was: " << ChoiceName(LoserChoice) << "\n";
        cout << "\t\t Computer Choice was: " << ChoiceName(WinnerChoice) << "\n\n";
    }
    else if (Winner.Name == "Player1") {
        system("color 2f");
        cout << "\n\n\t\t You won!!\n";
        cout << "\t\t Your Choice was: " << ChoiceName(WinnerChoice) << "\n";
        cout << "\t\t Computer Choice was: " << ChoiceName(LoserChoice) << "\n\n";
    }
    else {
        system("color 6f");
        cout << "\n\n\t\t It's a tie!!\n";
        cout << "\t\t Your Choice was: " << ChoiceName(LoserChoice) << "\n";
        cout << "\t\t Computer Choice was: " << ChoiceName(WinnerChoice) << "\n\n";
    }
    cout << "\t\t ==========================================================\n\n";
}

Player DecideTheWinner(Player& Player1, Player& Player2, enChoice Player1Choice, enChoice Player2Choice) {
    if (Player1Choice == enChoice::Paper) {
        if (Player2Choice == enChoice::Scissors) return Player2;
        if (Player2Choice == enChoice::Stone) return Player1;
    }
    else if (Player1Choice == enChoice::Stone) {
        if (Player2Choice == enChoice::Paper) return Player2;
        if (Player2Choice == enChoice::Scissors) return Player1;
    }
    else {
        if (Player2Choice == enChoice::Paper) return Player1;
        if (Player2Choice == enChoice::Stone) return Player2;
    }

    Player NoOne;
    NoOne.Name = "No One";
    return NoOne;
}

void PlayTheGame(int TimesToPlay, Player& Player1, Player& Player2) {
    for (int i = 0; i < TimesToPlay; ++i) {
        enChoice Player1Choice = ShowPlayerOptions();
        enChoice Player2Choice = (enChoice)GetRandomNumber(1, 3);
        Player Winner = DecideTheWinner(Player1, Player2, Player1Choice, Player2Choice);
        if (Winner.Name == Player1.Name) {
            Player1.Score++;
            ShowActions(Winner, Player1Choice, Player2Choice);
        }
        else if (Winner.Name == Player2.Name) {
            Player2.Score++;
            ShowActions(Winner, Player2Choice, Player1Choice);
        }
        else {
            ShowActions(Winner, Player1Choice, Player2Choice);
        }
    }
}

void GameResults(Player Player1, Player Player2, int Times) {
    Player FinalWinner;
    if (Player1.Score > Player2.Score) FinalWinner.Name = Player1.Name;
    else if (Player2.Score > Player1.Score) FinalWinner.Name = Player2.Name;
    else FinalWinner.Name = "No winner!";
    cout << "\n\t\t --------------------------------------------------------\n";
    cout << "\n\t\t\t\t +++ G A M E  O V E R +++\n";
    cout << "\n\t\t --------------------------------------------------------\n";
    cout << "\n\t\t --------------------- Game Results ---------------------\n\n";
    cout << "\t\t Game Rounds        :" << Times << endl;
    cout << "\t\t Player Won Times   :" << Player1.Score << endl;
    cout << "\t\t Computer Won Times :" << Player2.Score << endl;
    cout << "\t\t Draw Times         :" << Times - (Player1.Score + Player2.Score) << endl;
    cout << "\t\t Final Winner       :" << FinalWinner.Name << endl;
    cout << "\n\t\t --------------------------------------------------------\n";
}

void StartTheGame() {
    Player Player1, Computer;
    Player1.Name = "Player1";
    Computer.Name = "Computer";

    while (true) {
        int Times = TimesToPlay();
        PlayTheGame(Times, Player1, Computer);
        GameResults(Player1, Computer, Times);

        cout << "\n\n\t\t Do you Want to play again, [y]Yes, [n]No? ";
        char Answer; cin >> Answer;
        if (tolower(Answer == 'n')) break;
        Player1.Score = 0, Computer.Score = 0;
    }


}

int main() {
    srand((unsigned)time(NULL));
    StartTheGame();
}