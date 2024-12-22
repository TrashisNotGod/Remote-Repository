// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBaseCharacter.h"
#include "Logging/LogMacros.h"
#include "Widget/PlayerStatusWidget.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FTimerHandle;
class ATheGameMode;
//enum class SpiritPower : uint8;
//class UAnimMontage;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class GAME_API APlayerCharacter : public APlayerBaseCharacter
{
	GENERATED_BODY()

	// ʹ�� friend �ؼ���ʹ UPlayerStatusWidget �ܹ����ʸ����˽�г�Ա
	//friend class UPlayerStatusWidget;

	

	// �����ָ���ʱ�����
	FTimerHandle EnergyRegenTimerHandle;

	// �ָ������ĺ���
	void RegenerateEnergy();

	// ��ʼ�ָ�����
	void StartEnergyRegen();

	// ֹͣ�ָ�����,����������Ͳ���Ҫ�ָ�������
	void StopEnergyRegen();

	void DestroyAfterDelay();


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
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

	/** pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;

	/** focus Input Action */
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FocusAction;*/

	/** switch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SwitchAction;

	/** SkillQ Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;

	/** SkillQ Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SkillQAction;
	
	/** Dodge Montage Animation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DodgeMontage, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DodgeMontage;




public:

	//Player Statue
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
	float MaxEnergy = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
	float Energy = MaxEnergy;


	//���飬ÿ����һ�����ˣ����߿���һ�����䣬�·���һ���浵��������ӡ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Experience)
	int32 Experience = 0;

	//Ǯ~
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Coins)
	int32 Coins = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Level)
	int32 Level = 1;

	//������� 0Ϊ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponIndex)
	int32 WeaponIndex = 0;

	// Sets default values for this character's properties
	APlayerCharacter();

	//���˺�
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;



	//����
	void Die();

	//����ǰ����
	void Destroyed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DodgeOrNot)
	bool bIsDodging = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DeadOrNot)
	bool bIsDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SkillQOrNot)
	bool bIsSkillQ = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ComboOrNot)
	bool bIsCombo = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AttackOrNot)
	bool bIsAttack = false;

	UFUNCTION(BlueprintCallable)
	void ExperienceAddOn(int32 Add=20);


	/*level up*/
	void LevelUp();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	
	/*Called for Jumping input */
	void ConditionalJump();
	
	/*Called for dodging input */
	void ConditionalDodge();

	/*Called for pausing input */
	void Pause();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowPauseUI();

	/*Play Dodging Animation Montage*/
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDodging();

	

	/*Focus*/
	//void Focus();

	//void EndFocus();

	/*UFUNCTION(BlueprintImplementableEvent)
	void PlayFocus();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEndFocus();*/

	/*Switch Weapon*/
	void SwitchWeapon();

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchToSword();

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchToMagic();

	/*Attack*/
	void Attack();

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySwordAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMagicAttack();

	/*Skill Q*/
	void SkillQ();

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySwordSkillQ();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMagicSkillQ();

	/*Play Hit Reacting Animation Montage*/
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitReacting();

	/*Play Get Damage Sound Montage*/
	UFUNCTION(BlueprintImplementableEvent)
	void PlayOach();

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Widget��ͼ��������
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> BPWidget;
	//TSubclassOf<T> ��һ��ģ�����ͣ�����ʾ T ���ͻ���������������á�
	//������WidgetClass �������Ա����κ�
	// �̳��� UUserWidget ����ͼ�ࣨ�� MyWidget_BP ��ͼ����

	// Widget ʵ��
	UPROPERTY()
	UUserWidget* WidgetInstance;

	//��ʱ����������Game Mode
	ATheGameMode* GameMode = nullptr;

	//��ʱ���������������
	APlayerController* SavedPlayerController = nullptr;

	

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
