// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "InteractActor/BXActor.h"

// Sets default values
ABXActor::ABXActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABXActor::Debuff()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn()))
		{
			if (PlayerCharacter->Coins > 0)
			{
				PlayerCharacter->Coins--;
				PlayerCharacter->Experience += 20;
				PlayerCharacter->LevelUp();
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Coins: %d"), PlayerCharacter->Coins));
			}
			
		}
	}
}

// Called when the game starts or when spawned
void ABXActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABXActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

