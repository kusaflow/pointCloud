// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CaptureAllColorMngr.generated.h"

UCLASS()
class LIDAR_API ACaptureAllColorMngr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaptureAllColorMngr();

	int capIdx = 0;
	bool CapDataReset = true;

	bool fileMade = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
	TArray<class ACaptureColor*> TA_domes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
	TArray<FString> Main_Data;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
	class UTextureRenderTarget2D* RT_tex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float Itr_For_captureDomes = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		int ScanAngleLmt = 360;


protected:
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void makeMainFile();

	bool doesEveryThingCaptured();

	UFUNCTION(BlueprintImplementableEvent, Category = "customF")
	void writeToFile();
};
