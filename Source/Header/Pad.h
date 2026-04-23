#pragma once

//コントローラーからの押した瞬間

namespace Pad
{
    // パッドの入力状態取得
    void Update();
    // トリガー判定(ボタンを押した瞬間だけ反応)
    bool IsTrigger(int button);
}