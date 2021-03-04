// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "C_WeaponComponent.generated.h"

enum E_WeaponType;
class AC_MasterCharacter;
class AC_MasterWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERSHOOTER_API UC_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_WeaponComponent();
	UC_WeaponComponent(AC_MasterCharacter* OwnerRef);

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, replicated)
		AC_MasterWeapon* CurrentWeapon = nullptr;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, replicated)
		AC_MasterWeapon* PrimaryWeapon;
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, replicated)
		AC_MasterWeapon* SecondaryWeapon;
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, replicated)
		AC_MasterWeapon* MeleeWeapon;

	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnSwitchWeapon(E_WeaponType EType);

	void OnFire(bool IsPressed);

	UFUNCTION(Server, Reliable)
		void Server_Fire(bool IsPressed);
	void Server_Fire_Implementation(bool IsPressed);



	UFUNCTION(Server, Reliable)
		void Server_spawnWeapon(TSubclassOf<AC_MasterWeapon> WeaponToSpawn);
	void Server_spawnWeapon_Implementation(TSubclassOf<AC_MasterWeapon> WeaponToSpawn);


	UFUNCTION(Server, Reliable)
		void Server_OnSwitchWeapon(E_WeaponType EType);
	void Server_OnSwitchWeapon_Implementation(E_WeaponType EType);

	void Aiming(); 

private:
	void DetachCurrentWeapon();

	void AttachCurrentWeapon(AC_MasterWeapon* NewWeapon);
	UPROPERTY(replicated)
	AC_MasterCharacter* _Owner;
};
