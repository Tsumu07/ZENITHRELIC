#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>

/*
　　前方宣言
*/
class Object;

class ObjectManager 
{
private:

    Object* mpObject;

    std::list<Object*> objList;
    std::list<std::pair<std::string, int>> effectList;

    MATRIX matView;


public:
    ObjectManager();     //コンストラクタ
    ~ObjectManager();    //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    void Add(Object *object);    //リストにオブジェクトを追加
    void Delete(Object *object); //リストからオブジェクトを削除

    //オブジェクト全削除
    void DeleteAll();

    //必要であればオブジェクトを削除する
    void DeleteAllIfNeeded();

    Object* FindByTag(int tag);

    std::vector<Object *> FindsByTag(int tag);

    void SetDeleteFlagAll();

    //オブジェクトリストの追加
    void AddObjectList(Object* obj);

    //オブジェクトリストの取り出し
    std::list<Object*> GetObjectByTag(int tag);

    std::list<Object*>& GetObjectList() { return objList; }

    //エフェクト関係
    void AddEffect(std::string name, std::string tag, VECTOR pos, VECTOR rot, VECTOR scale);
    void UpdateEffect(std::string tag, VECTOR pos, VECTOR rot, VECTOR scale);
    int GetEffectByTag(std::string tag);

    //カメラの復元
    void RestoreViewMatrix() const;
};
