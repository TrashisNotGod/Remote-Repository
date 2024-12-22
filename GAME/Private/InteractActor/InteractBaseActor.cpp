// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/InteractBaseActor.h"
#include "Components/SphereComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AInteractBaseActor::AInteractBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//InitTriggerVolume();
}

void AInteractBaseActor::InitTriggerVolume()
{
	// ��ʼ����ײ��
	TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);
	//��������������TriggerVolume��
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AInteractBaseActor::OnOverlapBegin);
	// �󶨴����������ص��¼�
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AInteractBaseActor::OnComponentEndOverlap);
}

void AInteractBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ����Ƿ������
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) 
	{
		Player = Cast<APlayerCharacter>(OtherActor);
		// ����������
		if (Player) {
			OnceFound();
		}
	}
}

void AInteractBaseActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ȷ��������뿪
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		// ����뿪������ʱ�Ĵ����߼�
		Player = Cast<APlayerCharacter>(OtherActor);
		// ����������
		if (Player) {
			OnceLeave();
		}
	}
}

void AInteractBaseActor::OnceFound()
{
	
}

void AInteractBaseActor::OnceLeave()
{
	
}



