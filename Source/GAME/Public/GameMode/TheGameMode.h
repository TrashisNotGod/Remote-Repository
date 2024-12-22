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

	// 在GameMode中记录重生点
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = RespawnPoints)
	TArray<FVector> RespawnPoints;

	//添加新的重生点位置
	UFUNCTION(BlueprintCallable)
	void AddNewSpawnPoint(FVector NewLocation);

	//死亡地点
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DeathLocationInDebug)
	FVector DeathLocation;

	//死亡后计算最近的重生点
	UFUNCTION(BlueprintCallable)
	FVector GetNearestSpawnPoint();

	//角色重生
	UFUNCTION(BlueprintCallable)
	void RespawnPlayer(APlayerController* PlayerController);
	
	//需要在Details里面重写
	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<APlayerCharacter> PlayerCharacterBlueprint = nullptr;

	UPROPERTY()
	APlayerCharacter * NewCharacter = nullptr;

};
