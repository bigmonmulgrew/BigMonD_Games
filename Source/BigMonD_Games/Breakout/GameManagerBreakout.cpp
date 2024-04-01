// Copyright 100705789


#include "BigMonD_Games/Breakout/GameManagerBreakout.h"

void AGameManagerBreakout::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
	GetWorld()->GetTimerManager().SetTimer(LevelReloadTimerHandle, this, &AGameManager::ReloadLevel, DelayBeforeReload, false);
}
