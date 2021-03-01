// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/C_MasterItem.h"
#include "Characters/C_MasterCharacter.h"

// Sets default values
AC_MasterItem::AC_MasterItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void AC_MasterItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_MasterItem::TakeIt(AC_MasterCharacter* Who)
{
	if (_Owner == nullptr)
	{
		_Owner = Who;
		this->SetActorEnableCollision(false);
		this->SetActorHiddenInGame(true);
		FAttachmentTransformRules L_AttachTransform(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
		this->AttachToComponent(_Owner->GetMesh(), L_AttachTransform, "");
	}
}