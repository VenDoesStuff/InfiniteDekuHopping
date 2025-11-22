#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_HOOK ("func_808373F8") void InfiniteHops(PlayState* play, Player* this, u16 sfxId) {
    if (CHECK_BTN_ANY(CONTROLLER1(&play->state)->cur.button, BTN_A)){
        this->remainingHopsCounter = 5;}

    
}