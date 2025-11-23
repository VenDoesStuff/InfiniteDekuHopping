#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "z64player.h"

RECOMP_HOOK ("func_808373F8") void InfiniteHops(PlayState* play, Player* this, u16 sfxId) {
    f32 speed;
    f32 speedXZ;
    
    // Make it so holding A stops hops counter from decreasing by raising it
    if (CHECK_BTN_ANY(CONTROLLER1(&play->state)->cur.button, BTN_A)){
        this->remainingHopsCounter++;
    }
    if (this->remainingHopsCounter > 5){
        this->remainingHopsCounter = 5;
    }

    //Raise minimum hopping speed
    if (this->speedXZ < 8.0f) {
        this->speedXZ = 8.0f;
    }
    
}

void func_80834140(PlayState* play, Player* this, PlayerAnimationHeader* anim);
void func_808345C8(void);
void func_8083B8D0(PlayState* play, Player* this);
s32 func_808373F8(PlayState* play, Player* this, u16 sfxId);
void func_80169EFC(PlayState* this);
void func_8083B930(PlayState* play, Player* this);
void func_8083B32C(PlayState* play, Player* this, f32 arg2);
void Player_SetupTurnInPlace(PlayState* play, Player* this, s16 yaw);
void Player_Action_33(Player* this, PlayState* play);
void Player_Action_49(Player* this, PlayState* play);
void Player_Action_28(Player* this, PlayState* play);
void Player_Action_WaitForPutAway(Player* this, PlayState* play);
s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3);
void Player_Action_1(Player* this, PlayState* play);
void Player_Action_43(Player* this, PlayState* play);
void Player_Action_61(Player* this, PlayState* play);
void Player_Action_54(Player* this, PlayState* play);
void Player_Action_62(Player* this, PlayState* play);
void Player_Action_57(Player* this, PlayState* play);
void Player_Action_58(Player* this, PlayState* play);
void Player_Action_59(Player* this, PlayState* play);
void Player_Action_60(Player* this, PlayState* play);
void Player_Action_55(Player* this, PlayState* play);
s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3);
void Player_Action_56(Player* this, PlayState* play);

extern PlayerAnimationHeader gPlayerAnim_link_swimer_swim_down;

RECOMP_PATCH void func_8083BB4C(PlayState* play, Player* this) {
    f32 sp1C = this->actor.depthInWater - this->ageProperties->unk_2C;

    if (sp1C < 0.0f) {
        this->underwaterTimer = 0;
        if ((this->transformation == PLAYER_FORM_ZORA) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
        }
        Audio_SetBaseFilter(0);
    } else {
        Audio_SetBaseFilter(0x20);
        if ((this->transformation == PLAYER_FORM_ZORA) || (sp1C < 10.0f)) {
            this->underwaterTimer = 0;
        } else if (this->underwaterTimer < 300) {
            this->underwaterTimer++;
        }
    }

    if ((this->actor.parent == NULL) && (Player_Action_33 != this->actionFunc) &&
        (Player_Action_49 != this->actionFunc) &&
        ((Player_Action_28 != this->actionFunc) || (this->actor.velocity.y < -2.0f))) {
        if (this->ageProperties->unk_2C < this->actor.depthInWater) {
            if (this->transformation == PLAYER_FORM_GORON) {
                // # 80834140 is the (a?) death function
                // func_80834140(play, this, &gPlayerAnim_link_swimer_swim_down);
                // Stuff about Deku mask, can be used to make deku void out while goron
                // func_808345C8();
                // func_8083B8D0(play, this);
            } else if (this->transformation == PLAYER_FORM_DEKU) {
                // If hops arent zero, point to the hopping function. (Still hops if commented out.)
                // if (this->remainingHopsCounter != 0) {
                //     func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);
                // } else {
                    if ((play->sceneId == SCENE_20SICHITAI) && (this->unk_3CF == 0)) {
                        if (CHECK_EVENTINF(EVENTINF_50)) {
                            play->nextEntrance = ENTRANCE(TOURIST_INFORMATION, 2);
                        } else {
                            play->nextEntrance = ENTRANCE(TOURIST_INFORMATION, 1);
                        }
                //         // play->transitionTrigger = TRANS_TRIGGER_START;
                //         // play->transitionType = TRANS_TYPE_FADE_BLACK_FAST;
                //         // this->stateFlags1 |= PLAYER_STATE1_200;
                //         // Audio_PlaySfx(NA_SE_SY_DEKUNUTS_JUMP_FAILED);
                    } else if ((this->unk_3CF == 0) &&
                               ((play->sceneId == SCENE_30GYOSON) || (play->sceneId == SCENE_31MISAKI) ||
                                (play->sceneId == SCENE_TORIDE))) {
                        // func_80169EFC(play);
                        // func_808345C8();
                //     } else {
                //         Player_SetAction(play, this, Player_Action_1, 0);
                //         this->stateFlags1 |= PLAYER_STATE1_20000000;
                //     }
                // 8083B8D0 points to the splash SFX when calling into water.
                //     func_8083B8D0(play, this);
                }
            } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) ||
                       (((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) ||
                         !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) &&
                        (Player_Action_43 != this->actionFunc) && (Player_Action_61 != this->actionFunc) &&
                        (Player_Action_62 != this->actionFunc) && (Player_Action_54 != this->actionFunc) &&
                        (Player_Action_57 != this->actionFunc) && (Player_Action_58 != this->actionFunc) &&
                        (Player_Action_59 != this->actionFunc) && (Player_Action_60 != this->actionFunc) &&
                        (Player_Action_55 != this->actionFunc) && (Player_Action_56 != this->actionFunc))) {
                func_8083B930(play, this);
            }
        } else if ((this->stateFlags1 & PLAYER_STATE1_8000000) &&
                   (this->actor.depthInWater < this->ageProperties->unk_24) &&
                   (((Player_Action_56 != this->actionFunc) && !(this->stateFlags3 & PLAYER_STATE3_8000)) ||
                    (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
            if (this->skelAnime.movementFlags == 0) {
                Player_SetupTurnInPlace(play, this, this->actor.shape.rot.y);
            }
            func_8083B32C(play, this, this->actor.velocity.y);
        }
    }
}