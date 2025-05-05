// Dmytro Chesniuk All Rights Reserved


#include "AnimInstances/Hero/GAS_SlashHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/GAS_SlashHeroAnimInstance.h"

UGAS_SlashHeroAnimInstance* UGAS_SlashHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UGAS_SlashHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
