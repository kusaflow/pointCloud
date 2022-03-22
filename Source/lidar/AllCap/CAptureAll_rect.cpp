// Fill out your copyright notice in the Description page of Project Settings.


#include "CAptureAll_rect.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "../rectCapture.h"

// Sets default values
ACAptureAll_rect::ACAptureAll_rect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACAptureAll_rect::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ACAptureAll_rect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TA_domes.Num() == 0)
		return;

	if (!fileMade) {
		if (doesEveryThingCaptured()) {
			//UE_LOG(LogTemp, Warning, TEXT("alldone"));
			//for last dome
			TA_domes[capIdx]->MakeStrData();
			makeMainFile();
		}
		else {
			if (capIdx < TA_domes.Num()) {
				//UE_LOG(LogTemp, Warning, TEXT("gg"));
				if (TA_domes[capIdx]->DataCaptured) {
					//UE_LOG(LogTemp, Warning, TEXT("dataCaptured"));
					TA_domes[capIdx]->MakeStrData();
					TA_domes[capIdx]->capture->TextureTarget = nullptr;
					capIdx++;
					CapDataReset = true;
				}
				else {
					if (CapDataReset) {
						//UE_LOG(LogTemp, Warning, TEXT("capdataReset"));
						TA_domes[capIdx]->capture->TextureTarget = RT_tex;
						TA_domes[capIdx]->start_Capturing = true;
						CapDataReset = false;
						if (TA_domes[capIdx]->overrideIttVal)
							TA_domes[capIdx]->ScanIterator = Itr_For_captureDomes;
					}
				}

			}
		}
	}


	UE_LOG(LogTemp, Warning, TEXT("%d of %d"), capIdx, TA_domes.Num());



}



void ACAptureAll_rect::makeMainFile() {
	fileMade = true;
	for (int i = 0; i < TA_domes.Num(); i++) {
		for (int j = 0; j < TA_domes[i]->Data.Num(); j++) {
			Main_Data.Add(TA_domes[i]->Data[j]);
		}
	}
	writeToFile();
}

bool ACAptureAll_rect::doesEveryThingCaptured() {
	bool ret = true;

	for (int i = 0; i < TA_domes.Num(); i++) {
		if (!TA_domes[i]->DataCaptured)
			ret = false;
	}

	return ret;

}

