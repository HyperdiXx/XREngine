#define NUM 4

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightPositionBuffer
{
	float4 lightPosition[NUM];
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 lightPos1 : TEXCOORD1;
    float3 lightPos2 : TEXCOORD2;
    float3 lightPos3 : TEXCOORD3;
    float3 lightPos4 : TEXCOORD4;
};

PixelInputType LightVertexShaderPoint(VertexInputType input)
{
	PixelInputType output;
	float4 worldPos;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);
	worldPos = mul(input.position, worldMatrix);

	output.lightPos1.xyz = lightPosition[0].xyz - worldPos.xyz;
    output.lightPos2.xyz = lightPosition[1].xyz - worldPos.xyz;
    output.lightPos3.xyz = lightPosition[2].xyz - worldPos.xyz;
    output.lightPos4.xyz = lightPosition[3].xyz - worldPos.xyz;

    // Normalize the light position vectors.
    output.lightPos1 = normalize(output.lightPos1);
    output.lightPos2 = normalize(output.lightPos2);
    output.lightPos3 = normalize(output.lightPos3);
    output.lightPos4 = normalize(output.lightPos4);

    return output;
}