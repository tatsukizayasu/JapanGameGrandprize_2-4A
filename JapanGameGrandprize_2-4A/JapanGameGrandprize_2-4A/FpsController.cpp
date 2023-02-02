#include"DxLib.h"
#include "FpsController.h"


void FpsController::Init(float RefreshRate, int UpdateTime) {
    frame_time = (int)(1000.0f / RefreshRate); //1フレームの時間の計算
    update_time = UpdateTime;
    wait_time = 0;
    last_time = now_time = 0;
    count = 0.0f;
    fps = 0.0f;
    last_update = 0;
}
//待ち時間の計算
void FpsController::Wait() {
    now_time = GetNowCount();
    wait_time = frame_time - (now_time - last_time);
    if (wait_time > 0) { //待ち時間があれば
        WaitTimer(wait_time); //指定時間待つ
    }
    last_time = GetNowCount();
}

//FPS値の計算
float FpsController::Get() {
    count += 1.0f;
    if (update_time < (last_time - last_update)) { //アップデート時間になっていれば
        fps = count / (float)(last_time - last_update) * 1000.0f; //FPS値の計算
        last_update = last_time;
        count = 0.0f;
    }
    return (fps);
}

