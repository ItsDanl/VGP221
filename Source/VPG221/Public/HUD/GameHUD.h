// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class VPG221_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	// 1. HUD DRaw Method of making UI
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairTexture;

};
