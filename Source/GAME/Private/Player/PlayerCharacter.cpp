// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputActionValue.h>
#include "GameMode/TheGameMode.h"
#include "TimerManager.h"
#include "PlayerState/RecoverPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Elements/Elements.h"
#include "Engine/DamageEvents.h"
//#include "Animation/AnimInstance.h"
//#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

void APlayerCharacter::RegenerateEnergy()
{
	// �����ǰ����С������������ָ�����
	if (Energy < MaxEnergy)
	{
		Energy = Energy + 1.f <= MaxEnergy ? Energy + 1.f : MaxEnergy;
	}
}

void APlayerCharacter::StartEnergyRegen()
{
	//���ö�ʱ����ÿ��0.25�����һ�� `RegenerateEnergy` ����
	GetWorldTimerManager().SetTimer(EnergyRegenTimerHandle, this, &APlayerCharacter::RegenerateEnergy, 0.25f, true);
}

void APlayerCharacter::StopEnergyRegen()
{
	// �����ʱ��
	GetWorldTimerManager().ClearTimer(EnergyRegenTimerHandle);
}





// Sets default values
APlayerCharacter::APlayerCharacter()
{
	MaxHealth = 100.f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	
	PlayerSpirit = SpiritPower::Earth;
	
	//��UE��ɫDetails�������������
	BPWidget = nullptr;
	WidgetInstance = nullptr;

}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	if (Health > 0.f && !bIsDodging)
	{
		// ����ʵ���ܵ����˺�
		Health -= DamageAmount;
		PlayOach();
		//UE_LOG(LogTemp, Log, TEXT("Character took %f damage. Remaining Health: %f"), ActualDamage, CurrentHealth);

		if (Health <= 0.f)
		{
			// ��ɫ�����߼�
			Health = 0.f;
	
			// ��������
			Die();
		}
		PlayHitReacting();
	}

	return DamageAmount;
}



void APlayerCharacter::Die()
{
	//�����ظ�����
	if (bIsDead) {
		return;
	}
	bIsDead = true;
	
	if (WidgetInstance) {
		WidgetInstance->RemoveFromParent();
		WidgetInstance = nullptr;
	}
	// ���ý�ɫ�ƶ�
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	// ���ý�ɫ����ײ���������������������ͻ��
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// ���� Skeletal Mesh ������ģ�⣨������Ч����
	USkeletalMeshComponent* MeshComponent = GetMesh();

	// ȷ����ɫ MeshComponent�Ѿ�����
	if (MeshComponent)
	{
		MeshComponent->SetCollisionProfileName(TEXT("Ragdoll"));  // ʹ�� Ragdoll ��ײ����
		MeshComponent->SetSimulatePhysics(true);                 // ��������ģ��
	}

	//��ȡ�����ص�
	
	if (GameMode)
	{
		GameMode->DeathLocation=GetActorLocation();
	}

	//�������һЩ����
	ARecoverPlayerState* ThePlayerState = Cast<ARecoverPlayerState>(GetPlayerState());
	if (ThePlayerState)
	{
		ThePlayerState->Level = Level;
		ThePlayerState->Experience = Experience;
		ThePlayerState->Coins = Coins;
		ThePlayerState->MaxHealth = MaxHealth;
		ThePlayerState->MaxEnergy = MaxEnergy;
	}
	
	// ���浱ǰ������
	SavedPlayerController = Cast<APlayerController>(GetController());
	
	// ��������ٽ�ɫ
	FTimerHandle DestroyTimerHandle;
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &APlayerCharacter::DestroyAfterDelay, 2.0f, false);

}

void APlayerCharacter::DestroyAfterDelay()
{
	Destroy();
}

void APlayerCharacter::Destroyed()
{
	Super::Destroyed();

	// ���� GameMode �� RespawnPlayer ��ִ�������߼�

	
	if (GameMode)
	{
		if (SavedPlayerController)
		{
			GameMode->RespawnPlayer(SavedPlayerController);
		}
	}
	

}

void APlayerCharacter::ExperienceAddOn(int32 Add)
{
	Experience += Add;
	int OldLevel = Level;
	LevelUp();
	//����һ��
	if (Level>OldLevel) {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Cheers!LevelUP!!!\nAnd You Now Are Lv. %d"),Level));
	}
}


