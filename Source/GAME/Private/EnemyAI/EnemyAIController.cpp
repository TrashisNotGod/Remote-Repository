
// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI/EnemyAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"



AEnemyAIController::AEnemyAIController()
{
	
	PrimaryActorTick.bCanEverTick = true;

	/// 设置初始值
	PlayerCharacter = nullptr;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	/// 获取场景中的第一个玩家角色
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	/// 开始追踪玩家
	MoveToPlayer();
}

void AEnemyAIController::MoveToPlayer()
{
	if (PlayerCharacter)
	{
		// 获取玩家的位置
		FVector TargetLocation = PlayerCharacter->GetActorLocation();

		// 使用 AI Controller 自带的 MoveToLocation 函数来移动敌人
		MoveToLocation(TargetLocation);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

