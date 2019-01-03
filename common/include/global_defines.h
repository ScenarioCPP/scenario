#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H
#include <QString>
#include <QDir>

const int PLAYER = 1;
const int NPC = 2;
const int ROWS = 9;
const int COLS = 12;
const int CELL_SIZE = 16;
const double FRICTION = 0.78;
const double JUMP_INC = 40.0;
const double V_INC = 0.55;
const int TICK = 1;
const int FRAME_LIMIT = 3;
const int MS_DEFAULT = 1000;  // 1 second in milliseconds
const int DEFAULT_FRAME_RATE = MS_DEFAULT/30;  // 30 fps
const double GRAVITY = DEFAULT_FRAME_RATE/9.8;  // as earth-like with this frame rate as we can make it
const QString TITLE_COLOR = "orange";
const int DEFAULT_TIMER_START = 33;
const QString PLAYER1_NAME = "Snow Flake";
const QString DEFAULT_MUSIC = "qrc:/assets/sounds/background_music/bk05.mp3";
const QString PROJECT = "qt/scenario";
const QString DEFAULT_ASSET_ROOT = QDir::homePath()+"/Code/"+PROJECT+"/assets";
const QString DEFAULT_JUMP_SOUND = "jump02";
const QString COMPANY="Scenario";
const QString APPLICATION="Scenario";
const int DIRECTION_RIGHT = 1;
const int DIRECTION_LEFT = -1;

#endif // GLOBAL_DEFINES_H
