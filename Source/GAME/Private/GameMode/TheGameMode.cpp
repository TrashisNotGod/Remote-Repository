// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TheGameMode.h"
#include "Player/PlayerCharacter.h"
#include "PlayerState/RecoverPlayerState.h"

void ATheGameMode::RespawnPlayer(APlayerController* PlayerController)
{
    if (!PlayerController) return;

    // ��ȡ��������λ�������������
    FVector SpawnLocation = GetNearestSpawnPoint();

    // ����ӽ��������������½�ɫ
    if (PlayerCharacterBlueprint) // ȷ����ͼ��������
    {
        NewCharacter = GetWorld()->SpawnActor<APlayerCharacter>(PlayerCharacterBlueprint, SpawnLocation, FRotator::ZeroRotator);
        //NewCharacter->bIsDead = false;

        if (NewCharacter)
        {
            //�ָ���ǰ��һЩ��Ϣ
            ARecoverPlayerState* PlayerState = Cast<ARecoverPlayerState>(PlayerController->PlayerState);
            if (PlayerState)
            {
                NewCharacter->Level = PlayerState->Level; 
                NewCharacter->Experience = PlayerState->Experience;
                NewCharacter->Coins = PlayerState->Coins; 
                NewCharacter->MaxHealth = PlayerState->MaxHealth; 
                NewCharacter->MaxEnergy = PlayerState->MaxEnergy; 


            }


            PlayerController->Possess(NewCharacter);  // �ÿ����������½�ɫ
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

    return NearestLocation;  // ���ؾ�����̵�������
}

