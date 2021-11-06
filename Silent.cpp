FVector OriginalLocation;
FRotator OriginalRotation;

// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/ULocalPlayer/GetViewPoint/
void(*GetViewPoint)(ULocalPlayer*, FMinimalViewInfo*, EStereoscopicPass) = nullptr;
void GetViewPointHook(ULocalPlayer* this_LocalPlayer, FMinimalViewInfo* OutViewInfo, EStereoscopicPass StereoPass)
{
	GetViewPoint(this_LocalPlayer, OutViewInfo, StereoPass);

	if (GetAsyncKeyState(hotkey)) {
		OutViewInfo->Location = OriginalLocation;
		OutViewInfo->Rotation = OriginalRotation;
	}
}

// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/APlayerController/GetPlayerViewPoint/
void(*GetPlayerViewPoint)(APlayerController*, FVector*, FRotator*) = nullptr;
void GetPlayerViewPointHook(APlayerController* this_PlayerController, FVector* Location, FRotator* Rotation) {

	GetPlayerViewPoint(this_PlayerController, Location, Rotation);

	OriginalLocation = *Location;
	OriginalRotation = *Rotation;

	if (GetAsyncKeyState(hotkey)) {
		if (BestTarget) {
			auto Player = BestTarget->Instigator;
			if (Player) {
				auto Mesh = Player->Mesh;
				if (Mesh) {
					// Get Target Bone Location
					FRotator AimAt; // = Calculate Rotation
					// Set Rotation
					*Rotation = AimAt;
				}
			}
		}
	}
}
