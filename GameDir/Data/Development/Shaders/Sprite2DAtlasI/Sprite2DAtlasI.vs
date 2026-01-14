$input a_position, a_texcoord0, i_data0, i_data1, i_data2, i_data3, i_data4
$output v_texcoord0, v_atlasInfo, v_color

#include "../Shared/common.sh"

/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/

void main()
{
	v_atlasInfo = vec4(i_data4.x, i_data4.y, 1.0, 1.0);

	mat4 model = mtxFromCols(i_data0, i_data1, i_data2, i_data3);
	vec4 worldPos = mul(model, vec4(a_position.xy, 0.0, 1.0) );
	gl_Position = mul(u_viewProj, worldPos);

	v_texcoord0 = a_texcoord0;
	v_color = vec4(i_data4.z, i_data4.w, i_data0.z, 1.0);
}