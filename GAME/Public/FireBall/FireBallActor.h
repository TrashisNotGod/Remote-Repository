// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
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

	///��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ignore Actors")
	TArray<AActor*> IgnoreActors;

	
	/// ��ײ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> Sphere;

	/// ��Ч������ͼ������д
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> Sound = nullptr;

	///��ը����Ч��������ͼ������д
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	TObjectPtr<UParticleSystem> Explosion = nullptr;

	UFUNCTION(BlueprintCallable,Category= "Custom Events")
	void Force();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Custom Event")
	void BlueprintForce();
	
	/// ����ı�������ͼ�������

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///������ײ
	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
