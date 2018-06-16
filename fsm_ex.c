

enum BombStates {
	SETTING_STATE,
	TIMMING_STATE
};

enum BombSignals {
	UP_SIG,			// u
	DOWN_SIG,		// d
	ARM_SIG,		// press 'a' to change state
	TICK_SIG		// countdown every 0.1s
};

typedef struct EventTag {
	uint16_t sig;	// Bomb Signals
} Event;

typedef struct TickEvtTag {
	Event super;
	uint8_t fine_time;
} TickEvt;

typedef struct Bomb1Tag {
	uint8_t state;
	uint8_t timeout;
	uint8_t code;
	uint8_t defuse;
} Bomb1;

#define INIT_TIMEOUT 10
#define TRAN(target_) (me->state = (uint8_t)(target_))

void Bomb1_ctor(Bobm1 *me, uint8_t defuse)
{
	me->defuse = defuse;
}

void Bomb1_init(Bomb1 *me)
{
	me->timeout = INIT_TIMEOUT;
	TRAN(SETTING_STATE);
}

void Bomb1_dispatch(Bomb1 *me, Event const *e)
{
	switch (me->state) {
		case	SETTING_STATE: {
			switch (e->sig) {
				case UP_SIG: 
			}

		}


	}




}
