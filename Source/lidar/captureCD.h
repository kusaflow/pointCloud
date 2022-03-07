// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "captureCD.generated.h"

UCLASS()
class LIDAR_API AcaptureCD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcaptureCD();

	TArray<FVector> Vertices;
	TArray<FVector> Vertices_normals;
	TArray<FVector> V_Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
	TArray<FString> Data;

	int totalVert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float ScanIterator = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float TraceLen = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class USceneCaptureComponent2D* capture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class USceneComponent* scencomp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TSubclassOf<class AActor> dots;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CollectData();

	void DrawDots();
	void MakeStrData();


};
