// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item/Weapon/C_MasterWeapon.h"
#include "C_MasterCharacter.generated.h"

#define DefaultSpawn FVector(0.f, 0.f, -1000.f), FRotator(0.f, 0.f, 0.f) //Использовать только для спавна объектов которым владеет Игрок
class UC_StorageComponent;
class UC_WeaponComponent;

UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterCharacter : public ACharacter
{


	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_MasterCharacter();
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UC_WeaponComponent* WeaponComponent;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UC_StorageComponent* StorageComponent;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool isWeapon = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo", replicated)
	bool isRunning = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo", replicated)
	bool IsCrouched = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool CanRun = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool WantsToRun = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool isAiming = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool WantsToAim = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo", replicated)
	bool ChangingWeapon = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo", replicated)
	bool Reloading = false;
	


protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire(bool IsPressed);
	

	void Run(bool IsPressed);
	UFUNCTION(Server, Reliable)
		void Server_Run(bool IsPressed);
	void Server_Run_Implementation(bool IsPressed);

	void OnAiming(bool IsPressed);
	UFUNCTION(Server, Reliable)
		void Server_OnAiming(bool IsPressed);
	void Server_OnAiming_Implementation(bool IsPressed);

	

public:	
	

	void Reload(bool isShort);

	void OnSwitchWeapon(E_WeaponType EType);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float RunSpeedModifier = 1.5f;

	float DefaultMovementSpeed = 270;

	void CheckRun();

	bool CheckCanAim();

	bool CheckCanRun();
};
