// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALL_MotionCapture.generated.h"

UCLASS()
class LIDAR_API AALL_MotionCapture : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AALL_MotionCapture();

	int capIdx = 0;
	bool CapDataReset = true;

	bool fileMade = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TArray<class AMotionScan*> TA_domes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TArray<FString> Main_Data;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UTextureRenderTarget2D* RT_tex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float Itr_For_captureDomes = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		int Num_Of_LineTrace_At_A_Time = 20;

protected:

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void makeMainFile();

	bool doesEveryThingCaptured();

	UFUNCTION(BlueprintImplementableEvent, Category = "customF")
		void writeToFile();
};
