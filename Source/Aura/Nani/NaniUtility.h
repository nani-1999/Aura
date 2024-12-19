// Copyright Na9i Studio

#pragma once

#define NANI_LOG(Verbosity, Str, ...) \
	switch (GetWorld()->GetNetMode()) { \
		case ENetMode::NM_Client: \
			UE_LOG(LogTemp, Verbosity, TEXT("Client: %d | " ## Str), GPlayInEditorID, ##__VA_ARGS__); \
			break; \
		case ENetMode::NM_DedicatedServer: \
		case ENetMode::NM_ListenServer: \
			UE_LOG(LogTemp, Verbosity, TEXT("Server | " ## Str), ##__VA_ARGS__); \
			break; \
		case ENetMode::NM_Standalone: \
			UE_LOG(LogTemp, Verbosity, TEXT("Standalone | " ## Str), ##__VA_ARGS__); \
			break; \
		default : \
			UE_LOG(LogTemp, Verbosity, TEXT("MAX? | " ## Str), ##__VA_ARGS__); \
	} \

#define ECC_NonPhysical ECollisionChannel::ECC_GameTraceChannel1