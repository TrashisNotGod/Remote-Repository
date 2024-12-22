
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

	/// �� BeginPlay �е���
	virtual void BeginPlay() override;

	/// ����Ŀ�꣨Player��
	void MoveToPlayer();

protected:

	// Ŀ���ɫ
	ACharacter* PlayerCharacter;

public:
	virtual void Tick(float DeltaTime) override;

	// �����������Ƶ����ж����߼�
	
};
