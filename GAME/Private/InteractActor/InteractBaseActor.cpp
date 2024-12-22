// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/InteractBaseActor.h"
#include "Components/SphereComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AInteractBaseActor::AInteractBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//InitTriggerVolume();
}

void AInteractBaseActor::InitTriggerVolume()
{
	// 初始化碰撞体
	TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);
	//将触发函数绑定在TriggerVolume上
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AInteractBaseActor::OnOverlapBegin);
	// 绑定触发器结束重叠事件
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AInteractBaseActor::OnComponentEndOverlap);
}

void AInteractBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 检查是否是玩家
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) 
	{
		Player = Cast<APlayerCharacter>(OtherActor);
		// 触发被发现
		if (Player) {
			OnceFound();
		}
	}
}

void AInteractBaseActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 确保是玩家离开
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		// 玩家离开触发器时的处理逻辑
		Player = Cast<APlayerCharacter>(OtherActor);
		// 触发被发现
		if (Player) {
			OnceLeave();
		}
	}
}

void AInteractBaseActor::OnceFound()
{
	
}

void AInteractBaseActor::OnceLeave()
{
	
}



