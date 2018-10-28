cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};


PixelInput VertexShaderColor(VertexInput input)
{
	PixelInput output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
		
	output.color = input.color;

	return output;
}

float4 PixelShaderColor(PixelInput input) : SV_TARGET
{
	return input.color;
//return float4( 1.0f, 1.0f, 0.0f, 1.0f );
}
