// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/C_MasterCharacter.h"
#include "C_Player.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;


UCLASS()
class MULTIPLAYERSHOOTER_API AC_Player : public AC_MasterCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
public:
	AC_Player();
	void RunEffect(bool IsRun);

	float DeffaultFieldOfView = 90.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AC_MasterWeapon> WeaponToSpawn;

protected:
	virtual void BeginPlay() override;
//===================== | Base Move | ==============================

	void MoveForward(float Val);

	void MoveRight(float Val);

	void LookUpAtRate(float Rate);

	void TurnAtRate(float Rate);
	
	void StartRun();

	void StopRun();

//===========================================================================
	void OnFire();

	void OnStopFire();

	void OnPrimaryWeapon();

	void OnSecondaryWeapon();

	void OnMeleeWeapon();

	void OnFastUse_1();

	void OnFastUse_2();

	void StartAiming();

	void StopAiming();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
};
