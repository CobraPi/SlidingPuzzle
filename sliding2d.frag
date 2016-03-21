#version 430

in int fsize;
in int instanceID;
in vec2 fuvCoords;
in vec4 fcolor;
flat in int instance;

uniform int hiddenInstance;
uniform sampler2D texture;

out vec4 fragColor;

void main() {
    if (instance == hiddenInstance)
    {
        fragColor = vec4(0,0,0,1);
    }
    else
    {
        vec2 coords;
        coords.s = fuvCoords.s;
        coords.t = fuvCoords.t;
        vec4 texClr = texture2D(texture, coords);
        texClr.a = 1.0;
        fragColor = texClr;
    }
}
