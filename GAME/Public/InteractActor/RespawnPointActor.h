// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor/InteractBaseActor.h"
#include "RespawnPointActor.generated.h"

//class APlayerCharacter;
class ATheGameMode;

/**
 * 
 */
UCLASS()
class GAME_API ARespawnPointActor : public AInteractBaseActor
{
	GENERATED_BODY()

public:
	ARespawnPointActor();

	virtual void OnceFound() override;

	virtual void OnceLeave() override;

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	//在篮图中写找到后的特效
	UFUNCTION(BlueprintImplementableEvent)
	void FoundEffectEditInBP();

	ATheGameMode * GameMode;



	
};
