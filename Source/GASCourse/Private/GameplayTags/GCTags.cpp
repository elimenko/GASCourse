#include "GameplayTags/GCTags.h"

namespace GCTags
{
	namespace GCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GCTags.GCAbilities.ActivateOnGiven", "Tag for the Abilities that should activate immediately once given");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GCTags.GCAbilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GCTags.GCAbilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GCTags.GCAbilities.Tertiary", "Tag for the Tertiary Ability");
	}
	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GCTags.Events.Enemy.HitReact", "Tag for the enemy hit react event");
		}
	}
}