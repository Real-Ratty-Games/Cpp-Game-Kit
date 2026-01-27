$input v_texcoord0, v_color

#include "../Shared/common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec2 modifiedUV = v_texcoord0;
	gl_FragColor = texture2D(s_texColor, modifiedUV);
	gl_FragColor *= v_color;
}