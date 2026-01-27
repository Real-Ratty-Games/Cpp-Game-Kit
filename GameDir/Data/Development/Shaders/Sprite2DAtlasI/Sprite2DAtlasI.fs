$input v_texcoord0, v_atlasInfo, v_color

#include "../Shared/common.sh"

SAMPLER2D(s_texColor, 0);

uniform vec4 atlasInfo[2];

void main()
{
	vec2 modifiedUV = v_texcoord0;
	
	float resX = (atlasInfo[0].z / atlasInfo[1].x);
	float resY = (atlasInfo[0].w / atlasInfo[1].y);
	vec2 offsetUv = vec2(v_atlasInfo.x / resX, v_atlasInfo.y / resY);
	modifiedUV = modifiedUV * vec2(1.0 / resX, 1.0 / resY) + offsetUv;

	gl_FragColor = texture2D(s_texColor, modifiedUV);
	gl_FragColor *= v_color;
}