
Texture2D shaderTexture;
SamplerState SampleType;


struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


float4 main(PixelInput input) : SV_TARGET
{
	float4 textureColor;

    textureColor = shaderTexture.Sample(SampleType, input.tex);

    return textureColor;
}
