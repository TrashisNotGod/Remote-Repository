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
#include "TimerManager.h"
//#include "Animation/AnimInstance.h"
//#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

void APlayerCharacter::RegenerateEnergy()
{
	// 如果当前体力小于最大体力，恢复体力
	if (Energy < MaxEnergy)
	{
		Energy = Energy + 1.f <= MaxEnergy ? Energy + 1.f : MaxEnergy;
	}
}

void APlayerCharacter::StartEnergyRegen()
{
	//设置定时器，每隔0.25秒调用一次 `RegenerateEnergy` 函数
	GetWorldTimerManager().SetTimer(EnergyRegenTimerHandle, this, &APlayerCharacter::RegenerateEnergy, 0.25f, true);
}

void APlayerCharacter::StopEnergyRegen()
{
	// 清除定时器
	GetWorldTimerManager().ClearTimer(EnergyRegenTimerHandle);
}



// Sets default values
APlayerCharacter::APlayerCharacter()
{

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//加载蓝图dodge Montage动画资源
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> DodgeMontageAsset(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Animations/Combat/Dodge_F_Montage.Dodge_F_Montage'"));

	//if (DodgeMontageAsset.Succeeded()) {
	//	DodgeMontage = DodgeMontageAsset.Object;
	//}
	//else
	//{
	//	// 处理加载失败的情况
	//	UE_LOG(LogTemp, Warning, TEXT("Failed to load DodgeMontage!"));
	//}

	//在UE角色Details面板中重新设置
	BPWidget = nullptr;
	WidgetInstance = nullptr;

}

//每次经验增加时触发检验（？）
void APlayerCharacter::LevelUp()
{
	Level = Experience / 100 <= 20 ? Experience/40 : 20;
	MaxEnergy = Level * 5.f + 50.f;
	MaxHealth = Level * 5.f + 100.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//开始监测,并设置定时器恢复体力
	StartEnergyRegen();
	// 确保 BPWidget 已经设置
	if (BPWidget)
	{
		// 创建 Widget 实例
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), BPWidget);

		if (WidgetInstance)
		{
			// 将 Widget 添加到屏幕上
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

		bIsDodging = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("IsDodging:%d"), bIsDodging));
	}
}






