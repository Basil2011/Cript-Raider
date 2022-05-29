// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Mover.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Trigger_compent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRIPTRAIDER_API UTrigger_compent : public UBoxComponent
{
	GENERATED_BODY()
	
public:	

UTrigger_compent();

	




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	


	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void setmover(UMover* Mover);


private:
	UPROPERTY(EditAnywhere)
	FName AAT;


	UMover* Mover;

	AActor* GetAAT() const;

};
