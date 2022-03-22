// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAptureAll_rect.generated.h"

UCLASS()
class LIDAR_API ACAptureAll_rect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAptureAll_rect();

	int capIdx = 0;
	bool CapDataReset = true;

	bool fileMade = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TArray<class ArectCapture*> TA_domes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TArray<FString> Main_Data;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UTextureRenderTarget2D* RT_tex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float Itr_For_captureDomes = 10;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void makeMainFile();

	bool doesEveryThingCaptured();

	UFUNCTION(BlueprintImplementableEvent, Category = "customF")
		void writeToFile();
};
