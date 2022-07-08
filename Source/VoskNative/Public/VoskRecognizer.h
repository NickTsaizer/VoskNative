// Copyright 2022, Infima Games. All Rights Reserved.

#pragma once

#include <vosk_api.h>

#include "CoreMinimal.h"
#include "VoskRecognizer.generated.h"

USTRUCT(BlueprintType)
struct FVoskResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString text;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewRecoginzeResult, FString, RecognizeResult);

/**
 * 
 */
UCLASS(BlueprintType)
class VOSKNATIVE_API UVoskRecognizer : public UEngineSubsystem
{
	GENERATED_BODY()

	VoskModel* Model;
	VoskRecognizer* Recognizer;
public:
	UPROPERTY()
	FString LastPartial;
	UPROPERTY()
	FString LastFinal;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadOnly)
	FNewRecoginzeResult OnPartialResult;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadOnly)
	FNewRecoginzeResult OnFinalResult;	
	UFUNCTION(BlueprintCallable, Category="VoskNative")
	void Recognize(TArray<uint8> Buffer, FString& Partial, FString& Final);
	
	UFUNCTION(BlueprintCallable, Category="VoskNative")
	void AcceptWave(TArray<uint8> Buffer);

	UFUNCTION(BlueprintCallable, Category="VoskNative")
	void RequestPartial();

	UFUNCTION(BlueprintCallable, Category="VoskNative")
	void RequestFinal();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void BeginDestroy() override;
};
