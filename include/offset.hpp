/*****************************************************************//**
 * \file   offset.hpp
 * \brief  Updated for 0.12.12.15.16909
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

#ifndef OFFSET_H
#define OFFSET_H

typedef unsigned long long offset_t;

/**
 * Global
 */
#define O_GOM 0x17F8D28

/**
 * Game Object Iteration
 */
#define O_GOM_NODE_PREVIOUS 0x0
#define O_GOM_NODE_NEXT 0x8
#define O_GOM_NODE_DATA 0x10
#define O_GOM_TAGGED_NODES 0x8
#define O_GOM_MAINCAMERA_TAGGED_NODES 0x10
#define O_GOM_ACTIVE_NODES 0x28

/**
 * UnityEngine::Object
 */
#define O_OBJECT_INSTANCEID 0x8
#define O_OBJECT_SCRIPTING_HANDLE 0x18		// 'ScriptingGCHandle'
#define O_OBJECT_SCRIPTING_WEAKNESS 0x20	// 'ScriptingGCHandleWeakness'
#define O_OBJECT_SCRIPTING_OBJECT 0x28		// 'ScriptingObjectPtr'

/**
 * UnityEngine::GameObject
 */
#define O_GAMEOBJECT_COMPONENT_ARRAY 0x30
#define O_GAMEOBJECT_COMPONENT_SIZE 0x40
#define O_GAMEOBJECT_COMPONENT_NEXT 0x8
#define O_GAMEOBJECT_LAYER 0x50
#define O_GAMEOBJECT_TAG 0x54
#define O_GAMEOBJECT_ISACTIVE 0x56
#define O_GAMEOBJECT_ISACTIVE_CACHED 0x57
#define O_GAMEOBJECT_NAME 0x60

/**
 * UnityEngine::Component
 */
#define O_COMPONENT_SCRIPTING_OBJECT 0x28
#define O_COMPONENT_GAMEOBJECT 0x30

/**
 * UnityEngine::Camera
 */
#define O_CAMERA_STATE 0x40
#define O_CAMERA_STATE_WORLDTOCAMERA_MATRIX 0x1C
#define O_CAMERA_STATE_PROJECTION_MATRIX 0x5C
#define O_CAMERA_STATE_FOV 0x11C
#define O_CAMERA_STATE_BACKGROUND_COLOR 0x3B4
#define O_CAMERA_STATE_DEPTH 0x41C
#define O_CAMERA_STATE_CAMERATYPE 0x4D0

/**
 * UnityEngine::Transform
 */
#define O_TRANSFORM_ACCESS 0x38
#define O_TRANSFORM_ACCESS_INDEX 0x8
#define O_TRANSFROM_ACCESS_HIERARCHY 0x0
#define O_TRANSFORM_ACCESS_HIERARCHY_CAPACITY 0x10
#define O_TRANSFORM_ACCESS_HIERARCHY_FIRSTFREEINDEX 0x14
#define O_TRANSFORM_ACCESS_HIERARCHY_LOCALTRANSFORMS 0x18
#define O_TRANSFORM_ACCESS_HIERARCHY_PARENTINDICES 0x20

/**
 * Mono Class
 */
#define O_MONO_CLASS_INSTANCE_SIZE 0x1C
#define O_MONO_CLASS_PARENT 0x30
#define O_MONO_CLASS_NAME 0x48
#define O_MONO_CLASS_NAMESPACE 0x50

/**
 * System.String
 */
#define O_STRING_LENGTH 0x10
#define O_STRING_FIRSTCHAR 0x14

/**
 * System.Array
 */
#define O_ARRAY_SIZE 0x18
#define O_ARRAY_BASE 0x20

/**
 * System.Collections.Generic.List
 */
#define O_LIST_ITEMS 0x10
#define O_LIST_SIZE 0x18

/**
 * EFT.Player
 */
