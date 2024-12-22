// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Enemy/PlayerDamageType.h"
#include "Blueprint/UserWidget.h"
#include "EnemyBaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(EnemyDieDelegate, AEnemyBaseCharacter*);


struct FTimerHandle;
class APlayerBaseCharacter;
enum class SpiritPower :uint8;

UCLASS(Blueprintable)
class GAME_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();
	
	//����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerDamage ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttacking ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelUpDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BeginPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle FacePlayerTimehandle;

	//CheckHealth Function: receive damage and check health
	UFUNCTION(BlueprintCallable)
	bool CheckHealth(float Damage);

	//Die FUnction
	
	UFUNCTION(BlueprintCallable)
	void Buff();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Custom")
	void CustomBuff();

	virtual void CustomBuff_Implementation();
	
	//Die FUnction
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnDeath();

	UFUNCTION(BlueprintCallable,Category= "Custom Events")
	void BeginTrace();
	
	UFUNCTION(BlueprintImplementableEvent,Category="Custom Events")
	void BluePrintBeginTrace();

	UFUNCTION(BlueprintImplementableEvent,Category="Custom Events")
	void BluePrintEndTrace();
	
	UFUNCTION(BlueprintCallable,Category= "Custom Events")
	void EndTrace();

	UFUNCTION(BlueprintCallable)
	void HandleAnyDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigateBy,
		AActor* DamageCauser);
	
	//Destroy Enemy
	void DestroySelf();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
