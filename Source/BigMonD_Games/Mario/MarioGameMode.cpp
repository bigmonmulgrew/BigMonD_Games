// Copyright 100705789


#include "BigMonD_Games/Mario/MarioGameMode.h"

void AMarioGameMode::ResetScore()
{
	PlayerScore = 0;
}

void AMarioGameMode::AddScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}

int AMarioGameMode::GetScore()
{
	return PlayerScore;
}
