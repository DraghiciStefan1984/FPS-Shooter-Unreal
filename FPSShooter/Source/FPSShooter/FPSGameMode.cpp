// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "EnemyController.h"

void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(startWidgetClass);
	((UGameWidget*)currentWidget)->Load();
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Restart", IE_Pressed, this, &AFPSGameMode::OnRestart).bExecuteWhenPaused = true;
}

void AFPSGameMode::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	gameTimer += deltaSeconds;
	enemyTimer -= deltaSeconds;
	UWorld* world = GetWorld();

	if (enemyTimer <= 0.0f)
	{
		float difficulty_percentage = FMath::Min(gameTimer / time_to_min_interval, 1.0f);
		enemyTimer = max_interval - (max_interval - min_interval) * difficulty_percentage;

		if (world)
		{
			float distance = 800.0f;
			float randomAngle = FMath::RandRange(0.0f, 360.0f);
			FVector playerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
			FVector enemyLocation = playerLocation;
			enemyLocation.X += FMath::Cos(randomAngle*3.14f / 180.0f) * distance;
			enemyLocation.Y += FMath::Sin(randomAngle*3.14f / 180.0f) * distance;
			enemyLocation.Z = 250.0f;
			AEnemyController* enemy = world->SpawnActor<AEnemyController>(enemy_BP, enemyLocation, FRotator::ZeroRotator);
			enemy->direction = (playerLocation - enemyLocation).GetSafeNormal();
		}
	}
}

void AFPSGameMode::IncrementScore()
{
	score += 100;
	((UGameWidget*)currentWidget)->SetScore(score);
}

void AFPSGameMode::OnGameOver()
{
	((UGameWidget*)currentWidget)->OnGameOver(score);
}

void AFPSGameMode::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AFPSGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass)
{
	if (currentWidget != nullptr)
	{
		currentWidget->RemoveFromViewport();
		currentWidget = nullptr;
	}

	if (newWidgetClass != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), newWidgetClass);
		
		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}
}
