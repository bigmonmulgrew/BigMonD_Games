// Copyright 100705789


#include "BigMonD_Games/Pong/GameManagerPong.h"
#include "BigMonD_Games/GameManager.h"
#include "Blueprint/UserWidget.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

void AGameManagerPong::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreUI)
	{
		MyWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreUI);
		if (MyWidgetInstance)
		{
			MyWidgetInstance->AddToViewport();

			// Find the Text Block by its name in the widget
			MyTextBlock = Cast<UTextBlock>(MyWidgetInstance->GetWidgetFromName(TEXT("ScoreText")));
		}
	}
}

void AGameManagerPong::IncreaseScore(int player)
{
	Score[player]++;
	UE_LOG(LogTemp, Warning, TEXT("Player %i Score: %i"), player+1, Score[player]);

	if (MyTextBlock)		// Incase we cant find the UI, so we don't get an error
	{
		FString FormattedText = FString::Printf(TEXT("%i : %i"), Score[0], Score[1]);
		MyTextBlock->SetText(FText::FromString(FormattedText));
	}
	
	if(Score[player] >= MaxScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %i Wins"), player + 1);

		AActor* Ball = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
		Ball->Destroy();

		ShowWidget(); // Displays the end match UI
		
		// Set a timer to call the ReloadLevel function after the delay
		GetWorld()->GetTimerManager().SetTimer(LevelReloadTimerHandle, this, &AGameManager::ReloadLevel, DelayBeforeReload, false);
	}
}

void AGameManagerPong::ShowWidget()
{
	if (MatchOverUI) // Check if the Widget class is set in the Blueprint
	{
		UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MatchOverUI);
		if (MyWidget)
		{
			// Add the widget to the game's viewport so it becomes visible.
			MyWidget->AddToViewport();
		}
	}
}