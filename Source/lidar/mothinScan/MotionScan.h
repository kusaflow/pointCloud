// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionScan.generated.h"

UCLASS()
class LIDAR_API AMotionScan : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMotionScan();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UStaticMeshComponent* arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class USceneCaptureComponent2D* capture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class USceneComponent* scencomp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		class UStaticMeshComponent* RayCastPlaceHolder;


	/// <summary>
	/// ////////////////////////////
	/// </summary>
	TArray<FVector> Vertices;
	TArray<FVector> Vertices_normals;
	TArray<FVector> V_Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
	TArray<FVector> CapturePosThatNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		TArray<FString> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float ScanIterator = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float TraceLen = 100;

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
		FVector planeDim = FVector(200, 0, 200);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool drawDebugRay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float drawDebugRay_Timer = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool overrideIttVal = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float planeTranverseAxisPos = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float Itr_planeTranverseAxisPos = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		float Lmt_planeTranverseAxisPos = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool SinglePlaneCaptured = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		int Num_Of_LineTrace_At_A_Time = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "customVar")
		bool ColorCaptured = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CollectData();

	void DrawDots();
	void project_DrawDots();

	UFUNCTION(BlueprintCallable, Category = "customVar")
		void MakeStrData();

	void GetPlanePosToCapture(); 
	void CaptureColor();


};
