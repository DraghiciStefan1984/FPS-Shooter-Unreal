// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "EnemyController.h"
#include "GameWidget.h"
#include "FPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSSHOOTER_API AFPSGameMode : public AGameMode
{
	GENERATED_BODY()

	float min_interval = 0.5f;
	float max_interval = 2.0f;
	float time_to_min_interval = 30.0f;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	void IncrementScore();
	void OnGameOver();
	void OnRestart();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> enemy_BP;

	float enemyTimer;
	float gameTimer;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass);

protected:
	int score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> startWidgetClass;

	UPROPERTY()
	UUserWidget* currentWidget;
};
