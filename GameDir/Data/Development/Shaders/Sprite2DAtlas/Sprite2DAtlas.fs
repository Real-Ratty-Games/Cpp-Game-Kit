$input v_texcoord0

#include "../Shared/common.sh"

/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/

SAMPLER2D(s_texColor, 0);

uniform vec4 atlasInfo[2];
uniform vec4 color;

void main()
{
	vec2 modifiedUV = v_texcoord0;
	
	float resX = (atlasInfo[0].z / atlasInfo[1].x);
	float resY = (atlasInfo[0].w / atlasInfo[1].y);
	vec2 offsetUv = vec2(atlasInfo[0].x / resX, atlasInfo[0].y / resY);
	modifiedUV = modifiedUV * vec2(1.0 / resX, 1.0 / resY) + offsetUv;

	gl_FragColor = texture2D(s_texColor, modifiedUV);
	gl_FragColor *= color;
}