// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"

class UBoxComponent;

UCLASS()
class GAME_API AObstacleActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleActor();

	///�ϰ�����Ա����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
	float Health = 50.f;

	///�ϰ�����ײ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Box)
	TObjectPtr<UBoxComponent> Box;

	///���˺�
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
