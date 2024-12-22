
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

	/// ���ó�ʼֵ
	PlayerCharacter = nullptr;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	/// ��ȡ�����еĵ�һ����ҽ�ɫ
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	/// ��ʼ׷�����
	MoveToPlayer();
}

void AEnemyAIController::MoveToPlayer()
{
	if (PlayerCharacter)
	{
		// ��ȡ��ҵ�λ��
		FVector TargetLocation = PlayerCharacter->GetActorLocation();

		// ʹ�� AI Controller �Դ��� MoveToLocation �������ƶ�����
		MoveToLocation(TargetLocation);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

