FVector OriginalLocation;
FRotator OriginalRotation;

void(*GetViewPoint)(ULocalPlayer*, FMinimalViewInfo*, EStereoscopicPass) = nullptr;
void GetViewPointHook(ULocalPlayer* this_LocalPlayer, FMinimalViewInfo* OutViewInfo, EStereoscopicPass StereoPass)
{
	GetViewPoint(this_LocalPlayer, OutViewInfo, StereoPass);

	if (GetAsyncKeyState(hotkey)) {
		OutViewInfo->Location = OriginalLocation;
		OutViewInfo->Rotation = OriginalRotation;
	}
}

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
					// Calculate Rotation
					// Set Rotation
					FRotator AimAt; // = TargetRotation
					*Rotation = AimAt;
				}
			}
		}
	}
}
