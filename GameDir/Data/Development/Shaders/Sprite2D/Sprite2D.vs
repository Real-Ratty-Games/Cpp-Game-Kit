$input a_position, a_texcoord0
$output v_texcoord0

#include "../Shared/common.sh"

/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position.xy, 0.0, 1.0));
	v_texcoord0 = a_texcoord0;
}