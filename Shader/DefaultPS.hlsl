#include "../dxlib_shader/PixelShader.h"

//カメラ・ライト
cbuffer cbCamera : register(b4)
{
    float4 CameraPos; // ワールド座標
    float4 LightDir; // 平行光
};

//テクスチャ
SamplerState g_SrcSampler : register(s0);
Texture2D g_SrcTexture : register(t0); // 元画像
Texture2D g_NormalTexture : register(t1); // ノーマルマップ

SamplerState g_ShadowMap0Sampler : register(s8);
Texture2D g_ShadowMap0Texture : register(t8);

//入力
struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 WorldPos : POSITION0;
    float4 ShadowMapPos : POSITION1;
    float4 Color : COLOR0;
    float2 Tex0 : TEXCOORD0;

    float3 Tangent : TEXCOORD2;
    float3 Binormal : TEXCOORD3;
    float3 Normal : TEXCOORD4;
};

//Pixel Shader
float4 ps_simple(PS_INPUT input) : SV_TARGET0
{
    //元のテクスチャ色
    float4 texColor = g_SrcTexture.Sample(g_SrcSampler, input.Tex0);

    //ノーマルマップ
    float3 n = g_NormalTexture.Sample(g_SrcSampler, input.Tex0).xyz;
    n = n * 2.0f - 1.0f;

    n.xy *= 0.5f;
    n = normalize(n);
    
    float3x3 TBN =
    {
        normalize(input.Tangent),
        normalize(input.Binormal),
        normalize(input.Normal)
    };

    float3 normal = normalize(mul(n, TBN));

    //明るさ計算
    float3 L = normalize(-LightDir.xyz);
    float light = dot(normal, L);
    light = light * 0.5f + 0.5f;
    light = saturate(light);

    float brightness = lerp(0.4f, 1.0f, light);
    
    //シャドウマップ
    float shadow = 1.0f;

    if (input.ShadowMapPos.x >= -1 && input.ShadowMapPos.x <= 1 &&
        input.ShadowMapPos.y >= -1 && input.ShadowMapPos.y <= 1 &&
        input.ShadowMapPos.z >= 0 && input.ShadowMapPos.z <= 1)
    {
        float2 uv;
        uv.x = (input.ShadowMapPos.x + 1.0f) * 0.5f;
        uv.y = 1.0f - (input.ShadowMapPos.y + 1.0f) * 0.5f;

        float depth = g_ShadowMap0Texture
            .Sample(g_ShadowMap0Sampler, uv).r;

        if (depth < input.ShadowMapPos.z - 0.001f)
        {
            shadow = 0.6f;
        }
    }

    //最終出力
    float3 finalColor = texColor.rgb * brightness * shadow;

    return float4(finalColor, texColor.a);
}