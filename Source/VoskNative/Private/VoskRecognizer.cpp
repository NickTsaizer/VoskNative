// Copyright 2022, Infima Games. All Rights Reserved.


#include "VoskRecognizer.h"

#include "JsonObjectConverter.h"


void UVoskRecognizer::Recognize(TArray<uint8> Buffer, FString& Partial, FString& Final)
{
	vosk_recognizer_accept_waveform(Recognizer, reinterpret_cast<char*>(Buffer.GetData()), Buffer.Num());
	
	Partial = vosk_recognizer_partial_result(Recognizer);
	Final = vosk_recognizer_final_result(Recognizer);
}

void UVoskRecognizer::AcceptWave(TArray<uint8> Buffer)
{
	Async(EAsyncExecution::TaskGraph, [this, Buffer]()
	{
		// ReSharper disable once CppCStyleCast
		vosk_recognizer_accept_waveform(Recognizer, (char*)Buffer.GetData(), Buffer.Num());
		RequestFinal();
	})
	;
}

void UVoskRecognizer::RequestPartial()
{
	const FString PartialJson = vosk_recognizer_partial_result(Recognizer);
	FVoskResult Result;
	FJsonObjectConverter::JsonObjectStringToUStruct(PartialJson, &Result);
	LastPartial = Result.text;
	OnPartialResult.Broadcast(LastPartial);
}

void UVoskRecognizer::RequestFinal()
{
	const FString FinalJson = vosk_recognizer_final_result(Recognizer);
	FVoskResult Result;
	FJsonObjectConverter::JsonObjectStringToUStruct(FinalJson, &Result);
	LastFinal = Result.text;
	OnFinalResult.Broadcast(LastFinal);
}

void UVoskRecognizer::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const char* ModelPath = TCHAR_TO_ANSI(*FPaths::Combine(FPaths::ProjectContentDir(), "VoskModel"));
	Model = vosk_model_new(ModelPath);
	Recognizer = vosk_recognizer_new(Model, 16000);
}

void UVoskRecognizer::BeginDestroy()
{
	Super::BeginDestroy();
	vosk_model_free(Model);
	vosk_recognizer_free(Recognizer);
}
