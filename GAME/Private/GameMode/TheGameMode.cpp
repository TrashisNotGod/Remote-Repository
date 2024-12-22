// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TheGameMode.h"
#include "Player/PlayerCharacter.h"
#include "PlayerState/RecoverPlayerState.h"

void ATheGameMode::RespawnPlayer(APlayerController* PlayerController)
{
    if (!PlayerController) return;

    // 获取距离死亡位置最近的重生点
    FVector SpawnLocation = GetNearestSpawnPoint();

    // 在最接近的重生点生成新角色
    if (PlayerCharacterBlueprint) // 确保蓝图类已设置
    {
        NewCharacter = GetWorld()->SpawnActor<APlayerCharacter>(PlayerCharacterBlueprint, SpawnLocation, FRotator::ZeroRotator);
        //NewCharacter->bIsDead = false;

        if (NewCharacter)
        {
            //恢复死前的一些信息
            ARecoverPlayerState* PlayerState = Cast<ARecoverPlayerState>(PlayerController->PlayerState);
            if (PlayerState)
            {
                NewCharacter->Level = PlayerState->Level; 
                NewCharacter->Experience = PlayerState->Experience;
                NewCharacter->Coins = PlayerState->Coins; 
                NewCharacter->MaxHealth = PlayerState->MaxHealth; 
                NewCharacter->MaxEnergy = PlayerState->MaxEnergy; 


            }


            PlayerController->Possess(NewCharacter);  // 让控制器控制新角色
        }
    }
}

void ATheGameMode::AddNewSpawnPoint(FVector NewLocation)
{
	if (!RespawnPoints.Contains(NewLocation)) {
		RespawnPoints.Add(NewLocation);
	}
}

FVector ATheGameMode::GetNearestSpawnPoint()
{
    FVector NearestLocation = FVector::ZeroVector;
    float MinDistance = FLT_MAX;

    for (const FVector& SpawnPoint : RespawnPoints)
    {
        float Distance = FVector::Dist(DeathLocation, SpawnPoint);
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            NearestLocation = SpawnPoint;
        }
    }

    return NearestLocation;  // 返回距离最短的重生点
}

