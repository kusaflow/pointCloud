// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "rectCapture.generated.h"

UCLASS()
class LIDAR_API ArectCapture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ArectCapture();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UStaticMeshComponent* plane;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UStaticMeshComponent* arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class USceneCaptureComponent2D* capture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class USceneComponent* scencomp;

/// <summary>
/// ////////////////////////////
/// </summary>
	TArray<FVector> Vertices;
	TArray<FVector> Vertices_normals;
	TArray<FVector> V_Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TArray<FString> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		int totalVert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float ScanIterator = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float TraceLen = 2500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TSubclassOf<class AActor> dots;

	float i = 0, j = 0;
	bool drawOnce = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool start_Capturing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool DataCaptured = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float cap_Size = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		FVector planeDim = FVector(200,0,200);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool drawDebugRay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool overrideIttVal = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CollectData();

	void DrawDots();

	UFUNCTION(BlueprintCallable, Category = "customVar")
		void MakeStrData();
};
