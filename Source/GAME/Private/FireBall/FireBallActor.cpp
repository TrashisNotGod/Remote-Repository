// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall/FireBallActor.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerBaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Obstacle/ObstacleActor.h"

// Sets default values
AFireBallActor::AFireBallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    Sphere->SetSphereRadius(75.f);
}

// Called when the game starts or when spawned
void AFireBallActor::BeginPlay()
{
	Super::BeginPlay();

    ///可以写一个“障碍物类”。可以清理障碍物。
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    /// 遍历所有的演员，筛选出是“白名单”的实例
    /// 这里的“白名单”是APlayerBaseCharacter
    /// 子类重写
    for (AActor* Actor : AllActors)
    {
        if (Actor->IsA(APlayerBaseCharacter::StaticClass()))
        {
            AActor* IgnoreActor = Cast<AActor>(Actor);
            if (IgnoreActor)
            {
                IgnoreActors.Add(IgnoreActor);
            }
        }
       
    }

    Sphere->OnComponentHit.AddDynamic(this, &AFireBallActor::OnSphereHit);

}

void AFireBallActor::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    FVector BoomLocation = GetActorLocation();
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("1111"));
    Destroy();

    //IgnoreActors.Empty();

    UGameplayStatics::ApplyRadialDamage(GetWorld(), 25.f, BoomLocation, 250.f, UDamageType::StaticClass(), IgnoreActors,nullptr,nullptr,true);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, BoomLocation);
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, BoomLocation);
}

// Called every frame
void AFireBallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

