// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Widget/EnemyHealthWidget.h"
#include "Player/PlayerBaseCharacter.h"
#include "Player/PlayerCharacter.h"
#include"Elements/Elements.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAI/EnemyAIController.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MaxHealth = 100.f;

    Health = MaxHealth;

	IsAttacking = false;

	IsDead = false;

	Radius = 30.0;

	BaseDamage = 20.0; 
    
	LevelUpDamage = 0.0;
	
	PlayerDamage = 20.0;
}


bool AEnemyBaseCharacter::CheckHealth(float Damage)
{
	Damage += LevelUpDamage;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player Damage: %f"), Damage));
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	if (Health <= 0) return false;
	return true;
}





void AEnemyBaseCharacter::Buff()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn()))
		{
			PlayerCharacter->Experience += 20;
			PlayerCharacter->LevelUp();
			LevelUpDamage +=  20 * PlayerCharacter->Level;
			PlayerCharacter->Coins++;
		}
	}
}

void AEnemyBaseCharacter::CustomBuff_Implementation()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn()))
		{
			PlayerCharacter->Experience += 20;
			PlayerCharacter->LevelUp();
			LevelUpDamage +=  20 * PlayerCharacter->Level;
			PlayerCharacter->Coins++;
		}
	}
}

//Die Event
void AEnemyBaseCharacter::OnDeath_Implementation()
{
	if (IsDead) return;

	if (GetMesh())
	{
		GetMesh()->SetSimulatePhysics(true);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->Deactivate();
	}

	IsDead = true;

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
	}

	GetWorldTimerManager().SetTimer(FacePlayerTimehandle,this,&AEnemyBaseCharacter::DestroySelf,1.0f,false);
	
	CustomBuff_Implementation();
}

void AEnemyBaseCharacter::BeginTrace()
{
	BluePrintBeginTrace();
}


void AEnemyBaseCharacter::EndTrace()
{
	BluePrintEndTrace();
}

void AEnemyBaseCharacter::HandleAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigateBy, AActor* DamageCauser)
{
	if (DamagedActor == this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ActualDamage: %f"), Damage));
	}
}

void AEnemyBaseCharacter::DestroySelf()
{
	Destroy();
}

// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AEnemyBaseCharacter::HandleAnyDamage);
	
}




// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = DamageAmount;

	const UDamageType* DamageType = Cast<const UDamageType>(DamageEvent.DamageTypeClass.GetDefaultObject());
	if (!DamageType)
	{
		DamageType = UDamageType::StaticClass()->GetDefaultObject<UDamageType>();
	}
	
	if (DamageType->IsA(UPlayerDamageType::StaticClass()))
	{
		ActualDamage *= 1.5f;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ActualDamage: %f"), ActualDamage));
	}

	PlayerDamage = ActualDamage;
	
	OnTakeAnyDamage.Broadcast(this,ActualDamage,DamageEvent.DamageTypeClass.GetDefaultObject(),EventInstigator,DamageCauser);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


// Called to bind functionality to input
//void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

