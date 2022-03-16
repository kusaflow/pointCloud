// Fill out your copyright notice in the Description page of Project Settings.


#include "rectCapture.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ArectCapture::ArectCapture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	scencomp = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	RootComponent = scencomp;

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("plane"));
	plane->SetupAttachment(scencomp);

	capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("sceneCapture"));
	capture->SetupAttachment(scencomp);

	arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("arrow"));
	arrow->SetupAttachment(plane);

	plane->bHiddenInGame = true;
	arrow->bHiddenInGame = true;



}

// Called when the game starts or when spawned
void ArectCapture::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ArectCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (start_Capturing) {
		if (i >= plane->GetRelativeScale3D().X) {
			//+CollectData();

		}
		else {
			if (drawOnce) {
				//DrawDots();
				drawOnce = false;
				DataCaptured = true;
			}
		}
	}

}






void ArectCapture::DrawDots() {
	FActorSpawnParameters spawnPara;
	spawnPara.Owner = this;

	UWorld* world = GetWorld();
	for (int itr = 0; itr < Vertices.Num(); itr++) {
		AActor* cap_balls = world->SpawnActor<AActor>(dots, Vertices[itr], FRotator(0), spawnPara);
		cap_balls->SetActorScale3D(FVector(cap_Size));
	}
}

void ArectCapture::MakeStrData() {
	for (int itr = 0; itr < Vertices.Num(); itr++) {
		FString str = FString::SanitizeFloat(Vertices[itr].X) + " " +
			FString::SanitizeFloat(Vertices[itr].Y) + " " +
			FString::SanitizeFloat(Vertices[itr].Z) + " " +
			FString::SanitizeFloat(V_Colors[itr].X) + " " +
			FString::SanitizeFloat(V_Colors[itr].Y) + " " +
			FString::SanitizeFloat(V_Colors[itr].Z) + " " +
			FString::SanitizeFloat(Vertices_normals[itr].X) + " " +
			FString::SanitizeFloat(Vertices_normals[itr].Y) + " " +
			FString::SanitizeFloat(Vertices_normals[itr].Z) + " ";

		Data.Add(str);


	}

}

