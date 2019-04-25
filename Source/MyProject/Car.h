///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#pragma once

#include "CoreMinimal.h"
#include "MovableActor.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Car.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ACar : public AMovableActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apply Changes")
		bool check_to_apply_changes = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		class USpotLightComponent* front_right_light;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		class USpotLightComponent* front_left_light;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		class USpotLightComponent* back_right_light;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		class USpotLightComponent* back_left_light;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FVector initial_position_front_right_light = { 150, 50, 20 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FVector initial_position_front_left_light = { 150, -50, 20 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FVector initial_position_back_right_light = { -150, -50, 40 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FVector initial_position_back_left_light = { -150, 50, 40 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FRotator front_lights_rotator = { -10,0,0 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FRotator back_lights_rotator = { -10,-180,0 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FColor front_lights_color = { 224,219,255,1 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		FColor back_lights_color = { 214,85,85,1 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		float light_intensity = 55300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		float lights_inner_cone_angle = 37.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		float lights_outer_cone_angle = 47.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car lights")
		float attenuation_radius =7800;
	
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<USpotLightComponent*> front_lights;
	TArray<USpotLightComponent*> back_lights;

	void PostEditChangeProperty(struct FPropertyChangedEvent& e);
	
};