void APlayerCharacter::SkillQ()
{
	if (bIsSkillQ || Energy<=20.f) {
		return;
	}
	if (Level > 5)
	{
		Energy -= 20.f;
		bIsSkillQ = true;
		if (WeaponIndex == 0 ) {
			PlaySwordSkillQ();
		}
		if (WeaponIndex == 1) {
			PlayMagicSkillQ();
		}
	}
}

//ÿ�ξ�������ʱ�������飨����
void APlayerCharacter::LevelUp()
{
	Level = 1 + Experience / 100 <= 20 ? 1 + Experience/100 : 20;
	MaxEnergy = Level * 5.f + 50.f;
	if (Experience / 100  > 0)
	{
		Health = MaxHealth;
		Energy = MaxEnergy;
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//�������ʼ��
	GameMode = Cast<ATheGameMode>(GetWorld()->GetAuthGameMode());
	
	if (GameMode)
	{
		FVector InitLocation = GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f, %f, %f"), InitLocation.X, InitLocation.Y, InitLocation.Z));
		GameMode->RespawnPoints.Add(InitLocation);
		Health = MaxHealth;
		Energy = MaxEnergy;
	}

	

	//��ʼ���,�����ö�ʱ���ָ�����
	StartEnergyRegen();
	// ȷ�� BPWidget �Ѿ�����
	if (BPWidget)
	{
		// ���� Widget ʵ��
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), BPWidget);

		if (WidgetInstance)
		{
			// �� Widget ��ӵ���Ļ��
			WidgetInstance->AddToViewport();
		}
	}
}



//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::ConditionalJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		// Dodging
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &APlayerCharacter::ConditionalDodge);

		// Pausing
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::Pause);

		// Focusing
		//EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Started, this, &APlayerCharacter::Focus);
		//EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndFocus);


		// Switch weapon
		EnhancedInputComponent->BindAction(SwitchAction, ETriggerEvent::Started, this, &APlayerCharacter::SwitchWeapon);

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);

		// SkillQ
		EnhancedInputComponent->BindAction(SkillQAction, ETriggerEvent::Started, this, &APlayerCharacter::SkillQ);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::ConditionalJump()
{
	if (Energy >= 10.f) {
		Energy -= 10.f;
		Jump();
	}
}

void APlayerCharacter::ConditionalDodge()
{
	if (!bIsDodging && !bIsSkillQ && Energy >= 10.f) {
		Energy -= 10.f;
		bIsDodging = true;
		
		PlayDodging();
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("IsDodging:%d"), bIsDodging));
	}
}

void APlayerCharacter::Pause()
{
	// ��ͣ��Ϸ
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	//����ͼ����д
	ShowPauseUI();
}

void APlayerCharacter::Attack()
{
	if (bIsAttack || bIsSkillQ || bIsDodging) {
		if (WeaponIndex == 0) {
			bIsCombo = true;
		}
		return;
	}
	if (WeaponIndex == 1) {
		if (Energy <= 10.f) {
			return;
		}
		Energy -= 10.f;
	}
	bIsAttack = true;
	if (WeaponIndex == 0) {
		PlaySwordAttack();
	}
	else if (WeaponIndex == 1) {
		FRotator Rotation = FollowCamera->GetComponentRotation();
		Rotation.Roll = 0.0f;
		Rotation.Pitch = 0.0f;
		Rotation.Yaw += 90.f;
		SetActorRotation(Rotation);
		PlayMagicAttack();
	}
}

//void APlayerCharacter::Focus()
//{
//	PlayFocus();
//}
//
//void APlayerCharacter::EndFocus()
//{
//	PlayEndFocus();
//}

void APlayerCharacter::SwitchWeapon()
{
	if (bIsAttack || bIsSkillQ || bIsCombo) {
		return;
	}
	WeaponIndex += 1;
	WeaponIndex %= 2;
	switch (WeaponIndex) {
		case 0:
			SwitchToSword();
			PlayerSpirit = static_cast<SpiritPower>(3);
			break;
		case 1:
			SwitchToMagic();
			PlayerSpirit = static_cast<SpiritPower>(0);
			break;
	}
}






