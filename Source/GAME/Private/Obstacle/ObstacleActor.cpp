// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/ObstacleActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AObstacleActor::AObstacleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetBoxExtent(FVector(10.f, 10.f, 10.f));
}

float AObstacleActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("222"));
	if (Health > 0.f)
	{
		// ����ʵ���ܵ����˺�
		Health -= DamageAmount;

		if (Health <= 0.f)
		{
			// ��ɫ�����߼�
			Health = 0.f;

			// ��������
			Destroy();
		}
	}
	return DamageAmount;
}

// Called when the game starts or when spawned
void AObstacleActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AObstacleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

