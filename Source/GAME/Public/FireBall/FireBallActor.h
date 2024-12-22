// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBallActor.generated.h"

enum class SpiritPower : uint8;
class USphereComponent;
class EnemyBaseCharacter;

UCLASS()
class GAME_API AFireBallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBallActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spirit Power")
	SpiritPower PlayerSpirit = static_cast<SpiritPower>(0);

	///忽略友伤
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ignore Actors")
	TArray<AActor*> IgnoreActors;

	
	/// 碰撞体积
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> Sphere;

	/// 音效，在蓝图里面重写
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> Sound = nullptr;

	///爆炸粒子效果，在蓝图里面重写
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	TObjectPtr<UParticleSystem> Explosion = nullptr;


	/// 火球的本体在蓝图里面添加

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///火球碰撞
	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
