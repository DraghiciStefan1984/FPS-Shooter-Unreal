// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "FPSGameMode.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	rootBox->SetGenerateOverlapEvents(true);
	rootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnOverlap);
	RootComponent = rootBox;
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(10);
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation();
	newLocation.X += direction.X * speed * DeltaTime;
	newLocation.Y += direction.Y * speed * DeltaTime;
	SetActorLocation(newLocation);
}

void AEnemyController::OnOverlap(UPrimitiveComponent * overlapComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	if (otherActor->GetName().Contains("Projectile"))
	{
		((AFPSGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
		otherActor->Destroy();
		this->Destroy();
	}

	if (otherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		((AFPSGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
