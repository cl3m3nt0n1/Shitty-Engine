#pragma once

#ifndef PONG_SCOREMANAGER_H
#define PONG_SCOREMANAGER_H


class ScoreManager
{
public:
    int getPlayer1Score() const {
        return player1_Score;
    }

    int getPlayer2Score() const {
        return player2_Score;
    }

    const char* getPlayer1ScoreAsString()
    {
        std::string scoreString = std::to_string(player1_Score);
        return strdup(scoreString.c_str());
    }

    const char* getPlayer2ScoreAsString()
    {
        std::string scoreString = std::to_string(player2_Score);
        return strdup(scoreString.c_str());
    }

    void incrementPlayer1Score()
    {
        player1_Score++;
    }

    void incrementPlayer2Score()
    {
        player2_Score++;
    }

    bool checkForWinner()
    {
        if(player1_Score >= MAX_SCORE)
            return true;
        if(player2_Score >= MAX_SCORE)
            return true;
        return false;
    }

private:
    const int MAX_SCORE = 10;
    int player1_Score = 0;
    int player2_Score = 0;
};

#endif //PONG_SCOREMANAGER_H
