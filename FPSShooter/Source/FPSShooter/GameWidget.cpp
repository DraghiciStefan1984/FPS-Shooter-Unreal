// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"

void UGameWidget::Load()
{
	const FName textBlockName = FName(TEXT("ScoreText"));

	if (scoreTextBlock == nullptr)
	{
		scoreTextBlock = (UTextBlock*)(WidgetTree->FindWidget(textBlockName));
	}
}

void UGameWidget::SetScore(int score)
{
	if (scoreTextBlock != nullptr)
	{
		scoreTextBlock->SetText(FText::FromString(FString("Score: ") + FString::FromInt(score)));
	}
}

void UGameWidget::OnGameOver(int score)
{
	if (scoreTextBlock != nullptr)
	{
		scoreTextBlock->SetText(FText::FromString(FString("Game Over! \nScore: ") + FString::FromInt(score) + TEXT("\nPress R to restart!")));
	}
}
