#include "../dxlib_shader/PixelShader.h"

struct PS_INPUT
{
    float4 Position : SV_POSITION; // 座標
    float4 DiffuseColor : COLOR0; // ディフューズカラー
    float2 TextureCoord : TEXCOORD0; // テクスチャ座標０
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標１
};

cbuffer cbParam : register(b7)
{
    float4 hp;
    float4 baseColor;
    float4 diffColor;
    float4 lostColor;
};

void main(in PS_INPUT In, out float4 outDiffuse : SV_Target)
{

    //ストレート
    outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    float2 gage = In.TextureCoord * hp.z;
    outDiffuse.rgb += lostColor.rgb * step(hp.y, gage.x);
    outDiffuse.rgb += diffColor.rgb * (1.0f - step(hp.y, gage.x)) * step(hp.x, gage.x);
    outDiffuse.rgb += baseColor.rgb * (1.0f - step(hp.x, gage.x));

}
