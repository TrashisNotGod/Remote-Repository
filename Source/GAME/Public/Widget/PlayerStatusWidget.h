// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class GAME_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
	APlayerCharacter* GetPlayerCharacter() const;

public:

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable)
	float GetEnergyPercentage() const;

	UFUNCTION(BlueprintCallable)
	float GetXPPercentage() const;


};
