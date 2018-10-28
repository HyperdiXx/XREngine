cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightBuffer
{
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};


struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float4 color : COLOR;
};


Texture2D shaderTexture : register(t0);
Texture2D normalTexture : register(t1);

SamplerState SampleType : register(s0);


PixelInputType main(VertexInputType input) 
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	output.tangent = mul(input.tangent, (float3x3)worldMatrix);
	output.tangent = normalize(output.tangent);

	output.binormal = mul(input.binormal, (float3x3)worldMatrix);
	output.binormal = normalize(output.binormal);

	output.color = float4(input.color, 1.0f);

	return output;
}


float4 TerrainPixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float3 lightDir;
	float4 bumpMap;
	float3 bumpNormal;
	float lightIntensity;
	float4 color;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Combine the color map value into the texture color.
	textureColor = saturate(textureColor * input.color * 2.0f);

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel using the normal map.
	bumpMap = normalTexture.Sample(SampleType, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;
	bumpNormal = (bumpMap.x * input.tangent) + (bumpMap.y * input.binormal) + (bumpMap.z * input.normal);
	bumpNormal = normalize(bumpNormal);
	lightIntensity = saturate(dot(bumpNormal, lightDir));

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
	color = saturate(diffuseColor * lightIntensity);

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	color = color * textureColor;
	 
	return color;
}