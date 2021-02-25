// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_MasterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Characters/Components/C_StorageComponent.h"
#include "Characters/Components/C_WeaponComponent.h"

// Sets default values
AC_MasterCharacter::AC_MasterCharacter()
{

	//bReplicates = true;
	
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	WeaponComponent = CreateDefaultSubobject<UC_WeaponComponent>(TEXT("WeaponComponent"), this);
	StorageComponent = CreateDefaultSubobject<UC_StorageComponent>(TEXT("StorageComponent"));
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

void AC_MasterCharacter::OnSwitchWeapon(E_WeaponType EType)
{
	WeaponComponent->OnSwitchWeapon(EType);
}