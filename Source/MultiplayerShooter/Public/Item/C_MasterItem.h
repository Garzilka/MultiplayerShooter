// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MasterItem.generated.h"

class AC_MasterCharacter;

UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MasterItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	float Wheight;

	float State; //!Wear

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void TakeIt(AC_MasterCharacter* Who);

protected:
	AC_MasterCharacter* _Owner;

};
