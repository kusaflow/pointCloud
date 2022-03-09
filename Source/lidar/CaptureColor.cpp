// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureColor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"

// Sets default values
ACaptureColor::ACaptureColor()
{
	PrimaryActorTick.bCanEverTick = true;

	scencomp = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	RootComponent = scencomp;

	capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("sceneCapture"));
	capture->SetupAttachment(scencomp);

	totalVert = 0;

	i = 0;
	j = ScanIterator;

}

// Called when the game starts or when spawned
void ACaptureColor::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ACaptureColor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (start_Capturing) {
		if (i < 180) {
			CollectData();

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

void ACaptureColor::CollectData() {

	FHitResult hit;
	FVector start = GetActorLocation();
	FRotator rot = FRotator(j, i, 0);
	FVector end = FVector(start.X * TraceLen, start.Y, start.Z);
	end = rot.RotateVector(end);

	capture->SetRelativeRotation(rot);

	FCollisionQueryParams prams;
	prams.bTraceComplex = true;

	FVector end2 = GetActorForwardVector() * TraceLen;
	end2 += start;
	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 5, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Visibility, prams)) {
		totalVert++;
		Vertices.Add(hit.ImpactPoint);
		Vertices_normals.Add(hit.ImpactNormal);


		//colors
		UTextureRenderTarget2D* RenderTarget = capture->TextureTarget;
		int sx = capture->TextureTarget->SizeX;
		int sy = capture->TextureTarget->SizeY;

		sx /= 2;
		sy /= 2;

		FColor color = UKismetRenderingLibrary::ReadRenderTargetPixel(GetWorld(), RenderTarget, sx, sy);
		FVector col = FVector(color.R, color.G, color.B);
		V_Colors.Add(col);

	}

	if (j < 360) {
		j += ScanIterator;
	}
	else {
		j = ScanIterator;
		i += ScanIterator;
	}

	UE_LOG(LogTemp, Warning, TEXT("%f-----%f"), i, j);

}



void ACaptureColor::DrawDots() {
	FActorSpawnParameters spawnPara;
	spawnPara.Owner = this;

	UWorld* world = GetWorld();
	for (int itr = 0; itr < Vertices.Num(); itr++) {
		AActor* cap_balls = world->SpawnActor<AActor>(dots, Vertices[itr], FRotator(0), spawnPara);
		cap_balls->SetActorScale3D(FVector(cap_Size));
	}
}

void ACaptureColor::MakeStrData() {
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






