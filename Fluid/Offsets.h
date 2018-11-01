#pragma once
// Game ->
#define ADDRESS_GameManager 0x4eaa460
#define ADDRESS_GameRenderer 0x4d8fea8
#define ADDRESS_Interface 0x4ea8a60
#define StatusManager  0x4e6d1d8

// Game -> Interface ->
#define OFFSET_Interface 0x400
#define OFFSET_Interface_INCROSS 0x398 // Interface ->

// Game ->GameRenderer ->
#define OFFSET_GameManager_DEREF 0x0
#define OFFSET_GameManager_EngineLINK 0x120 // Deref ->
#define OFFSET_EngineLINK_Engine 0x230 // EngineLink ->
#define OFFSET_Engine_Camera 0x40 // Engine ->

// Game ->GameRenderer -> Camera ->
#define OFFSET_Camera_VIEWRIGHT 0xB0
#define OFFSET_Camera_VIEWUP 0xC0
#define OFFSET_Camera_VIEWFORWARD 0xD0
#define OFFSET_Camera_VIEWTRANSLATION 0xE0
#define OFFSET_Camera_VIEWFOVX 0xF0
#define OFFSET_Camera_VIEWFOVY 0x104

// Game -> GameManager ->
#define OFFSET_GameManager_EntityList 0xC8

// Game -> GameManager -> EntityList -> INDEX -> Entity ->
#define OFFSET_Entity_EntityINFO 0x18
#define OFFSET_EntityINFO_MainComponet 0xA8 // EntityInfo ->
#define OFFSET_MainComponet_CHILDCOMPONENT 0x8 // MainComponet ->
#define OFFSET_CHILDCOMPONENT_HEALTH 0x148 // ChildComponent ->

#define OFFSET_Entity_PlayerInfo 0x2B8
#define OFFSET_PlayerInfo_MainComponet 0x0 // PlayerInfo ->
#define OFFSET_MainComponet_TEAMID 0x146 // MainComponet ->

#define OFFSET_MainComponet_WEAPONCOMPONENT 0x38 // MainComponet ->
#define OFFSET_WEAPONCOMPONENT_WEAPONPROCESSOR 0xF0 // WeaponComponent ->
#define OFFSET_WEAPONPROCESSOR_WEAPON 0x0 // WeaponProcessor ->
#define OFFSET_WEAPON_WEAPONINFO1 0x120 // Weapon ->
#define OFFSET_WEAPON_WEAPONINFO2 0x110 // Weapon ->
#define OFFSET_WEAPONINFO_RECOIL 0xA8 // WeaponInfo ->
#define OFFSET_WEAPONINFO_SPREAD 0x70 // WeaponInfo ->

#define OFFSET_Entity_FEET 0x1D0
#define OFFSET_Entity_NECK 0x170
#define OFFSET_Entity_HEAD 0x180
#define OFFSET_Entity_RIGHTHAND 0xD20//0x1A0
#define OFFSET_Entity_LEFTHAND 0x340//0x1E0

// Game -> GameManager -> EntityList -> INDEX -> Entity -> EntityInfo -> MainComponet ->
#define ORACLE_1 0x30
#define ORACLE_2 0x78 // ESPCHAIN1 ->
#define ORACLE_3 0x2E4 // ESPCHAIN2 ->

// 68 300 264
// 30 178 2E4