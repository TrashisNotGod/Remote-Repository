// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/RespawnPointActor.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/TheGameMode.h"

ARespawnPointActor::ARespawnPointActor()
{
	// 创建一个默认的 SceneComponent 并将其设置为根组件
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	// 将其设置为根组件
	RootComponent = DefaultSceneRoot;


	// 初始化碰撞体,更多的在Details里面重写
	InitTriggerVolume();

}



void ARespawnPointActor::OnceFound()
{
	if (!bIsFound) {
		bIsFound = true;

		//经验增加
		Player->ExperienceAddOn();
		FoundEffectEditInBP();
		FVector NewLocation = GetActorLocation() + FVector(0.f, 0.f, 90.f);
		if (GameMode) {
			GameMode->RespawnPoints.Add(NewLocation);
		}
	}
	//完全恢复生命
	Player->Health = Player->MaxHealth;
}

void ARespawnPointActor::OnceLeave()
{
	//完全恢复生命
	Player->Health = Player->MaxHealth;
}

void ARespawnPointActor::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATheGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}
