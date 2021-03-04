// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_MasterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Characters/Components/C_StorageComponent.h"
#include "Characters/Components/C_WeaponComponent.h"
#include "Item/Weapon/C_MasterWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Player/C_Player.h"



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
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
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
	WeaponComponent->OnFire(IsPressed);
}
bool AC_MasterCharacter::CheckCanAim()
{
	return (!isRunning && !Reloading && !ChangingWeapon && WantsToAim && !GetCharacterMovement()->IsFlying());
}
bool AC_MasterCharacter::CheckCanRun()
{
	return (!isAiming && CanRun && !IsCrouched && !(GetCharacterMovement()->IsFlying()) && !Reloading && WantsToRun && !WantsToAim);
}
void AC_MasterCharacter::Run(bool IsPressed)
{
	WantsToRun = IsPressed;	
	bool L_CanRun = CheckCanRun();
	if (L_CanRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed * RunSpeedModifier;
		/*Temp realization -> delegate*/
		if (((AC_Player*)this) != nullptr)
			((AC_Player*)this)->RunEffect(L_CanRun);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
		if (((AC_Player*)this) != nullptr)
			((AC_Player*)this)->RunEffect(L_CanRun);
	}
	Server_Run(IsPressed);
}
void AC_MasterCharacter::Server_Run_Implementation(bool IsPressed)
{
	WantsToRun = IsPressed;
	bool L_CanRun = CheckCanRun();
	if (CheckCanRun())
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed * RunSpeedModifier;
		isRunning = L_CanRun;
		UE_LOG(LogTemp, Warning, TEXT("Server: Run"));
	}
	else
	{
		isRunning = L_CanRun;
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Server: Can't Run"));
	}
}
void AC_MasterCharacter::CheckRun()
{

}
void AC_MasterCharacter::OnAiming(bool IsPressed)
{
	WantsToAim = IsPressed;
	if (WeaponComponent->CurrentWeapon != nullptr)
	{
		CheckRun();
		if (CheckCanAim())
		{
			WeaponComponent->Aiming();
			Server_OnAiming(WantsToAim);
		}
	}
}
void AC_MasterCharacter::Server_OnAiming_Implementation(bool IsPressed)
{
	WantsToAim = IsPressed;
	if (WeaponComponent->CurrentWeapon != nullptr)
	{
		CheckRun();
		if (CheckCanAim())
			WeaponComponent->Aiming();
	}
}