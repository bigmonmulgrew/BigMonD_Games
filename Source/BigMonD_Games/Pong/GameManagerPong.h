// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BigMonD_Games/GameManager.h"
#include "GameManagerPong.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API AGameManagerPong : public AGameManager
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings"); float MaxScore = 10;
	// UPROPERTY to specify the Widget Blueprint class
	UPROPERTY(EditAnywhere, Category="UI")	TSubclassOf<UUserWidget> MatchOverUI;
	
public:
	void IncreaseScore(int player);
	int Score[2] {0,0};				// Use an array because it supports a flexible number of players for later

	// Function to create and show the widget
	void ShowWidget();

	UPROPERTY(EditAnywhere, Category = "UI")TSubclassOf<UUserWidget> ScoreUI;
	UUserWidget* MyWidgetInstance;
	UTextBlock* MyTextBlock;
};
