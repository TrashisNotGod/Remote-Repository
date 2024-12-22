// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RecoverPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ARecoverPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Experience;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Coins;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	float MaxEnergy;
	
};
