#include "../dxlib_shader/PixelShader.h"

struct PS_INPUT
{
    float4 Position : SV_POSITION; // 座標
    float4 Color : COLOR0; // 頂点カラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標0
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標1
};

cbuffer ParamBuffer : register(b6)
{
    float dissolveThreshold;
    float dissolveRange;
    float2 dummy;
}

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float4 main(PS_INPUT input) : SV_TARGET0
{
    //背景色を設定
    float4 outDiffuse = float4(float3(0.0, 0.0, 0.0), 1.0);
        
    //ワイプ用テクスチャからサンプリング(rgbaからrだけ抽出する)
    float dissolveValue = g_Texture.Sample(g_SamplerState, input.TextureCoord0).r;
    
    //                          0.5          1.0 +     0.3      0.65 - 0.3          
    float threshold = dissolveThreshold * (1.0f + dissolveRange) - dissolveRange;
    //                        0.5             0.35   0.15 / 0.3
    float rate = saturate((dissolveValue - threshold) / dissolveRange);
    
    outDiffuse.a = rate;
    
    return outDiffuse;
   
}