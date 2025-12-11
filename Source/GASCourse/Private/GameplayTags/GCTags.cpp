#include "GameplayTags/GCTags.h"

namespace GCTags
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile, "GCTags.SetByCaller.Projectile", "Tag for Set By Caller magnitude for projectiles");
	}
	namespace GCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GCTags.GCAbilities.ActivateOnGiven", "Tag for the Abilities that should activate immediately once given");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GCTags.GCAbilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GCTags.GCAbilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GCTags.GCAbilities.Tertiary", "Tag for the Tertiary Ability");
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "GCTags.GCAbilities.Enemy.Attack", "Tag for the enemy attack");
		}
	}
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "GCTags.Events.KillScored", "Tag for the KillScored Event");
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GCTags.Events.Player.HitReact", "Tag for the player hit react event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "GCTags.Events.Player.Death", "Tag for the player death");
		}
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GCTags.Events.Enemy.HitReact", "Tag for the enemy hit react event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "GCTags.Events.Enemy.EndAttack", "Tag for the enemy ending an attack");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHit, "GCTags.Events.Enemy.MeleeTraceHit", "Tag for the enemy melee trace hit");
		}
	}
}