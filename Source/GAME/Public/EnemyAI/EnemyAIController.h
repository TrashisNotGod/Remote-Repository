
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	/// 在 BeginPlay 中调用
	virtual void BeginPlay() override;

	/// 跟随目标（Player）
	void MoveToPlayer();

protected:

	// 目标角色
	ACharacter* PlayerCharacter;

public:
	virtual void Tick(float DeltaTime) override;

	// 可以用来控制敌人行动的逻辑
	
};
