/*
     オブジェクト管理クラス

     基本的には１つのシーンに１つのオブジェクト管理クラスを用意する。
*/

#include "DxLib.h"
#include "../Haeder/ObujectManeger.h"
#include "../Haeder/Object.h"

/**
*  @fn コンストラクタ
*/
ObjectManager::ObjectManager() : mpObject(nullptr)
{

}

/**
*  @fn デストラクタ
*/
ObjectManager::~ObjectManager()
{

}

/**
*  @fn Initialize
*  @brief 初期化処理
*/
void ObjectManager::Initaliza()
{

}

/**
*  @fn Update
*  @brief 更新
*/
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

}

/**
*  @fn Draw
*  @brief 描画
*/
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

/**
*  @fn Finaliza
*  @brief 終了処理
*/
void ObjectManager::Finaliza()
{
}

/**
*  @fn Add
*  @brief オブジェクト追加
*/
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

/**
*  @fn Delete
*  @brief オブジェクトの削除
*  @detail オブジェクトを直接削除したいときはこれを呼ぶ
*/
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
        delete object;
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
    delete target;
    target = nullptr;
}

/**
* @fn DeleteAllIfNeeded
* @必要であればオブジェクト削除を行う
* @detall 全オブジェクトのUpdate後に呼び出す
* そうすることで、ほかのオブジェクトへの干渉が少なくなり、より安全な処理が行える
*/
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

/**
* @fn DeleteAll
* @オブジェクト全削除を行う
* @detall 
*/
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
}

/**
* @ fn FindByTag
* @ brief タグからオブジェクトを取得する
*/
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

/**
* @ fn FindsByTag
* @ brief タグからオブジェクトを取得する
* 見つからなかった場合はnullを
*/
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

    //見つからなかったのでnullを返しておく
    return result;
}

