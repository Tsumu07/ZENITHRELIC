#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ResourceManeger.h"
#include "../Master.h"
#include <cassert>

//コンストラクタ
ObjectManager::ObjectManager() 
: mpObject(nullptr)
, matView()
{

}

//デストラクタ
ObjectManager::~ObjectManager()
{

}

//初期化処理
void ObjectManager::Initaliza()
{

}

//更新
void ObjectManager::Update()
{
    //何も生成されていないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object *workObject = mpObject;

    do
    {
        workObject->Update();
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);

    for (auto it = effectList.begin(); it != effectList.end(); )
    {
        // エフェクトが終了しているかをチェックする（0が再生中）
        if (IsEffekseer3DEffectPlaying((*it).second) != 0)
            it = effectList.erase(it);  // 再生が終了していたらリストから削除
        else
            ++it;  // 継続中なら次へ
    }

    // カメラのビュー行列を取得する。
    matView = GetCameraViewMatrix();

    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();
    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();
}

//描画
void ObjectManager::Draw()
{
    //何も生成されていないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object *workObject = mpObject;

    do
    {
        workObject->Draw();
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);
}

//終了処理
void ObjectManager::Finaliza()
{
}

//オブジェクト追加
void ObjectManager::Add(Object *object)
{
    //もし最初のオブジェクトがないなら入れる
    if (mpObject == nullptr)
    {
        mpObject = object;
        return;
    }

    // NextObject が null になっているものを検索
    Object *currentObject = mpObject;
    Object *nextObject = mpObject->GetNextObject();

    while (nextObject != nullptr)
    {
        currentObject = nextObject;
        nextObject = currentObject->GetNextObject();
    }

    //　見つけたらオブジェクトをセット
    currentObject->SetNextObject(object);
    object->SetPrevObject(currentObject);

}

//オブジェクトの削除
//オブジェクトを直接削除したいときはこれを呼ぶ
void ObjectManager::Delete(Object *object)
{
    //最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    //もし最初のオブジェクトが削除対象であれば専用処理を行う
    if (mpObject == object)
    {
        Object *next = mpObject->GetNextObject();

        if (next != nullptr)
        {
            next->SetPrevObject(nullptr);
            mpObject = next;
        }

        object->Finaliza();
        objList.remove(object);

        delete object;

        if (next == nullptr)
        {
            mpObject = nullptr;
        }

        return;
    }

    //削除対象のオブジェクトを探索
    Object *target = mpObject->GetNextObject();
    while (target != object)
    {
        //次のオブジェクトがnullの場合は探索を終わる　(削除処理もしないのでreturnしておく)
        if (target == nullptr)
        {
            return;
        }

        target = target->GetNextObject();
    }

    //　削除対象を見つけたら、その手間と次のオブジェクトを取得しておく
    Object *prev = target->GetPrevObject();
    Object *next = target->GetNextObject();

    //前後の繋がりを設定
    prev->SetNextObject(next);
    if (next != nullptr)
    {
        next->SetPrevObject(prev);
    }

    //総合性がとれたところで削除対象を削除
    target->Finaliza();

    objList.remove(target);

    delete target;

    target = nullptr;
}

//全オブジェクトのUpdate後に呼び出す
void ObjectManager::DeleteAllIfNeeded()
{
    //最初のオブジェクトが何もないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    //削除フラグが立っているオブジェクトを順番に削除
    Object *target = mpObject;
    do
    {
        Object *next = target->GetNextObject();
        if (target->IsDeleteFlag())
        {
            Delete(target);
        }
        target = next;

    } while (target != nullptr);

}

//オブジェクト全削除を行う
void ObjectManager::DeleteAll()
{
    //最初のオブジェクトが何もないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    //オブジェクトの全削除
    Object *target = mpObject;
    do
    {
        Object *next = target->GetNextObject();
        Delete(target);
        target = next;

    } while (target != nullptr);

    objList.clear();
}

//タグからオブジェクトを取得する
Object *ObjectManager::FindByTag(int tag)
{

    //最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {

        return nullptr;
    }

    Object *target = mpObject;
    do
    {
        Object *next = target->GetNextObject();
        if (target->GetTag() == tag)
        {
            //目的のタグと一致するオブジェクトがあればそれを返す
            return target;
        }
        target = next;
    } while (target != nullptr);

    //見つからなかったのでnullを返しておく
    return nullptr;
}

//タグからオブジェクトを取得する
std::vector<Object *> ObjectManager::FindsByTag(int tag)
{
    //格納するリストが作られる
    std::vector<Object *> result;

    //最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return result;
    }

    Object *target = mpObject;

    do
    {
        Object *next = target->GetNextObject();
        if (target->GetTag() == tag)
        {
            //目的のタグと一致するオブジェクトがあればそれを返す
            result.push_back(target);
        }
        target = next;

    } while (target != nullptr);

    //見つからなかった場合は空のvectorを返す
    return result;
}

void ObjectManager::SetDeleteFlagAll()
{
    //最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object *target = mpObject;
    do
    {
        Object *next = target->GetNextObject();
        target->SetDeleteFlag(true);
        target = next;
    } while (target != nullptr);

}

//オブジェクトをリストに追加する
void ObjectManager::AddObjectList(Object* obj)
{
    if (objList.empty())
    {
        objList.push_back(obj);
    }

    else
    {
        //レイヤー番号により挿入位置を決定する（昇順の挿入ソート）
        auto it = objList.begin();
        while (it != objList.end() && (*it)->GetLayer() < obj->GetLayer())
        { 
            it++;
        }

        objList.insert(it, obj);
    }

}

//　タグで指定されたオブジェクトのリストを取得する
std::list<Object*> ObjectManager::GetObjectByTag(int tag)
{
    std::list<Object*> objectsWithTag;

    for (Object* obj : objList)
    {
        if (obj->GetTag() == tag)
        {
            objectsWithTag.push_back(obj);
        }
    }

    return objectsWithTag;
}

void ObjectManager::AddEffect(std::string name, std::string tag, VECTOR pos, VECTOR rot, VECTOR scale)
{
    //リソースマネージャーからハンドルを取得する
    int handle = Master::mpResourceManager->GetEffect(name);

    if (handle == -1)
        return;

    // エフェクトを再生する。
    int playingEffectHandle = PlayEffekseer3DEffect(handle);

    // 再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);
    SetRotationPlayingEffekseer3DEffect(playingEffectHandle, rot.x, rot.y, rot.z);
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);

    effectList.push_back(std::make_pair(tag, playingEffectHandle));
}

void ObjectManager::UpdateEffect(std::string tag, VECTOR pos, VECTOR rot, VECTOR scale)
{
    //リソースマネージャーからハンドルを取得する
    int playingEffectHandle = GetEffectByTag(tag);

    if (playingEffectHandle == -1)
        return;

    // 再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);
    SetRotationPlayingEffekseer3DEffect(playingEffectHandle, rot.x, rot.y, rot.z);
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

int ObjectManager::GetEffectByTag(std::string tag)
{
    for (auto& pair : effectList) {
        if (pair.first == tag) {
            return pair.second;
        }
    }

    return -1;
}

void ObjectManager::RestoreViewMatrix(void) const
{
    SetCameraViewMatrix(matView);

    SetCameraNearFar(100.0f, 150000.0f);

    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();
}