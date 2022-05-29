// Fill out your copyright notice in the Description page of Project Settings.
#include "Trigger_compent.h"


UTrigger_compent::UTrigger_compent()
{
PrimaryComponentTick.bCanEverTick = true;

}

void UTrigger_compent::BeginPlay()
{
	Super::BeginPlay();

}




 void UTrigger_compent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
 {
     Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
 

    AActor* Actor = GetAAT();
    if (Actor != nullptr)
    {
        UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
       
        if(comp != nullptr)
        {
            comp->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

        Mover->setShouldMove(true);   
    }
    else
    {
        Mover->setShouldMove(false);  
    }
 }
 

 void UTrigger_compent::setmover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor* UTrigger_compent::GetAAT() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

for (AActor* actor : Actors)
    {   
        bool HAT = actor->ActorHasTag(AAT);
        bool IsGrabbed = actor->ActorHasTag("Grabbed");
        if(HAT && !IsGrabbed)
        {
            return actor;
        }
        
    }
    return nullptr;
}