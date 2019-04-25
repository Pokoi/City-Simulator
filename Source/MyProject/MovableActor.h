///
///Created by Jesus pokoidev Villar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableActor.generated.h"


UCLASS()
class MYPROJECT_API AMovableActor : public AActor
{
	GENERATED_BODY()


public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* box_collider;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* front_proximity_sensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float current_speed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float speed_random_offset = 100.0f;


	//Trigger Enter
	UFUNCTION()
		void FrontSensorTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//Trigger Exit
	UFUNCTION()
		void FrontSensorTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	   
private:

	bool       movable;
	bool       sensor_activated;
	FVector    movement_direction;
	int        sensor_contacts;
	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdateMovementDirectionVector();
	
	float initial_speed;

public:

	// Sets default values for this actor's properties
	AMovableActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ChangeDirection();
	UFUNCTION()
		void ChangePosition(FVector new_position);
	UFUNCTION()
		void Stop();
	UFUNCTION()
		void Move();

	
};
