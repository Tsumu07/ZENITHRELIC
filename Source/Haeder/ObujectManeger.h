#pragma once
#include <vector>
/*
　　前方宣言
*/
class Object;

class ObjectManager 
{
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

private:

    Object *mpObject;
};
