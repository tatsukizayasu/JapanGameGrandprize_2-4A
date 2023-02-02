#pragma once

class FpsController {
private:
    int frame_time; //1フレームの時間(ミリ秒)
    int wait_time; //待ち時間
    int last_time, now_time; //最後に取得した時間と，今の時間
    float count; //フレームのカウント
    float fps; //表示するしたFPS値
    int update_time; //表示値を更新する時間
    int last_update; //最後に表示値を更新した時間

private:
    //初期化
    void Init(float RefreshRate, int UpdateTime);

public:

    //コンストラクタ
    FpsController(float RefreshRate, int UpdateTime) {
        Init(RefreshRate, UpdateTime);
    }

    FpsController() {
        Init(60.0f, 800);
    }

    //待ち時間の計算
    void Wait();

    //FPS値の計算
    float Get();
   
    //描画処理
    void Disp() {
        SetFontSize(10);
        DrawFormatString(10, 10, 0xffffff, "fps:%0.1f", fps);
    }
    //処理をまとめたもの
    float All() {
        Get();
        Wait();
        return (fps);
    }

};

