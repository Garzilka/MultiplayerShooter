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

		/*UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh;*/
public:
	// Sets default values for this character's properties
	AC_MasterCharacter();
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UC_WeaponComponent* WeaponComponent;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UC_StorageComponent* StorageComponent;

	void Reload(bool isShort);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool isWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool isRunning;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool isAiming;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	bool isReload;
protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire(bool IsPressed);

public:	

	void OnSwitchWeapon(E_WeaponType EType);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:


};
