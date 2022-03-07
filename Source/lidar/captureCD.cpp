// Fill out your copyright notice in the Description page of Project Settings.


#include "captureCD.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"

// Sets default values
AcaptureCD::AcaptureCD()
{
	PrimaryActorTick.bCanEverTick = true;

	scencomp = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	RootComponent = scencomp;

	capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("sceneCapture"));
	capture->SetupAttachment(scencomp);

	totalVert = 0;
	

}

// Called when the game starts or when spawned
void AcaptureCD::BeginPlay()
{
	Super::BeginPlay();
	CollectData();
	DrawDots();
	MakeStrData();
	
}

// Called every frame
void AcaptureCD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AcaptureCD::CollectData() {
	totalVert = 0;
	for (int i = 0; i < 180; i += ScanIterator*2) {
		for (int j = ScanIterator; j < 360; j += ScanIterator) {
			FHitResult hit;
			FVector start = GetActorLocation();
			FRotator rot = FRotator(j, i, 0);
			FVector end = FVector(start.X* TraceLen, start.Y, start.Z);
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

		}
	}

}



void AcaptureCD :: DrawDots() {
	FActorSpawnParameters spawnPara;
	spawnPara.Owner = this;

	UWorld* world = GetWorld();
	for (int i = 0; i < Vertices.Num(); i++) {
		world->SpawnActor<AActor>(dots,Vertices[i], FRotator(0), spawnPara);

		
	}
}

void AcaptureCD::MakeStrData() {
	for (int i = 0; i < Vertices.Num(); i++) {
		FString str = FString::SanitizeFloat(Vertices[i].X) + " " +
			FString::SanitizeFloat(Vertices[i].Y) + " " +
			FString::SanitizeFloat(Vertices[i].Z) + " " +
			FString::SanitizeFloat(V_Colors[i].X) + " " +
			FString::SanitizeFloat(V_Colors[i].Y) + " " +
			FString::SanitizeFloat(V_Colors[i].Z) + " " +
			FString::SanitizeFloat(Vertices_normals[i].X) + " " +
			FString::SanitizeFloat(Vertices_normals[i].Y) + " " +
			FString::SanitizeFloat(Vertices_normals[i].Z) + " ";

		Data.Add(str);


	}

}