#define O_PLAYER_MOVEMENTCONTEXT 0x40
#define O_PLAYER_PLAYERBODY 0xA8
#define O_PLAYER_PROCEDURALWEPANIM 0x198
#define O_PLAYER_PROFILE 0x4C0
#define O_PLAYER_PHYSICAL 0x4D0
#define O_PLAYER_HANDSCONTROLLER 0x510
#define O_PLAYER_PLAYERBONES 0x558

/**
 * EFT.Profile
 */
#define O_PROFILE_ID 0x10
#define O_PROFILE_ACCOUNTID 0x18
#define O_PROFILE_INFO 0x28
#define O_PROFILE_INFO_NICKNAME 0x10
#define O_PROFILE_INFO_GROUPID 0x18
#define O_PROFILE_INFO_SIDE 0x58
#define O_PROFILE_INFO_REGISTRATION_DATE 0x5C
#define O_PROFILE_INFO_SAVAGE_LOCKTIME 0x60
#define O_PROFILE_INFO_MEMBER_CATEGORY 0x70
#define O_PROFILE_INVENTORY 0x48
#define O_PROFILE_SKILLS 0x60
#define O_PROFILE_STATS 0xE8

/**
 * EFT.Player.FirearmController
 */
#define O_FIREARMCONTROLLER_FIREPORT 0xE8

/**
 * EFT.PlayerBody
 */
#define O_PLAYERBODY_PLAYERBONES 0x20
#define O_PLAYERBODY_SKELETONROOTJOINT 0x28

/**
 * PlayerBones
 */
#define O_PLAYERBONES_FIREPORT 0x140

/**
 * MovementContext
 */
#define O_MOVEMENTCONTEXT_ROTATION 0x22C

/**
 * @brief Diz.Skinning.Skeleton
 */
#define O_SKELETONROOTJOINT_BONES 0x18
#define O_SKELETONROOTJOINT_KEYS 0x20
#define O_SKELETONROOTJOINT_VALUES 0x28

/**
 * EFT.GameWorld
 */
#define O_GAMEWORLD_LOOTLIST 0x60
#define O_GAMEWORLD_LOOTITEMS 0x70
#define O_GAMEWORLD_ALLLOOT 0x78
#define O_GAMEWORLD_REGISTEREDPLAYERS 0x80

/**
 * EFT.BifacialTransform
 */
#define O_BIFACIALTRANSFORM_ORIGINAL 0x10

/**
 * Physical
 */
#define O_PHYSICAL_LEGSSTAMINA 0x38
#define O_PHYSICAL_HANDSSTAMINS 0x40
#define O_PHYSICAL_OXYGEN 0x48

/**
 * EFT.ProceduralWeaponAnimation
 */
#define O_PROCWEPANIM_MASK 0x100
#define O_PROCWEPANIM_BREATH 0x28
#define O_PROCWEPANIM_WALK 0x30
#define O_PROCWEPANIM_MOTION 0x38
#define O_PROCWEPANIM_FORCE 0x40
#define O_PROCWEPANIM_SHOT 0x48
#define O_PROCWEPANIM_AIMINGDISPLACEMENT 0x2F8

/**
 * ShotEffector
 */
#define O_SHOTEFFECTOR_RECOILSTRENGTH_XY 0x40
#define O_SHOTEFFECTOR_RECOILSTRENGTH_Z 0x48
#define O_SHOTEFFECTOR_INTENSITY 0x70

/**
 * EFT.Animations.BreathEffector
 */
#define O_BREATHEFFECTOR_INTENSITY 0xA4
#define O_BREATHEFFECTOR_BREATHINTENSITY 0xAC

/**
 * WalkEffector
 */
#define O_WALKEFFECTOR_INTENSITY 0x44

/**
 * MotionEffector
 */
#define O_MOTIONEFFECTOR_INTENSITY 0xD0

/**
 * ForceEffector
 */
#define O_FORCEEFFECTOR_INTENSITY 0x28

#endif
