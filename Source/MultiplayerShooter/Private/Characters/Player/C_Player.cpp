// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/C_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Characters/Components/C_WeaponComponent.h"

AC_Player::AC_Player() :
	AC_MasterCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

	

}

void AC_Player::BeginPlay()
{
	Super::BeginPlay();
	WeaponComponent->spawnWeapon(WeaponToSpawn);
}

void AC_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AC_Player::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AC_Player::OnStopFire);


	PlayerInputComponent->BindAction("PrimaryWeapon", IE_Pressed, this, &AC_Player::OnPrimaryWeapon);
	PlayerInputComponent->BindAction("SecondaryWeapon", IE_Pressed, this, &AC_Player::OnSecondaryWeapon);
	PlayerInputComponent->BindAction("MeleeWeapon", IE_Pressed, this, &AC_Player::OnMeleeWeapon);
	PlayerInputComponent->BindAction("FastUse_1", IE_Pressed, this, &AC_Player::OnFastUse_1);
	PlayerInputComponent->BindAction("FastUse_2", IE_Pressed, this, &AC_Player::OnFastUse_2);

	

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Player::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AC_Player::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AC_Player::LookUpAtRate);
}

void AC_Player::MoveForward(float Value)
{
	if (Value != 0.0f)
		AddMovementInput(GetActorForwardVector(), Value);
}

void AC_Player::MoveRight(float Value)
{
	if (Value != 0.0f)
		AddMovementInput(GetActorRightVector(), Value);
}

void AC_Player::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AC_Player::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AC_Player::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Fire!"));
	Fire(true); //Fire if pressed
}
void AC_Player::OnStopFire()
{
	Fire(false); //Stop Fire
}
void AC_Player::OnPrimaryWeapon()
{

	UE_LOG(LogTemp, Warning, TEXT("Player Switch OnPrimary!"));
	OnSwitchWeapon(E_WeaponType::E_Prime);
}

void AC_Player::OnSecondaryWeapon()
{

	UE_LOG(LogTemp, Warning, TEXT("Player Switch OnSecond!"));
}

void AC_Player::OnMeleeWeapon()
{

	UE_LOG(LogTemp, Warning, TEXT("Player Switch OnMelee!"));
}

void AC_Player::OnFastUse_1()
{

}

void AC_Player::OnFastUse_2()
{

}