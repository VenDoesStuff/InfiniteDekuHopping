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