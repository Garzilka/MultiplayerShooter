// Fill out your copyright notice in the Description page of Project Settings.
/*
*
* Maybe need to create a base class from a Pawn instead of a Character? I think this is bad because there will be more data on the network.
* And in the player itself, will need to create a Ñharacter Movement.
* I need to consult someone. Until I continue like this
*
*/

#pragma once

#include "CoreMinimal.h"
#include "Characters/C_MasterCharacter.h"
#include "C_AI.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API AC_AI : public AC_MasterCharacter
{
	GENERATED_BODY()

protected:
	bool IsAgressive; //Temp. I think I need to "inherit" from here, for Citizen and Aggressive, but I need the logic of a citizen who will be able to attack
	
};
