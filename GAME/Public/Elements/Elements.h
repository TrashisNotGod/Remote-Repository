// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class SpiritPower : uint8
{
	Fire UMETA(DisplayName = "Fire"),
	Water UMETA(DisplayName = "Water"),
	Wind UMETA(DisplayName = "Wind"),
	Earth UMETA(DisplayName = "Earth"),
};

///水克制火，火克制风，风克制地，地克制水