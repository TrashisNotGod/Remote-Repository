// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TheGameMode.generated.h"


class APlayerController;
class APlayerCharacter;
struct FTimerHandle;

/**
 * 
 */
UCLASS()
class GAME_API ATheGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	// ��GameMode�м�¼������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = RespawnPoints)
	TArray<FVector> RespawnPoints;

	//����µ�������λ��
	UFUNCTION(BlueprintCallable)
	void AddNewSpawnPoint(FVector NewLocation);

	//�����ص�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DeathLocationInDebug)
	FVector DeathLocation;

	//��������������������
	UFUNCTION(BlueprintCallable)
	FVector GetNearestSpawnPoint();

	//��ɫ����
	UFUNCTION(BlueprintCallable)
	void RespawnPlayer(APlayerController* PlayerController);
	
	//��Ҫ��Details������д
	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<APlayerCharacter> PlayerCharacterBlueprint = nullptr;

	UPROPERTY()
	APlayerCharacter * NewCharacter = nullptr;

};
