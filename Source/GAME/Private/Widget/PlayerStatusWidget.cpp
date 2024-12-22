// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStatusWidget.h"
#include "Player/PlayerCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


APlayerCharacter* UPlayerStatusWidget::GetPlayerCharacter() const
{
   // ʹ�� GetPlayerCharacter ��ȡ��ҽ�ɫ
   return Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

float UPlayerStatusWidget::GetHealthPercentage() const
{
    APlayerCharacter* TargetCharacter = GetPlayerCharacter();
    if (TargetCharacter)
    {
        // ��������ֵ�ٷֱ�
        return TargetCharacter->Health > 0 && TargetCharacter->MaxHealth ? (TargetCharacter->Health / TargetCharacter->MaxHealth) : 0.0f;
    }
    return 0.0f;
}

float UPlayerStatusWidget::GetEnergyPercentage() const
{
    APlayerCharacter* TargetCharacter = GetPlayerCharacter();
    if (TargetCharacter)
    {
        // ��������ֵ�ٷֱ�
        return TargetCharacter->Energy > 0 && TargetCharacter->MaxEnergy > 0 ? (TargetCharacter->Energy / TargetCharacter->MaxEnergy) : 0.0f;
    }
    return 0.0f;
}

float UPlayerStatusWidget::GetXPPercentage() const
{
    APlayerCharacter* TargetCharacter = GetPlayerCharacter();
    if (TargetCharacter)
    {
        // ���ؾ������ٷֱ�
        return static_cast<float>(TargetCharacter->Experience % 100 / 100.f);
    }
    return 0.0f;
}


