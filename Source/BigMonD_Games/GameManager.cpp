// Copyright 100705789

#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void AGameManager::ReloadLevel()
{	
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void AGameManager::LoadTitle()
{
	UGameplayStatics::OpenLevel(this,"L_Title");
}