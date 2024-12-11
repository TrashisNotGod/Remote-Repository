// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStatusWidget.h"
#include "Player/PlayerCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


APlayerCharacter* UPlayerStatusWidget::GetPlayerCharacter() const
{
   // 使用 GetPlayerCharacter 获取玩家角色
   return Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

float UPlayerStatusWidget::GetHealthPercentage() const
{
    APlayerCharacter* TargetCharacter = GetPlayerCharacter();
    if (TargetCharacter)
    {
        // 返回生命值百分比
        return TargetCharacter->MaxHealth > 0 ? (TargetCharacter->Health / TargetCharacter->MaxHealth) : 0.0f;
    }
    return 0.0f;
}

float UPlayerStatusWidget::GetEnergyPercentage() const
{
    APlayerCharacter* TargetCharacter = GetPlayerCharacter();
    if (TargetCharacter)
    {
        // 返回体力值百分比
        return TargetCharacter->MaxEnergy > 0 ? (TargetCharacter->Energy / TargetCharacter->MaxEnergy) : 0.0f;
    }
    return 0.0f;
}

float UPlayerStatusWidget::GetXPPercentage() const
{
    APlayerCharacter* TargetCharacter = GetPlayerCharacter();
    if (TargetCharacter)
    {
        // 返回经验条百分比
        return TargetCharacter->Experience % 100 / 100.f;
    }
    return 0.0f;
}


