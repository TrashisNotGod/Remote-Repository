// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Widget/PlayerStatusWidget.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FTimerHandle;
//class UAnimMontage;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class GAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// 使用 friend 关键字使 UPlayerStatusWidget 能够访问该类的私有成员
	friend class UPlayerStatusWidget;

	//Player Statue
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy, meta = (AllowPrivateAccess = "true"))
	float MaxEnergy = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy, meta = (AllowPrivateAccess = "true"))
	float Energy = MaxEnergy;

	// 体力恢复定时器句柄
	FTimerHandle EnergyRegenTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health = MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DodgeOrNot, meta = (AllowPrivateAccess = "true"))
	bool bIsDodging = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SkillQOrNot, meta = (AllowPrivateAccess = "true"))
	bool bIsSkillQ = false;

	//经验，每打死一个敌人，或者开了一个宝箱，新发现一个存档点可以增加。
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Experience, meta = (AllowPrivateAccess = "true"))
	int32 Experience = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Level, meta = (AllowPrivateAccess = "true"))
	int32 Level = 1;

	// 恢复体力的函数
	void RegenerateEnergy();

	// 开始恢复体力
	void StartEnergyRegen();

	// 停止恢复体力,比如死亡后就不需要恢复体力了
	void StopEnergyRegen();


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	
	/** Dodge Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DodgeAction;
	
	/** Dodge Montage Animation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DodgeMontage, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DodgeMontage;


public:
	// Sets default values for this character's properties
	APlayerCharacter();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	
	/*Called for Jumping input */
	void ConditionalJump();
	
	/*Called for dodging input */
	void ConditionalDodge();

	/*Play Dodging Animation Montage*/
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDodging();

	/*level up*/
	void LevelUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Widget蓝图的类引用
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> BPWidget;
	//TSubclassOf<T> 是一个模板类型，它表示 T 类型或其派生类的类引用。
	//这样，WidgetClass 变量可以保存任何
	// 继承自 UUserWidget 的蓝图类（如 MyWidget_BP 蓝图）。

	// Widget 实例
	UPROPERTY()
	UUserWidget* WidgetInstance;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
