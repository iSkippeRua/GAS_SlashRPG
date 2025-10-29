#pragma once

#include "NativeGameplayTags.h"

namespace GameItems
{
	namespace Equipment
	{
		namespace Weapons
        	{
        		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Axe)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sword)
        	}
        	
        	namespace Cloaks
        	{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(RedCloak)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(GreenCloak)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(YellowCloak)
        	}
        
        	namespace Masks
        	{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(SteelMask)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(GreenMask)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(YellowMask)
        	}
	}

	namespace Consumables
	{
		namespace Potions
		{
			namespace HealthPotion
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Small)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Large)
			}

			namespace ManaPotion
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Small)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Large)
			}
		}
	}

	namespace Craftables
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fruit)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Daisy)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Blossom)
	}
}