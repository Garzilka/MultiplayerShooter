// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_MasterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Characters/Components/C_StorageComponent.h"
#include "Characters/Components/C_WeaponComponent.h"
#include "Item/Weapon/C_MasterWeapon.h"

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
void AC_MasterCharacter::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

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
void AC_MasterCharacter::Reload(bool isShort)
{

}
void AC_MasterCharacter::Fire(bool IsPressed)
{
	if (WeaponComponent->CurrentWeapon != nullptr)
		WeaponComponent->CurrentWeapon->OnFire(IsPressed);
}