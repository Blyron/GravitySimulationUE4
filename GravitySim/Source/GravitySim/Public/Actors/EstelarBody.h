 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EstelarBody.generated.h"

UCLASS()
class GRAVITYSIM_API AEstelarBody : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstelarBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* Arrow;

	//Density in m^3 / kg
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		float density;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		FVector initialForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		bool affectedByGravitatoryFields;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Managment")
		UMaterialInterface* material;

	UFUNCTION(BlueprintCallable, Category = "Physics")
		void AddGravitationalForce(FVector forceToAdd);

	UFUNCTION(BlueprintCallable, Category = "Physics")
		float GetMass();
private:
	float radius;
	UMaterialInstanceDynamic* material_;
};
