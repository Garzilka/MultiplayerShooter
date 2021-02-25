// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_MasterCharacter.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AC_MasterCharacter::AC_MasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	/*
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh*/
}

// Called when the game starts or when spawned
void AC_MasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_MasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_MasterCharacter::OnFire()
{

}