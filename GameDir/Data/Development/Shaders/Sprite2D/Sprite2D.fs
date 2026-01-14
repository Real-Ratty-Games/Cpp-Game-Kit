$input v_texcoord0

#include "../Shared/common.sh"

/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/

SAMPLER2D(s_texColor, 0);

uniform vec4 color;

void main()
{
	vec2 modifiedUV = v_texcoord0;
	gl_FragColor = texture2D(s_texColor, modifiedUV);
	gl_FragColor *= color;
}