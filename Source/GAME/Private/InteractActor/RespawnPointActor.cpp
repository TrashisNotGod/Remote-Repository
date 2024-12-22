// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/RespawnPointActor.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/TheGameMode.h"

ARespawnPointActor::ARespawnPointActor()
{
	// ����һ��Ĭ�ϵ� SceneComponent ����������Ϊ�����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	// ��������Ϊ�����
	RootComponent = DefaultSceneRoot;


	// ��ʼ����ײ��,�������Details������д
	InitTriggerVolume();

}



void ARespawnPointActor::OnceFound()
{
	if (!bIsFound) {
		bIsFound = true;

		//��������
		Player->ExperienceAddOn();
		FoundEffectEditInBP();
		FVector NewLocation = GetActorLocation() + FVector(0.f, 0.f, 90.f);
		if (GameMode) {
			GameMode->RespawnPoints.Add(NewLocation);
		}
	}
	//��ȫ�ָ�����
	Player->Health = Player->MaxHealth;
}

void ARespawnPointActor::OnceLeave()
{
	//��ȫ�ָ�����
	Player->Health = Player->MaxHealth;
}

void ARespawnPointActor::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATheGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}
