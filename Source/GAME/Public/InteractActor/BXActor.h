// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerCharacter.h"
#include "InterActor/InterBaseActor.h"
#include "BXActor.generated.h"

UCLASS()
class GAME_API ABXActor : public AInterBaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABXActor();

	UFUNCTION(BlueprintCallable)
	void Debuff();

	UFUNCTION(BlueprintCallable)
	void Success();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
