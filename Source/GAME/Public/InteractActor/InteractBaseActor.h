// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractBaseActor.generated.h"

class USphereComponent;
class APlayerCharacter;

UCLASS()
class GAME_API AInteractBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractBaseActor();

	bool bIsFound = false;

	//初始化碰撞体
	void InitTriggerVolume();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=TriggerVolume)
	TObjectPtr<USphereComponent> TriggerVolume = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//子类重写发现了它的方法
	UFUNCTION(BlueprintCallable)
	virtual void OnceFound();

	//子类重写远离了它的方法
	UFUNCTION(BlueprintCallable)
	virtual void OnceLeave();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player)
	APlayerCharacter* Player;

	// 默认根组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;


};
