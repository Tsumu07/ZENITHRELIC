#include "../dxlib_shader/VertexShader.h"

SamplerState g_SkySampler : register(s0);
TextureCube g_SkyTexture : register(t0);

struct PS_INPUT
{
    float4 Position : SV_POSITION; // 座標
    float4 WorldPos : POSITION0;
    float4 ShadowMapPos : POSITION1;
    float4 Color : COLOR0; // 頂点カラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標0
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標1
};

cbuffer cbSkyBox : register(b5)
{
    matrix rotation; // ワールド座標
};


//ピクセルを動かす
float4 main(PS_INPUT input) : SV_TARGET0
{
    float4 TexColor;

    float4 pos = mul(input.WorldPos, rotation);
    TexColor = g_SkyTexture.Sample(g_SkySampler, pos.xyz);
    
    return TexColor;
}
