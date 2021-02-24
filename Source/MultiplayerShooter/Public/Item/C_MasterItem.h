// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MasterItem.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MasterItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	float Wheight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
