// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/C_Player.h"

void AC_Player::MoveForward(float Value)
{
	bool Aiming = false;

	if(!Aiming)
		if (Value != 0.0f)
		{
			// Движение вперед
			AddMovementInput(GetActorForwardVector(), Value);
		}
}

void AC_Player::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Движение вправо
		AddMovementInput(GetActorRightVector(), Value);
	}
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