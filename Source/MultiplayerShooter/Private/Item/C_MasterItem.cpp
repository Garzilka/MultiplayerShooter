// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/C_MasterItem.h"

// Sets default values
AC_MasterItem::AC_MasterItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

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

