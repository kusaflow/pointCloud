// Fill out your copyright notice in the Description page of Project Settings.


#include "captureCD.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values
AcaptureCD::AcaptureCD()
{
	PrimaryActorTick.bCanEverTick = true;
	capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("sceneCapture"));
	RootComponent = capture;

	totalVert = 0;
	CollectData();

}

// Called when the game starts or when spawned
void AcaptureCD::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AcaptureCD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AcaptureCD::CollectData() {
	totalVert = 0;
	for (int i = 0; i <= 360; i += ScanIterator) {
		for (int j = 0; j <= 360; j += ScanIterator) {
			FHitResult hit;
			FVector start = GetActorLocation();
			FRotator rot = FRotator(j, i, 0);
			FVector end = FVector(start.X* TraceLen, start.Y, start.Z);
			end = rot.RotateVector(end);

			FCollisionQueryParams prams;
			prams.bTraceComplex = true;

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

}






