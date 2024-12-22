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

void AFireBallActor::Force()
{
	BlueprintForce();
}

// Called when the game starts or when spawned
void AFireBallActor::BeginPlay()
{
	Super::BeginPlay();

    ///����дһ�����ϰ����ࡱ�����������ϰ��
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    /// �������е���Ա��ɸѡ���ǡ�����������ʵ��
    /// ����ġ�����������APlayerBaseCharacter
    /// ������д


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
	Force();
}

// Called every frame
void AFireBallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

