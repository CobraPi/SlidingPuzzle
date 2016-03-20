#version 430

in int fsize;
in int instanceID;
in vec2 fuvCoords;
in vec4 fcolor;

uniform sampler2D texture;

void main() {
    vec2 coords;
    coords.s = fuvCoords.s;
    coords.t = fuvCoords.t;
    vec4 texClr = texture2D(texture, coords);
    texClr.a = 1.0;
    gl_FragColor = texClr;
}
