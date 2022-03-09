// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "k_GI.generated.h"

/**
 * 
 */
UCLASS()
class LIDAR_API Uk_GI : public UGameInstance
{
	GENERATED_BODY()
	
public:
	int camIdx = 0;

};
