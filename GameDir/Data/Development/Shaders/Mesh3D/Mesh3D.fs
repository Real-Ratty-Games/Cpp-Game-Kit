$input v_texcoord0

#include "../Shared/common.sh"

SAMPLER2D(tex_diffuse, 0);

void main()
{
	gl_FragColor = texture2D(tex_diffuse, v_texcoord0);
}