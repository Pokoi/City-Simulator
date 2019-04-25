///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#pragma once

#include "CoreMinimal.h"
#include "MovableActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Walker.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AWalker : public AMovableActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float speed_modificator;
	
	AWalker();
	void HurryUp();
	void Relax();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
