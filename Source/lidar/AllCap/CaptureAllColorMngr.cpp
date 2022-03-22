// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureAllColorMngr.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "../CaptureColor.h"

// Sets default values
ACaptureAllColorMngr::ACaptureAllColorMngr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called every frame
void ACaptureAllColorMngr::Tick(float DeltaTime)
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
						TA_domes[capIdx]->ScanIterator = Itr_For_captureDomes;
						TA_domes[capIdx]->ScanAngleLmt = ScanAngleLmt;
					}
				}

			}
		}
	}


	UE_LOG(LogTemp, Warning, TEXT("%d of %d"), capIdx, TA_domes.Num());
	


}



void ACaptureAllColorMngr :: makeMainFile() {
	fileMade = true;
	for (int i = 0; i < TA_domes.Num(); i++) {
		for (int j = 0; j < TA_domes[i]->Data.Num(); j++) {
			Main_Data.Add(TA_domes[i]->Data[j]);
		}
	}
	writeToFile();
}

bool ACaptureAllColorMngr::doesEveryThingCaptured() {
	bool ret = true;

	for (int i = 0; i < TA_domes.Num(); i++) {
		if (!TA_domes[i]->DataCaptured)
			ret = false;
	}

	return ret;

}