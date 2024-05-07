// Copyright 100705789


#include "BigMonD_Games/Mario/Mushroom.h"

#include "Mario.h"

void AMushroom::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->GrowMario();
		Destroy();
	}
}
